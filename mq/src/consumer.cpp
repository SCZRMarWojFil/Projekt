#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <errno.h>
#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <chrono>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../include/common.h"
#include "../include/structures.h"

using namespace cv;
using namespace std;
using namespace chrono;


int main(int argc, char **argv)
{
    rlimit limits;
    limits.rlim_max = QUEUE_SIZE_CEILING;
    limits.rlim_cur = MAX_QUEUE_SIZE;
    CHECK(setrlimit(RLIMIT_MSGQUEUE, &limits) != -1);

    int res = getrlimit(RLIMIT_MSGQUEUE,  &limits);

    printf("rlim_cur: %lu  rlim_max: %lu\n", limits.rlim_cur, limits.rlim_max);


    mqd_t mq;
    struct mq_attr attr;
    msg_buffer msg_in;

    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MSGS;
    attr.mq_msgsize = sizeof(msg_in);
    attr.mq_curmsgs = 0;

    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0666, &attr);
    if((mqd_t)-1 == mq)
    {
        cout << "Meesage queue with given name doesn't exist.\nSpawn producer first\n";
        return -1;
    }

    int receive_code = mq_receive(mq, (char *) &msg_in, sizeof(msg_in)+1, NULL);
    cout << "bytes received: " << receive_code << endl;
    CHECK((mqd_t)-1 != receive_code);

    cout << " struct received: byte_total_size: " << msg_in.total_size << endl;

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    //Mat img_received(buf.rows, buf.cols, buf.type);
   // Size img_size(msg_in.cols, i_in.rows)
    Mat img_received(msg_in.rows, msg_in.cols, msg_in.cv_type);
    memcpy(img_received.data, msg_in.image_data, msg_in.total_size);

    duration<double> time_span = duration_cast<duration<double>>(high_resolution_clock::now() - msg_in.send_time);
    cout << "received msg"<<endl<<"it took: " << time_span.count() << "seconds\n";

    imshow( "Display window", img_received);                   // Show our image inside it.
    waitKey(0);                                          // Wait for a keystroke in the window

    return 0;
}
