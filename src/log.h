#ifndef LOG_H
#define LOG_H

#include <stdio.h>

// Initializes the logging system. Opens the log file.
void init_log(const char *filename);

// Logs a move
void log_move(const char *move);

// Closes the log file
void close_log(void);

#endif
