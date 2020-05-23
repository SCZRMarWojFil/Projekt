#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/select.h>
#include <termios.h>
#include <stropts.h>
#include <sys/ioctl.h>

#include <string.h>

// Replacement of kbhit from conio.h on windows
int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

// Handling errors
#define errExit(msg)        \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

// Predefinied sizes of images
#define IMG_WIDTH 1280
#define IMG_HEIGHT 853

// Pathname of shm
#define SHM_PATH "/myshm"

// Definition of a structure that will be imposed on the shared memory object
struct shmbuf
{
    sem_t sem1;         /* POSIX unnamed semaphore */
    sem_t sem2;         /* POSIX unnamed semaphore */
    cv::Vec3b img_data[IMG_HEIGHT][IMG_WIDTH]; /* Data being transferred */
};