typedef struct {
    char** list;
    int n_history_list;
} HistoryList;

void add_history(char* new_element, HistoryList* history_list) {
    if (history_list->list == NULL) {
        history_list->list = (char**) malloc(sizeof(char*));
        history_list->list[0] = (char*) malloc((strlen(new_element) + 1) * sizeof(char));
        strcpy(history_list->list[0], new_element);
    } else {
        if (strcmp(new_element, history_list->list[history_list->n_history_list - 1])) {
            history_list->list = realloc(history_list->list, (history_list->n_history_list + 1) * sizeof(char*));
            history_list->list[history_list->n_history_list] = (char*) malloc((strlen(new_element) + 1) * sizeof(char));
            strcpy(history_list->list[history_list->n_history_list], new_element);
        } else {
            return; // If the current input is the same as the immediately previous input.
        }
    }
    history_list->n_history_list++;
}

void destroy_history(HistoryList* history_list) {
    if (history_list == NULL) {
        return;
    }
    for (int i = 0; i < history_list->n_history_list; i++) {
        if (history_list->list[i] != NULL) {
            free(history_list->list[i]);
            history_list->list[i] = NULL;
        }
    }
    if (history_list->list != NULL) {
        free(history_list->list);
        history_list->list = NULL;
    }
}

void print_history_list(HistoryList* history_list) {
    for (int i = 0; i < history_list->n_history_list; i++) {
        printf("%d: %s\n", i + 1, history_list->list[i]);
    }
}

HistoryList history_list = {NULL, 0};