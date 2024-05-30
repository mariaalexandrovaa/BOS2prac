#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include <mysyslog.h>

int main(int argc, char **argv) {
    int opt;
    char *message = NULL;
    int priority = LOG_INFO;
    char *driver = "stdout";
    char *format = "text";
    char *filename = NULL;

    while ((opt = getopt(argc, argv, "m:p:d:f:o:")) != -1) {
        switch (opt) {
            case 'm':
                message = optarg;
                break;
            case 'p':
                priority = atoi(optarg);
                break;
            case 'd':
                driver = optarg;
                break;
            case 'f':
                format = optarg;
                break;
            case 'o':
                filename = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -m <message> -p <priority> -d <driver> -f <format> -o <filename>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (!message) {
        fprintf(stderr, "Error: Missing message argument (-m).\n");
        exit(EXIT_FAILURE);
    }

    if (!driver) {
        fprintf(stderr, "Error: Missing driver argument (-d).\n");
        exit(EXIT_FAILURE);
    }

    if (!format) {
        fprintf(stderr, "Error: Missing format argument (-f).\n");
        exit(EXIT_FAILURE);
    }

    if (!filename) {
        filename = "stdout";
    }

    // Open the syslog connection
    mysyslog *slog = msyslog_open(driver, filename, format);
    if (!slog) {
        fprintf(stderr, "Error: Failed to open syslog connection.\n");
        exit(EXIT_FAILURE);
    }

    // Write the message to the syslog connection
    msyslog_log(slog, priority, "%s", message);

    // Close the syslog connection
    msyslog_close(slog);

    return EXIT_SUCCESS;
}
