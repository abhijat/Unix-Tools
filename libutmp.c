#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>

static int utmpfd;
static int rec_size = sizeof(struct utmp);
static int cur_rec;
static int nread;
static char utmp_buf[16 * sizeof(struct utmp)];

int utmp_open(const char* path)
{
    utmpfd = open(path, O_RDONLY);
    if (utmpfd == -1) return -1;
    return 0;
}

int utmp_reload()
{
    cur_rec = nread = 0;
    int rc = read(utmpfd, utmp_buf, sizeof(utmp_buf));
    return (rc / sizeof(struct utmp));
}

struct utmp* utmp_next()
{
    if (cur_rec == nread) {
	nread = utmp_reload();
        if (nread <= 0) return NULL;
    }
    struct utmp* u =
	(struct utmp*) &utmp_buf[cur_rec * rec_size];
    ++cur_rec;
    return u;
}

void utmp_close()
{
    close(utmpfd);
}
