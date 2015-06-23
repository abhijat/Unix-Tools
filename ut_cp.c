#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 4096
#define COPYMODE 0644

void err(const char*, const char*);

int main(int argc, char* argv[])
{
    if (argc != 3) {
        exit(1);
    }

    int infd = open(argv[1], O_RDONLY);
    if (infd == -1) {
        err("Cannot open", argv[1]);
        exit(1);
    }

    int outfd = creat(argv[2], COPYMODE);
    if (outfd == -1) {
        err("Cannot create", argv[2]);
        exit(1);
    }

    int nread;
    char buf[BUFSIZE];
    while ( (nread = read(infd, buf, sizeof(buf))) > 0) {
        if (write(outfd, buf, nread) != nread) {
            err("Write error", argv[2]);
        }
    }

    if (nread == -1) {
        err("Read error from", argv[1]);
    }

    close(infd);
    close(outfd);
}

void err(const char* s1, const char* s2)
{
    fprintf(stderr, "Error: %s", s1);
    perror(s2);
    exit(1);
}


