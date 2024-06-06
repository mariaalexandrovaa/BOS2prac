#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "mysyslog.h"

void signal_handler(int sig) {
    switch (sig) {
        case SIGHUP:
            // Reload configuration
            break;
        case SIGTERM:
            // Terminate the daemon
            exit(0);
            break;
    }
}

void daemonize() {
    pid_t pid;

    // Fork off the parent process
    pid = fork();

    // If we got a good PID, then we can exit the parent process
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // Change the file mode mask
    umask(0);

    // Open any logs here

    // Create a new SID for the child process
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    // Change the current working directory
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    // Close out the standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main(int argc, char *argv[]) {
    daemonize();

    // Signal handling
    signal(SIGCHLD, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGHUP, signal_handler);
    signal(SIGTERM, signal_handler);

    // Daemon loop
    while (1) {
        mysyslog("Daemon is running...", INFO, 0, 0, "/var/log/mysyslog.log");
        sleep(60);
    }

    return EXIT_SUCCESS;
}
