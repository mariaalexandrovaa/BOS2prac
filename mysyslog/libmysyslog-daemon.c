#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "libmysyslog.h"

// Обработчик сигнала для обработки сигналов SIGHUP и SIGTERM
void signal_handler(int sig) {
    switch (sig) {
        case SIGHUP:
            // Перезагрузить конфигурацию
            break;
        case SIGTERM:
            // Завершить работу демона
            exit(0);
            break;
    }
}

// Функция для перевода процесса в режим демона
void daemonize() {
    pid_t pid;

    // Создать новый процесс путем форка
    pid = fork();

    // Если форк прошел успешно, то в родительском процессе можно завершить работу
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // Изменить маску прав доступа для создаваемых файлов
    umask(0);

    // Открыть необходимые логи

    // Создать новый сеанс для дочернего процесса
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }

    // Изменить текущий рабочий каталог
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    // Закрыть стандартные дескрипторы файлов
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main(int argc, char *argv[]) {
    // Перевести процесс в режим демона
    daemonize();

    // Обработка сигналов
    signal(SIGCHLD, SIG_IGN); // Игнорировать сигнал SIGCHLD
    signal(SIGTSTP, SIG_IGN); // Игнорировать сигнал SIGTSTP
    signal(SIGTTOU, SIG_IGN); // Игнорировать сигнал SIGTTOU
    signal(SIGTTIN, SIG_IGN); // Игнорировать сигнал SIGTTIN
    signal(SIGHUP, signal_handler); // Установить обработчик сигнала для SIGHUP
    signal(SIGTERM, signal_handler); // Установить обработчик сигнала для SIGTERM

    // Цикл демона
    while (1) {
        // Вывести сообщение журнала в файл /var/log/mysyslog.log
        mysyslog("Daemon is running...", INFO, 0, 0, "/var/log/mysyslog.log");
        sleep(60); // Ожидать 60 секунд перед выводом следующего сообщения журнала
    }

    return EXIT_SUCCESS;
}
