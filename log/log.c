#include "log.h"
static char buf[BUFSZ];
static int fd;
static int pos;

int log_error(int level, char* fmt, ...) {
    va_list params;
    va_start(params, fmt);
    get_log_level(level);
    get_time();
    paste_pid();
    if ( vsnprintf(buf + pos, BUFSZ - pos, fmt, params ) < 0) {
        perror("vsnprintf");
        return -1;
    }
    if ( level == ERR ) {
        int check = sprintf(buf, "%s %s\n", buf, strerror(errno));
        if ( check < 0 ) {
            perror("sprintf log_error");
            return -1;
        }
    }
    if ( fd < 0 ) {
        log_init(NULL);
    }
    if ( write(fd, buf, BUFSZ) < 0 ) {
        perror("write buf to log");
        return -1;
    }
    if ( level == INFO || level == WARN ) {
        if (write(fd, "\n", 1) < 0) {
            perror("write \ in fd");
            return -1;
        }
    }
    pos = 0;
    for (int i = 0; i < BUFSZ; buf[i++] = 0);
    return 0;
}

int get_log_level(int level) {
    char* buffer = (char*) calloc(0, BUFSZ);
    if (level == INFO) {
        buffer = "INFO";
    }
    if (level == ERR) {
        buffer = "ERR";
    }
    if (level == WARN) {
        buffer = "WARN";
    }
    if (level < INFO || level > WARN) {
        perror("level < INFO || level > WARN");
        return -1;
    }
    int ret = sprintf(buf + pos, "[%s]", buffer);
    if (ret < 0) {
        perror("get_log_level sprintf");
        return -1;
    }
    pos += ret;
    return 0;
}

int log_init(char * path) {
    if ( path == NULL ) {
        fd = open(COMMON_PATH, O_WRONLY | O_CREAT | O_APPEND, 0666);
    }
    else {
        fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0666);
    }
    if (fd < 0) {
        perror("open");
        return -1;
    }
    return 0;
}

int get_time() {
    time_t rawtime;
    time(&rawtime);
    char * strtime = ctime(&rawtime);
    strtime[strlen(strtime) - 1] = 0;
    int ret = sprintf(buf + pos, "[%s]", strtime);
    if (ret < 0) {
        perror("get_time sprintf");
        return -1;
    }
    pos += ret;
    return 0;
}

int paste_pid() {
    int ret = sprintf(buf + pos, "[%d]", getpid());
    if (ret < 0) {
        perror("paste_pid");
        return -1;
    }
    pos += ret;
    return 0;
}
