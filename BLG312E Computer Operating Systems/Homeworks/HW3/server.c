#include "blg312e.h"
#include "request.h"

// Defines a structural data type representing a node in a queue.
typedef struct queue_node {
    int thread_size; // Stores the thread size related to the node.
    int data; // Holds the data stored in the node.
    struct queue_node* next; // Pointer to the next node.
    char file_name[MAXLINE]; // Stores the file name associated with the node.
    time_t last_modified; // Stores the last modified time of the file.
    off_t file_size; // Stores the size of the file.
} queue_node;

queue_node* queue_front = NULL; // Points to the front of the queue.
queue_node* queue_rear = NULL; // Points to the rear of the queue.
int node_count = 0; // Keeps track of the number of nodes in the queue.
int max_node_count = 4; // Maximum number of nodes allowed in the queue.
char scheduling_policy[4]; // Stores the scheduling policy (FIFO, RFF, SFF).

pthread_mutex_t queue_lock; // Mutex lock for thread synchronization.
sem_t empty_slots; // Semaphore to track empty slots in the queue.
sem_t filled_slots; // Semaphore to track filled slots in the queue.

// Function to enqueue a new node into the queue.
void enqueue_node(queue_node* new_node) {
    if (queue_front == NULL) { // If the queue is empty.
        queue_front = queue_rear = new_node; // Set both front and rear to the new node.
    } else {
        queue_node* current = queue_front; // Start from the front of the queue.
        queue_node* previous = NULL; // Previous node starts as NULL.

        // Enqueue based on the scheduling policy.
        if (strcmp(scheduling_policy, "FIFO") == 0) {
            queue_rear->next = new_node; // Add new node at the rear.
            queue_rear = new_node; // Update the rear pointer.
        } else if (strcmp(scheduling_policy, "RFF") == 0) { // Recent First Policy.
            while (current != NULL && current->last_modified >= new_node->last_modified) {
                previous = current;
                current = current->next;
            }
            if (previous == NULL) {
                new_node->next = queue_front; // Insert new node at the front.
                queue_front = new_node;
            } else {
                new_node->next = current; // Insert new node in the middle.
                previous->next = new_node;
            }
        } else if (strcmp(scheduling_policy, "SFF") == 0) { // Smallest First Policy.
            while (current != NULL && current->file_size <= new_node->file_size) {
                previous = current;
                current = current->next;
            }
            if (previous == NULL) {
                new_node->next = queue_front; // Insert new node at the front.
                queue_front = new_node;
            } else {
                new_node->next = current; // Insert new node in the middle.
                previous->next = new_node;
            }
        }
    }
}

// Function to enqueue a new node based on data and file name.
int enqueue(int data, char* file_name) {
    int ret = -1;
    struct stat file_stat;
    if (node_count < max_node_count) { // Check if the queue is not full.
        queue_node* new_node = (queue_node*) malloc(sizeof(queue_node)); // Allocate memory for the new node.
        if (new_node == NULL) {
            return ret; // Return -1 if memory allocation fails.
        }
        new_node->data = data; // Set the data of the new node.
        new_node->next = NULL; // Initialize next pointer to NULL.
        node_count++; // Increment the node count.

        strncpy(new_node->file_name, file_name, MAXLINE); // Copy the file name to the new node.
        if (stat(file_name, &file_stat) == 0) { // Get file statistics.
            new_node->last_modified = file_stat.st_mtime; // Set last modified time.
            new_node->file_size = file_stat.st_size; // Set file size.
        } else {
            new_node->last_modified = 0; // Default last modified time.
            new_node->file_size = 0; // Default file size.
        }

        enqueue_node(new_node); // Enqueue the new node.
        ret = 0; // Return 0 on success.
    }
    return ret; // Return the result.
}

// Function to dequeue a node from the queue.
int dequeue() {
    int holder = -1;
    if (queue_front != NULL) { // Check if the queue is not empty.
        holder = queue_front->data; // Get the data from the front node.
        queue_node* temp = queue_front; // Temporarily store the front node.
        queue_front = queue_front->next; // Move the front pointer to the next node.
        if (queue_front == NULL) {
            queue_rear = NULL; // If the queue becomes empty, set rear to NULL.
        }
        free(temp); // Free the memory of the dequeued node.
        node_count--; // Decrement the node count.
    }
    return holder; // Return the data of the dequeued node.
}

// Function to check if the queue is full or empty.
int is_full_or_empty() {
    if (node_count == max_node_count) { // Check if the queue is full.
        return 1; // Return 1 if full.
    } else if (node_count == 0) { // Check if the queue is empty.
        return 0; // Return 0 if empty.
    }
    return -1; // Return -1 if neither.
}

// Function to set the maximum number of nodes allowed in the queue.
void set_max_nodes(int max) {
    max_node_count = max;
}

// Producer routine to handle incoming connections and enqueue requests.
int producer_routine(int connection_fd, char* file_name) {
    sem_wait(&empty_slots); // Wait for an empty slot.
    pthread_mutex_lock(&queue_lock); // Acquire the mutex lock.

    enqueue(connection_fd, file_name); // Enqueue the new request.

    pthread_mutex_unlock(&queue_lock); // Release the mutex lock.
    sem_post(&filled_slots); // Signal that a slot has been filled.
    return 0;
}

// Consumer routine to handle requests from the queue.
void* consumer_routine() {
    while (1) {
        sem_wait(&filled_slots); // Wait for a filled slot.
        pthread_mutex_lock(&queue_lock); // Acquire the mutex lock.

        int request_number = dequeue(); // Dequeue a request.

        pthread_mutex_unlock(&queue_lock); // Release the mutex lock.
        sem_post(&empty_slots); // Signal that a slot has been emptied.
        requestHandle(request_number); // Handle the request.
        Close(request_number); // Close the connection.
    }
}

// Function to create a thread pool of consumer threads.
void create_thread_pool(pthread_t* threads, int thread_count) {
    for (int i = 0; i < thread_count; i++) {
        pthread_create(&threads[i], NULL, consumer_routine, NULL); // Create a new consumer thread.
    }
}

// Function to parse command line arguments.
void parse_arguments(int* port, int* thread_count, int* buffer_count, char* policy, int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <port> <threads> <buffers> <policy (FIFO|RFF|SFF)> \n", argv[0]);
        exit(1);
    }
    
    *port = atoi(argv[1]); // Parse the port number.
    *thread_count = atoi(argv[2]); // Parse the thread count.
    *buffer_count = atoi(argv[3]); // Parse the buffer count.
    strncpy(policy, argv[4], 4); // Copy the scheduling policy.
    policy[3] = '\0'; // Null-terminate the policy string.

    if (*thread_count < 0 || *buffer_count < 0) {
        fprintf(stderr, "Please enter positive integers for threads and buffers\n");
        exit(1);
    }
    set_max_nodes(*buffer_count); // Set the maximum number of nodes.
}

int main(int argc, char** argv) {
    int listen_fd;
    int connection_fd;
    int port;
    int client_len;
    int thread_count;
    int buffer_count;
    struct sockaddr_in client_addr;
    char policy[4];

    parse_arguments(&port, &thread_count, &buffer_count, policy, argc, argv); // Parse command line arguments.
    pthread_mutex_init(&queue_lock, NULL); // Initialize the mutex lock.
    sem_init(&empty_slots, 0, buffer_count); // Initialize the empty slots semaphore.
    sem_init(&filled_slots, 0, 0); // Initialize the filled slots semaphore.
    pthread_t threads[thread_count]; // Create an array for thread handles.

    create_thread_pool(threads, thread_count); // Create the thread pool.

    listen_fd = Open_listenfd(port); // Open a listening socket.
    while (1) {
        client_len = sizeof(client_addr); // Set the size of the client address structure.
        connection_fd = Accept(listen_fd, (SA*) &client_addr, (socklen_t*) &client_len); // Accept a new connection.

        char file_name[MAXLINE];

        producer_routine(connection_fd, file_name); // Handle the new connection.
    }

    return 1;
}
