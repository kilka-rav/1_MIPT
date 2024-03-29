#include <stdio.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <errno.h>
#include <stdarg.h>

#define BUFSZ 4096
#define INFO 0
#define ERR  1
#define WARN 2
#define COMMON_PATH "test.log"

#define pr_err(variables, ...)  log_error(ERR , "[%s:%d] " variables, __FILE__, __LINE__, ##__VA_ARGS__);
#define pr_info(variables, ...) log_error(INFO, "[%s:%d] " variables, __FILE__, __LINE__, ##__VA_ARGS__);
#define pr_warn(variables, ...) log_error(WARN, "[%s:%d] " variables, __FILE__, __LINE__, ##__VA_ARGS__);

int get_log_level(int level);
int log_init(char * path);
int get_time();
int paste_pid();
int log_error(int level, char* variables, ...);

