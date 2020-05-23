/*
The following header file is included by both programs below.Its
primary purpose is to define a structure that will be imposed on the
memory object that is shared between the two programs.
*/

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define errExit(msg)        \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

#define BUF_SIZE 1024 /* Maximum size for exchanged string */

#define SHM_PATH "/myshm"

/* Define a structure that will be imposed on the shared
              memory object */

struct shmbuf
{
    sem_t sem1;         /* POSIX unnamed semaphore */
    sem_t sem2;         /* POSIX unnamed semaphore */
    size_t cnt;         /* Number of bytes used in 'buf' */
    char buf[BUF_SIZE]; /* Data being transferred */
};