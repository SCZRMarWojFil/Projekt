// g++ main.c -lrt

#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define QUEUE_NAME   "/example-queue-name"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE MAX_MSG_SIZE + 10

int main(int argc, char *argv[])
{
    pid_t cpid, w;
    int wstatus;

    mqd_t mq_descriptor;
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    /*
    On success, the PID of the child process is returned in the parent,
    and 0 is returned in the child.  On failure, -1 is returned in the
    parent, no child process is created, and errno is set appropriately.
    */
    cpid = fork();

    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    { /* Code executed by child */

        printf("Child PID is %ld\n", (long)getpid());

        mq_descriptor = mq_open (QUEUE_NAME, O_RDONLY);

        char in_buffer [MSG_BUFFER_SIZE];

        while(1){
            // get the oldest message with highest priority
            if (mq_receive (mq_descriptor, in_buffer, MSG_BUFFER_SIZE, NULL) == -1) {
                perror ("Server: mq_receive");
                exit (1);
            }

            printf ("Child: message received.\n");
            printf ("Message: %s.\n", in_buffer);
        }
    }
    else
    { /* Code executed by parent */

        printf("Parent PID is %ld\n", (long)getpid());

        mq_descriptor = mq_open (QUEUE_NAME, O_WRONLY | O_CREAT, QUEUE_PERMISSIONS, &attr);

        char out_buffer [MSG_BUFFER_SIZE];

        sprintf (out_buffer, "siemanko");

        while(1){
            // send message to child
            if (mq_send (mq_descriptor, out_buffer, strlen (out_buffer) + 1, 0) == -1) {
                perror ("Client: Not able to send message to server");
                continue;
            }

            printf ("Parent: message sent.\n");
            printf ("Message: %s.\n", out_buffer);

            sleep(5);
        }
        exit(EXIT_SUCCESS);
    }
}