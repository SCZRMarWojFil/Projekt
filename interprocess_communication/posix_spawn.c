/*
The program below demonstrates the use of various functions in the
POSIX spawn API.  The program accepts command-line attributes that
can be used to create file actions and attributes objects.  The
remaining command-line arguments are used as the executable name and
command-line arguments of the program that is executed in the child.

In the first run, the date(1) command is executed in the child, and
the posix_spawn() call employs no file actions or attributes objects.

    $ ./a.out date
    PID of child: 7634
    Tue Feb  1 19:47:50 CEST 2011
    Child status: exited, status=0

In the next run, the -c command-line option is used to create a file
actions object that closes standard output in the child.  Conse‐
quently, date(1) fails when trying to perform output and exits with a
status of 1.

    $ ./a.out -c date
    PID of child: 7636
    date: write error: Bad file descriptor
    Child status: exited, status=1

In the next run, the -s command-line option is used to create an
attributes object that specifies that all (blockable) signals in the
child should be blocked.  Consequently, trying to kill child with the
default signal sent by kill(1) (i.e., SIGTERM) fails, because that
signal is blocked.  Therefore, to kill the child, SIGKILL is neces‐
sary (SIGKILL can't be blocked).

    $ ./a.out -s sleep 60 &
    [1] 7637
    $ PID of child: 7638

    $ kill 7638
    $ kill -KILL 7638
    $ Child status: killed by signal 9
    [1]+  Done                    ./a.out -s sleep 60

When we try to execute a nonexistent command in the child, the
exec(3) fails and the child exits with a status of 127.

    $ ./a.out xxxxx
    PID of child: 10190
    Child status: exited, status=127
*/

#include <spawn.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <errno.h>

#define errExit(msg)        \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

#define errExitEN(en, msg)  \
    do                      \
    {                       \
        errno = en;         \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

char **environ;

int main(int argc, char *argv[])
{
    pid_t child_pid;
    int s, opt, status;
    sigset_t mask;
    posix_spawnattr_t attr;
    posix_spawnattr_t *attrp;
    posix_spawn_file_actions_t file_actions;
    posix_spawn_file_actions_t *file_actionsp;

    /* Parse command-line options, which can be used to specify an
              attributes object and file actions object for the child. */

    attrp = NULL;
    file_actionsp = NULL;

    while ((opt = getopt(argc, argv, "sc")) != -1)
    {
        switch (opt)
        {
        case 'c': /* -c: close standard output in child */

            /* Create a file actions object and add a "close"
                      action to it */

            s = posix_spawn_file_actions_init(&file_actions);
            if (s != 0)
                errExitEN(s, "posix_spawn_file_actions_init");

            s = posix_spawn_file_actions_addclose(&file_actions,
                                                  STDOUT_FILENO);
            if (s != 0)
                errExitEN(s, "posix_spawn_file_actions_addclose");

            file_actionsp = &file_actions;
            break;

        case 's': /* -s: block all signals in child */

            /* Create an attributes object and add a "set signal mask"
                      action to it */

            s = posix_spawnattr_init(&attr);
            if (s != 0)
                errExitEN(s, "posix_spawnattr_init");
            s = posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETSIGMASK);
            if (s != 0)
                errExitEN(s, "posix_spawnattr_setflags");

            sigfillset(&mask);
            s = posix_spawnattr_setsigmask(&attr, &mask);
            if (s != 0)
                errExitEN(s, "posix_spawnattr_setsigmask");

            attrp = &attr;
            break;
        }
    }

    /* Spawn the child. The name of the program to execute and the
              command-line arguments are taken from the command-line arguments
              of this program. The environment of the program execed in the
              child is made the same as the parent's environment. */

    s = posix_spawnp(&child_pid, argv[optind], file_actionsp, attrp,
                     &argv[optind], environ);
    if (s != 0)
        errExitEN(s, "posix_spawn");

    /* Destroy any objects that we created earlier */

    if (attrp != NULL)
    {
        s = posix_spawnattr_destroy(attrp);
        if (s != 0)
            errExitEN(s, "posix_spawnattr_destroy");
    }

    if (file_actionsp != NULL)
    {
        s = posix_spawn_file_actions_destroy(file_actionsp);
        if (s != 0)
            errExitEN(s, "posix_spawn_file_actions_destroy");
    }

    printf("PID of child: %ld\n", (long)child_pid);

    /* Monitor status of the child until it terminates */

    do
    {
        s = waitpid(child_pid, &status, WUNTRACED | WCONTINUED);
        if (s == -1)
            errExit("waitpid");

        printf("Child status: ");
        if (WIFEXITED(status))
        {
            printf("exited, status=%d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("killed by signal %d\n", WTERMSIG(status));
        }
        else if (WIFSTOPPED(status))
        {
            printf("stopped by signal %d\n", WSTOPSIG(status));
        }
        else if (WIFCONTINUED(status))
        {
            printf("continued\n");
        }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));

    exit(EXIT_SUCCESS);
}
