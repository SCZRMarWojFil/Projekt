/*
The "send" program takes two command - line arguments : the pathname of
a shared memory object previously created by the "bounce" program and
a string that is to be copied into that object.

The program opens the shared memory object and maps the object into
its address space.It then copies the data specified in its second
argument into the shared memory,
and posts the first semaphore, which tells the "bounce" program that it can now access that data.After the "bounce" program posts the second semaphore, the "send" program prints the contents of the shared memory on standard output.
*/

//g++ pshm_ucase_send.c pshm_ucase.h -lpthread -lrt -fpermissive -o pshm_ucase_send

#include <string.h>
#include "pshm_ucase.h"

int main(int argc, char *argv[])
{
    // if (argc != 3)
    // {
    //     fprintf(stderr, "Usage: %s /shm-path string\n", argv[0]);
    //     exit(EXIT_FAILURE);
    // }

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s string\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // char *shmpath = argv[1];
    // char *string = argv[2];
    char *string = argv[1];
    size_t len = strlen(string);

    if (len > BUF_SIZE)
    {
        fprintf(stderr, "String is too long\n");
        exit(EXIT_FAILURE);
    }

    /* Open the existing shared memory object and map it
                  into the caller's address space */

    int fd = shm_open(SHM_PATH, O_RDWR, 0);
    if (fd == -1)
        errExit("shm_open");

    struct shmbuf *shmp = mmap(NULL, sizeof(struct shmbuf),
                               PROT_READ | PROT_WRITE,
                               MAP_SHARED, fd, 0);
    if (shmp == MAP_FAILED)
        errExit("mmap");

    /* Copy data into the shared memory object */

    shmp->cnt = len;
    memcpy(&shmp->buf, string, len);

    /* Tell peer that it can now access shared memory */

    if (sem_post(&shmp->sem1) == -1)
        errExit("sem_post");

    /* Wait until peer says that it has finished accessing
                  the shared memory */

    if (sem_wait(&shmp->sem2) == -1)
        errExit("sem_wait");

    /* Write modified data in shared memory to standard output */

    write(STDOUT_FILENO, &shmp->buf, len);
    write(STDOUT_FILENO, "\n", 1);

    exit(EXIT_SUCCESS);
}