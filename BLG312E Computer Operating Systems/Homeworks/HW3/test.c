#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include "blg312e.h"

#define NUM_CLIENTS 100
#define TEST_PORT 5003

// Stub implementations for testing
int Open_clientfd(char* hostname, int port) {
    int clientfd;
    struct hostent *hp;
    struct sockaddr_in serveraddr;

    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    if ((hp = gethostbyname(hostname)) == NULL) {
        return -2;
    }
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)hp->h_addr, (char *)&serveraddr.sin_addr.s_addr, hp->h_length);
    serveraddr.sin_port = htons(port);

    if (connect(clientfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) {
        return -1;
    }
    return clientfd;
}

void Close(int fd) {
    close(fd);
}

// Simulates a basic client sending a GET request
void* client_simulation(void* arg) {
    int client_socket = *((int*)arg);
    // Simulate a basic HTTP GET request for home.html
    char request[] = "GET /home.html HTTP/1.1\r\nHost: localhost\r\n\r\n";
    send(client_socket, request, sizeof(request), 0);

    char response[4096];
    recv(client_socket, response, sizeof(response), 0);
    printf("Response: %s\n", response);

    Close(client_socket);
    return NULL;
}

// Tests basic functionality of the server
void basic_functionality_test() {
    int client_socket = Open_clientfd("localhost", TEST_PORT);
    assert(client_socket > 0);

    pthread_t client_thread;
    pthread_create(&client_thread, NULL, client_simulation, (void*)&client_socket);
    pthread_join(client_thread, NULL);

    printf("Basic functionality test finished.\n");
    Close(client_socket);
}

// Simulates multiple clients for load testing
void* client_load_simulation(void* arg) {
    int client_socket = *((int*)arg);
    char request[] = "GET /home.html HTTP/1.1\r\nHost: localhost\r\n\r\n";
    send(client_socket, request, sizeof(request), 0);

    char response[4096];
    recv(client_socket, response, sizeof(response), 0);
    Close(client_socket);
    return NULL;
}

// Tests server performance under load
void load_testing(int num_clients) {
    pthread_t client_threads[NUM_CLIENTS];
    int client_sockets[NUM_CLIENTS];

    for (int i = 0; i < num_clients; i++) {
        client_sockets[i] = Open_clientfd("localhost", TEST_PORT);
        pthread_create(&client_threads[i], NULL, client_load_simulation, (void*)&client_sockets[i]);
    }

    for (int i = 0; i < num_clients; i++) {
        pthread_join(client_threads[i], NULL);
    }

    printf("Load testing with %d clients finished.\n", num_clients);
}

// Simulates a client requesting a large file for stress testing
void* client_stress_simulation(void* arg) {
    int client_socket = *((int*)arg);
    char request[] = "GET /home.html HTTP/1.1\r\nHost: localhost\r\n\r\n";
    send(client_socket, request, sizeof(request), 0);

    char response[4096];
    while (recv(client_socket, response, sizeof(response), 0) > 0);
    Close(client_socket);
    return NULL;
}

// Tests server behavior under extreme load conditions
void stress_testing(int num_clients) {
    pthread_t client_threads[NUM_CLIENTS];
    int client_sockets[NUM_CLIENTS];

    for (int i = 0; i < num_clients; i++) {
        client_sockets[i] = Open_clientfd("localhost", TEST_PORT);
        pthread_create(&client_threads[i], NULL, client_stress_simulation, (void*)&client_sockets[i]);
    }

    for (int i = 0; i < num_clients; i++) {
        pthread_join(client_threads[i], NULL);
    }

    printf("Stress testing with %d clients finished.\n", num_clients);
}

int main() {
    printf("Starting basic functionality test...\n");
    basic_functionality_test();

    printf("Starting load test...\n");
    load_testing(50);  // Test with 50 concurrent clients

    printf("Starting stress test....\n");
    stress_testing(100);  // Test with 100 concurrent clients

    return 0;
}
