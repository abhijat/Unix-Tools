#include <utmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void show_info(const struct utmp* u)
{
    printf("%-8.8s", u->ut_name);
    printf(" ");
    printf("%-8.8s", u->ut_line);
    printf(" ");
    printf("%11d", u->ut_time);
    printf(" ");
    printf("(%s)", u->ut_host);

    printf("\n");
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
