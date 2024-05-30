#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define DEBUG 7
#define INFO 6
#define WARN 4
#define ERROR 3
#define CRITICAL 2

typedef int (*format_func)(FILE *stream, const char *msg, int level);

int text_format(FILE *stream, const char *msg, int level) {
    fprintf(stream, "%s: %s\n", level_strings[level], msg);
    return 0;
}

int json_format(FILE *stream, const char *msg, int level) {
    fprintf(stream, "{\"level\": \"%s\", \"message\": \"%s\"}\n", level_strings[level], msg);
    return 0;
}

int csv_format(FILE *stream, const char *msg, int level) {
    fprintf(stream, "%s,%s\n", level_strings[level], msg);
    return 0;
}

typedef struct {
    const char *name;
    format_func func;
} format_driver;

format_driver format_drivers[] = {
    {"text", text_format},
    {"json", json_format},
    {"csv", csv_format},
};

int mysyslog(const char *msg, int level, int driver, int format, const char *path) {
    if (driver < 0 || driver >= NUM_DRIVERS) {
        return -1;
    }

    if (format < 0 || format >= NUM_FORMATS) {
        return -1;
    }

    FILE *stream = fopen(path, "a");
    if (!stream) {
        return -1;
    }

    format_func format_func = format_drivers[format].func;
    format_func(stream, msg, level);

    fclose(stream);

    return 0;
}
