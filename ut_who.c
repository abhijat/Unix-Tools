#include <utmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

void show_time(time_t);

void show_info(const struct utmp* u)
{
    printf("%-8.8s", u->ut_name);
    printf(" ");
    printf("%-8.8s", u->ut_line);
    printf(" ");
    show_time(u->ut_time);
    printf(" ");
    printf("(%s)", u->ut_host);

    printf("\n");
}

void show_time(time_t t)
{
    char* t_str = ctime(&t);
    t_str[strlen(t_str)-1] = 0;
    printf("%s", t_str);
}

int main()
{
    int utmp_fd;
    if ( (utmp_fd = open(UTMP_FILE, O_RDONLY)) == -1 ) {
        perror(UTMP_FILE);
        exit(1);
    }

    struct utmp curr;
    size_t rec_len = sizeof(curr);
    while (read(utmp_fd, &curr, rec_len) == rec_len) {
        if (curr.ut_type == LOGIN_PROCESS)
            show_info(&curr);
    }

    return 0;
}
