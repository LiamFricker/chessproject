#include "log.h"

static FILE *log_file = NULL;

void init_log(const char *filename) {
    log_file = fopen(filename, "a"); // Append mode
    if (log_file == NULL) {
        perror("Failed to open log file");
        return;
    }
    fprintf(log_file, "Starting new game\n");
}

void log_move(const char *move) {
    if (log_file != NULL) {
        fprintf(log_file, "Move: %s\n", move);
        fflush(log_file); // Flush after every write
    }
}

void close_log(void) {
    if (log_file != NULL) {
        fprintf(log_file, "Game over\n");
        fclose(log_file);
        log_file = NULL;
    }
}