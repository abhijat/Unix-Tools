#include <utmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

void show_time(time_t);
int utmp_open(const char*);
void utmp_reload();
struct utmp* utmp_next();
void utmp_close();

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
    if (utmp_open(UTMP_FILE) == -1)
        exit(1);
    struct utmp* u;
    while ( (u = utmp_next()) != NULL)
	if (u->ut_type == LOGIN_PROCESS)
	    show_info(u);
    return 0;
}
