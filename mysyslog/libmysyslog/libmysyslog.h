#ifndef MYSYSLOG_H
#define MYSYSLOG_H

#define DEBUG 0
#define INFO 1
#define WARN 2
#define ERROR 3
#define CRITICAL 4

int mysyslog(const char* msg, int level, int driver, int format, const char* path);

#endif // MYSYSLOG_H
