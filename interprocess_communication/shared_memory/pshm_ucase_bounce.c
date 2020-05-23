/*
The programs below employ POSIX shared memory and POSIX unnamed
semaphores to exchange a piece of data.  The "bounce" program (which
must be run first) raises the case of a string that is placed into
the shared memory by the "send" program.  Once the data has been
modified, the "send" program then prints the contents of the modified
shared memory.  An example execution of the two programs is the
following:

    $ ./pshm_ucase_bounce /myshm &
    [1] 270171
    $ ./pshm_ucase_send /myshm hello
    HELLO
*/
/*
The "bounce" program creates a new shared memory object with the name
given in its command-line argument and sizes the object to match the
size of the shmbuf structure defined in the header file.  It then
maps the object into the process's address space, and initializes two
POSIX semaphores inside the object to 0.

After the "send" program has posted the first of the semaphores, the
"bounce" program upper cases the data that has been placed in the
memory by the "send" program and then posts the second semaphore to
tell the "send" program that it may now access the shared memory.
*/

//g++ pshm_ucase_bounce.c pshm_ucase.h -lpthread -lrt -fpermissive -o pshm_ucase_bounce

#include <ctype.h>
#include "pshm_ucase.h"

int main(int argc, char *argv[])
{
    // I've used predefined pathname for shm
    // if (argc != 2)
    // {
    //     fprintf(stderr, "Usage: %s /shm-path\n", argv[0]);
    //     exit(EXIT_FAILURE);
    // }

    // char *shmpath = argv[1];

    /* Create shared memory object and set its size to the size
                  of our structure */

    int fd = shm_open(SHM_PATH, O_CREAT | O_EXCL | O_RDWR,
                      S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("shm_open");

    // Truncate file to size of theproper structure
    if (ftruncate(fd, sizeof(struct shmbuf)) == -1)
        errExit("ftruncate");

    /* Map the object into the caller's address space */

    struct shmbuf *shmp = mmap(NULL, sizeof(struct shmbuf),
                               PROT_READ | PROT_WRITE,
                               MAP_SHARED, fd, 0);
    if (shmp == MAP_FAILED)
        errExit("mmap");

    /* Initialize semaphores as process-shared, with value 0 */

    if (sem_init(&shmp->sem1, 1, 0) == -1)
        errExit("sem_init-sem1");
    if (sem_init(&shmp->sem2, 1, 0) == -1)
        errExit("sem_init-sem2");

    /* Wait for 'sem1' to be posted by peer before touching
                  shared memory */

    if (sem_wait(&shmp->sem1) == -1)
        errExit("sem_wait");

    /* Convert data in shared memory into upper case */

    for (int j = 0; j < shmp->cnt; j++)
        shmp->buf[j] = toupper((unsigned char)shmp->buf[j]);

    /* Post 'sem2' to tell the to tell peer that it can now
                  access the modified data in shared memory */

    if (sem_post(&shmp->sem2) == -1)
        errExit("sem_post");

    /* Unlink the shared memory object. Even if the peer process
                  is still using the object, this is okay. The object will
                  be removed only after all open references are closed. */

    shm_unlink(SHM_PATH);

    exit(EXIT_SUCCESS);
}
