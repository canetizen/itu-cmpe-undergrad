/**
 * BLG 312E Project 1
 * @author Mustafa Can Caliskan, 150200097
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <sys/wait.h>
#include "history.h"

#define MAX_COMMAND_SIZE 250

// Colors
#define COLOR_RED "\033[31m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_RESET "\033[0m"

void init_shell();
void print_directory();

bool clean_input(char*);
char** input_character_parser(const char*, const char*);
void trim_string(char*);
bool read_input(char*, int, FILE*);
void handle_input(char*);

void execute_command(char**);
void execute_piped_command(char** ,char**);
void execute_concurrent_command(char**);
void execute_mixed(char**, char**);

bool is_built_in(char*);
void execute_built_in(char**);
void change_directory(char**);
void print_help();

void batch_mode(char*); 

void destroy_handled_input(char**);
int n_of_distinct_commands(char**);

int main() {
    init_shell();
    char input_buffer[MAX_COMMAND_SIZE + 1] = "";
    while (1) {
        print_directory();
        read_input(input_buffer, MAX_COMMAND_SIZE + 1, stdin);
        if (clean_input(input_buffer)) {
            add_history(input_buffer, &history_list);
            handle_input(input_buffer);
        }
    }
    destroy_history(&history_list);
    return EXIT_FAILURE;
}

/**
 * It reads data from the desired source (stdin or a file).
 * @param buffer The buffer string where the command is stored.
*/
bool read_input(char* buffer, int max_size_buffer, FILE* stream) {
    memset(buffer, '\0', MAX_COMMAND_SIZE);
    if (fgets(buffer, max_size_buffer, stream) == NULL) { // It is assumed that the last line of the read file is empty.
        return false;
    }
    return true;
}

/**
 * Removes the trailing newline character from the command and calls related trim_string function.
*/
bool clean_input(char* raw_input) {
    if (raw_input != NULL) {
        raw_input[strlen(raw_input) - 1] = '\0';
        if (strlen(raw_input) == 0) { // Empty input
            return false;
        }
        trim_string(raw_input);
        return true;    
    } else {
        fprintf(stderr, COLOR_RED "Error:" COLOR_RESET " Input read error. Shell terminated.\n");
        destroy_history(&history_list);
        exit(EXIT_FAILURE);
    }
    return false;
}

/**
 * It reads commands from the provided script file in.
 * @param input_file The name of the script file to be opened.
*/
void batch_mode(char* input_file) {
    FILE *fileptr;
    char line[MAX_COMMAND_SIZE + 1] = "";

    fileptr = fopen(input_file, "r");

    if (fileptr == NULL) {
        fprintf(stderr, COLOR_RED "Error:" COLOR_RESET " Script file does not found.\n");
        return;
    }

    while (read_input(line, MAX_COMMAND_SIZE + 1, fileptr)) {
        if (clean_input(line)) {
            printf("\nCommand: %s\n", line);
            add_history(line, &history_list);
            handle_input(line);
        }
    }
    
    fclose(fileptr);
}

/**
 * It parses the command received as a parameter and invokes the necessary functions.
 * @param raw_input The command parsed from unnecessary whitespace.
*/
void handle_input(char* raw_input) {
    bool comma_flag = false, pipe_flag = false;

    if (strchr(raw_input, ';') != NULL) {
        comma_flag = true;
    }

    if (strchr(raw_input, '|') != NULL) {
        pipe_flag = true;
    }

    if (pipe_flag && comma_flag) { // It is assumed that the command contains only one '|' (It may contain multiple ';').
        char** parsed_pipe = input_character_parser(raw_input, "|");
        char** parsed_comma_left_pipe = input_character_parser(parsed_pipe[0], ";");
        char** parsed_comma_right_pipe = input_character_parser(parsed_pipe[1], ";");

        execute_mixed(parsed_comma_left_pipe, parsed_comma_right_pipe);
        destroy_handled_input(parsed_pipe);
        destroy_handled_input(parsed_comma_left_pipe);
        destroy_handled_input(parsed_comma_right_pipe);
    } else if (pipe_flag) { // It is assumed that the command contains only one '|'
        char** parsed_pipe = input_character_parser(raw_input, "|");
        char** parsed_pipe_left = input_character_parser(parsed_pipe[0], " ");
        char** parsed_pipe_right = input_character_parser(parsed_pipe[1], " ");
        execute_piped_command(parsed_pipe_left, parsed_pipe_right);
        destroy_handled_input(parsed_pipe_left);
        destroy_handled_input(parsed_pipe_right);
        destroy_handled_input(parsed_pipe);
    } else if (comma_flag) {
        char** parsed_comma = input_character_parser(raw_input, ";");
        execute_concurrent_command(parsed_comma);
        destroy_handled_input(parsed_comma);
    } else {
        char** space_parsed = input_character_parser(raw_input, " ");
        execute_command(space_parsed);
        destroy_handled_input(space_parsed);
    }
}

/**
 * It executes commands specific to the shell itself.
 * @param handled_input Built-in command.
*/
void execute_built_in(char** handled_input) {
    if (!strcmp(handled_input[0], "quit")) {
        destroy_handled_input(handled_input);
        destroy_history(&history_list);
        exit(EXIT_SUCCESS);
    }
    if (!strcmp(handled_input[0], "help")) {
        print_help();
        return;
    }
    if (!strcmp(handled_input[0], "cd")) {
        change_directory(handled_input);
        return;
    }
    if (!strcmp(handled_input[0], "history")) {
        print_history_list(&history_list);
        return;
    }

    if (!strcmp(handled_input[0], "batchmode")) {
        if (handled_input[1] == NULL) {
            fprintf(stderr, COLOR_RED "Error:" COLOR_RESET " File could not be found.\n");
        } else if(handled_input[2] != NULL) {
            fprintf(stderr, COLOR_RED "Error:" COLOR_RESET " Please input only one script file to execute.\n");
        } else {
            batch_mode(handled_input[1]);
        }
    }
}

/**
 * It executes commands from the user in the shell that do not contain any symbols.
 * @param handled_input Single command.
*/
void execute_command(char** handled_input) {
    if (is_built_in(handled_input[0])) {
        execute_built_in(handled_input);
    } else {
        pid_t pid = fork();
        if (pid == -1) {
            perror(COLOR_RED "Fork failed." COLOR_RESET);
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            execvp(handled_input[0], handled_input);
            perror(COLOR_RED "Error:" COLOR_RESET);
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, NULL, 0);
        } 
    }
}

/**
 * It executes parsed commands that need to be processed simultaneously.
 * @param parsed_comma Parsed concurrent commands.
*/
void execute_concurrent_command(char** parsed_comma) {
    int n_of_commands = n_of_distinct_commands(parsed_comma);
    bool quit_flag = false;
    pid_t* pid_array = (pid_t*) malloc(n_of_commands * sizeof(pid_t)); // The number of forks must be equal to the n_of_commands
    char** space_parsed = NULL;
    for (int i = 0; i < n_of_commands; i++) {
        space_parsed = input_character_parser(parsed_comma[i], " ");
        if (!is_built_in(parsed_comma[i])) {
            pid_array[i] = fork();
            if (pid_array[i] < 0) {
                perror(COLOR_RED "Error:" COLOR_RESET);
                exit(EXIT_FAILURE);
            } else if (pid_array[i] == 0) {
                execvp(space_parsed[0], space_parsed);
                perror(COLOR_RED "Execution of the concurrent command failed:" COLOR_RESET);
                exit(EXIT_FAILURE);
            }
        } else {
            if (!strcmp(space_parsed[0], "quit")) {
                quit_flag = true;
            } else {
                execute_built_in(space_parsed);
            }
        }
        if (space_parsed != NULL) {
            destroy_handled_input(space_parsed);
        }
    }

    for (int i = 0; i < n_of_commands; i++) {
        waitpid(pid_array[i], NULL, 0);
    }

    free(pid_array);

    if (quit_flag) {
        destroy_history(&history_list);
        exit(EXIT_SUCCESS);
    }
}


/**
 * It executes processed commands that need to be run as a pipe.
 * @param parsed_command_first First pipe command (left side of the pipe)
 * @param parsed_command_second Second pipe command (right side of the pipe)
*/
void execute_piped_command(char** parsed_command_first, char** parsed_command_second) {
    int pipefd[2];
    pid_t pid1, pid2;

    if (is_built_in(parsed_command_first[0]) || is_built_in(parsed_command_second[0])) {
        fprintf(stderr, COLOR_RED "Error:" COLOR_RESET " The pipe operation cannot be used with built-in functions.\n");
        return;
    }

    if (pipe(pipefd) == -1) {
        perror(COLOR_RED "Pipe failed." COLOR_RESET);
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 < 0) {
        perror(COLOR_RED "Fork failed." COLOR_RESET);
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execvp(parsed_command_first[0], parsed_command_first);
        perror(COLOR_RED "Execution of the first piped command failed:" COLOR_RESET);
        exit(EXIT_FAILURE);
    } else {
        waitpid(pid1, NULL, 0);
        pid2 = fork();
        if (pid2 < 0) {
            perror(COLOR_RED "Fork failed." COLOR_RESET);
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            close(pipefd[0]);
            execvp(parsed_command_second[0], parsed_command_second);
            perror(COLOR_RED "Execution of the second piped command failed:" COLOR_RESET);
            exit(EXIT_FAILURE);
        } else {
            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(pid2, NULL, 0);
        }
    }
}


/**
 * It counts the number of strings in the string array.
 * @param input String array
 * @return The number of strings
*/
int n_of_distinct_commands(char** input) {
    int i = 0;
    while(input[i] != NULL) {
        i++;
    }  
    return i;
}

/**
 * It executes commands containing multiple ';' and '|' symbols.
 * @param parsed_comma_left_pipe The segment on the left side of the pipe.
 * @param parsed_comma_right_pipe The segment on the right side of the pipe.
*/
void execute_mixed(char** parsed_comma_left_pipe, char** parsed_comma_right_pipe) {
    int i = 0;
    int pid_count = (n_of_distinct_commands(parsed_comma_left_pipe) * n_of_distinct_commands(parsed_comma_right_pipe));
    pid_t* pid_array = (pid_t*) malloc(pid_count * sizeof(pid_t));
    int pid_index = 0;
    while (parsed_comma_left_pipe[i] != NULL) {
        int j = 0;
        while (parsed_comma_right_pipe[j] != NULL) {
            pid_array[pid_index] = fork();
            if (pid_array[pid_index] < 0) {
                perror(COLOR_RED "Error:" COLOR_RESET);
                exit(EXIT_FAILURE);
            } else if (pid_array[pid_index] == 0) {
                char** space_parsed_left = input_character_parser(parsed_comma_left_pipe[i], " ");
                char** space_parsed_right = input_character_parser(parsed_comma_right_pipe[j], " ");
                execute_piped_command(space_parsed_left, space_parsed_right);
                destroy_handled_input(space_parsed_left);
                destroy_handled_input(parsed_comma_right_pipe);
                exit(EXIT_SUCCESS);
            } else {
                pid_index++;
                j++;
            }
        }
        i++;        
    }

    for (int i = 0; i < pid_count; i++) {
        waitpid(pid_array[i], NULL, 0);
    }

    free(pid_array);
}

/**
 * It returns whether a command is built-in or not.
*/
bool is_built_in(char* handled_input) {
    return (!strcmp(handled_input, "quit") 
    || !strcmp(handled_input, "cd") 
    || !strcmp(handled_input, "help") 
    || !strcmp(handled_input, "history") 
    || !strcmp(handled_input, "batchmode"));
}

/**
 * It splits the input string according to the given delimiter and generates new strings.
*/
char** input_character_parser(const char* input, const char* delim) {

    char** segments = NULL;
    char* temp_char = (char*) malloc((strlen(input) + 1) * sizeof(char));
    strcpy(temp_char, input);
    char* token = strtok(temp_char, delim);
    int count = 0;

    while (token != NULL) {
        segments = realloc(segments, (count + 1) * sizeof(char*));
        trim_string(token);
        segments[count] = malloc(strlen(token) + 1);
        strcpy(segments[count], token);
        count++;
        token = strtok(NULL, delim);
    }

    segments = realloc(segments, (count + 1) * sizeof(char*));
    segments[count] = NULL;
    free(token);
    free(temp_char);
    return segments;
}

/**
 * It formats the beginning, end, and spaces between command and its flags. 
 * In other words, '  batchmode     example.sh ' becomes 'batchmode example.sh'.
*/
void trim_string(char* string) {
    int length = strlen(string);
    int i, j;
    bool space = false;

    if (string[0] == ' ') // Check if the first character is a space
        space = true;

    j = 0;
    for (i = 0; i < length; i++) {
        if (string[i] != ' ') {
            string[j++] = string[i];
            space = false;
        } else if (string[i] == ' ' && !space) {
            string[j++] = ' ';
            space = true;
        }
    }
    
    // Remove trailing spaces
    while (j > 0 && string[j - 1] == ' ') {
        j--;
    }

    string[j] = '\0'; // Null terminate the string
}

void change_directory(char** handled_input) {
    if(handled_input[1] == NULL) {
        chdir(getenv("HOME"));
    } else {
        if(chdir(handled_input[1])) {
            perror(COLOR_RED "Error" COLOR_RESET);
        }
    }
}



/**
 * It frees handled and executed commands and each individual string they contain.
*/
void destroy_handled_input(char** handled_input) {
    if (handled_input == NULL) {
        return;
    }

    if (handled_input != NULL) {
        for (int i = 0; handled_input[i] != NULL; i++) {
            free(handled_input[i]);
            handled_input[i] = NULL;
        }

        free(handled_input);
        handled_input = NULL;
    }
}

void print_help() {
    printf("shelletizen command-line shell by Mustafa Can Caliskan\n"); 
    printf("version 1.0.0\n");
    printf("To enable batch mode, type 'batchmode example.sh'.\n");
    printf("To see history, type 'history'.\n");
    printf("To terminate shell, type 'quit'.\n");
}

void print_directory() { 
    char current_dir[1024]; 
    getcwd(current_dir, sizeof(current_dir));
    char* username = getenv("USER"); 
    printf(COLOR_MAGENTA "%s" COLOR_RESET " in " COLOR_CYAN "%s" COLOR_RESET ">> ", username, current_dir);
} 

void init_shell() { 
    system("clear");

    // Shelletizen ascii art
    printf(COLOR_CYAN "      _          _ _      _   _               \n" COLOR_RESET); 
    printf(COLOR_CYAN "     | |        | | |    | | (_)              \n" COLOR_RESET);
    printf(COLOR_CYAN "  ___| |__   ___| | | ___| |_ _ _______ _ __  \n" COLOR_RESET);
    printf(COLOR_CYAN " / __| '_ \\ / _ \\ | |/ _ \\ __| |_  / _ \\ '_ \\ \n" COLOR_RESET);
    printf(COLOR_CYAN " \\__ \\ | | |  __/ | |  __/ |_| |/ /  __/ | | |\n" COLOR_RESET);
    printf(COLOR_CYAN " |___/_| |_|\\___|_|_|\\___|\\__|_/___\\___|_| |_|\n" COLOR_RESET);

    printf("\nTo get help, type 'help'.\n\n");
}
