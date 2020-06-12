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
#include <fstream>
#include <chrono>
#include <unistd.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../include/common.h"
#include "../include/structures.h"

using namespace cv;
using namespace std;
using namespace chrono;




int main(int argc, char **argv)
{
    cout << "CONSUMER PROCESS PID: " << getpid() << endl;
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

    int receive_code = 0;
    ofstream time_log_file;
    time_log_file.open("time_logs.csv");
    time_log_file << "transfer_duration[us],processed_time\n";
    cout <<"log file created\n" << "loop started \n...";

    size_t n_loops = N_LOOPS;
    high_resolution_clock::time_point loop_begin_t = high_resolution_clock::now();

    for(size_t i=0; i<=N_LOOPS; ++i)
    {
        receive_code = mq_receive(mq, (char *) &msg_in, sizeof(msg_in)+1, NULL);
        CHECK((mqd_t)-1 != receive_code);

        Mat img_received(msg_in.rows, msg_in.cols, msg_in.cv_type);
        memcpy(img_received.data, msg_in.image_data, msg_in.total_size);
        time_log_file << duration_cast<microseconds>(high_resolution_clock::now() - msg_in.send_time).count() << endl;
        //cout << "msg received\n";
    //    msg_out.total_size = sizeInBytes;
    //    memcpy(msg_out.image_data, image.data, sizeInBytes);
    //    msg_out.cols = image.cols;
    //    msg_out.rows = image.rows;
    //    msg_out.cv_type = image.type();
    //    msg_out.send_time = high_resolution_clock::now();
    //    CHECK(mq_send(mq,  (const char *) &msg_out, sizeof(msg_out), 0) != (mqd_t)-1);
    //    this_thread::sleep_for(milliseconds(1000/PRODUCER_RATE));
    }
    cout << "done\n";

    time_log_file.close();
    cout << "loop finished\tavarage receive frequency: " << duration_cast<microseconds>(high_resolution_clock::now() - loop_begin_t).count()/N_LOOPS << endl;
/*
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    //Mat img_received(buf.rows, buf.cols, buf.type);
   // Size img_size(msg_in.cols, i_in.rows)
    Mat img_received(msg_in.rows, msg_in.cols, msg_in.cv_type);
    memcpy(img_received.data, msg_in.image_data, msg_in.total_size);

    duration<double> time_span = duration_cast<duration<double>>(high_resolution_clock::now() - msg_in.send_time);
    cout << "received msg"<<endl<<"it took: " << time_span.count() << "seconds\n";

    imshow( "Display window", img_received);                   // Show our image inside it.
    waitKey(0);                                          // Wait for a keystroke in the window
*/
    return 0;
}
