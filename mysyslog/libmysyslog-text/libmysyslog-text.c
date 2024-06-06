#include "libmysyslog-text.h"
#include <time.h>

int mysyslog_text(const char* msg, int level, const char* path) {
    FILE* file = fopen(path, "a");
    if (file == NULL) {
        return -1;
    }

    time_t timestamp = time(NULL);
    char* log_level = "UNKNOWN";
    switch (level) {
        case DEBUG:
            log_level = "DEBUG";
            break;
        case INFO:
            log_level = "INFO";
            break;
        case WARN:
            log_level = "WARN";
            break;
        case ERROR:
            log_level = "ERROR";
            break;
        case CRITICAL:
            log_level = "CRITICAL";
            break;
    }

    char* process = "libmysyslog-client"; // По умолчанию процесс называется mysyslog-client

    fprintf(file, "%ld %s %s %s", timestamp, log_level, process, msg);
    fprintf(file, "\n");
    fclose(file);

    return 0;
}
