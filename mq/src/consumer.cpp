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
#include <vector>
#include <sched.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../include/common.h"
#include "../include/structures.h"

using namespace cv;
using namespace std;
using namespace chrono;






int main(int argc, char **argv)
{
    // wektor 3 trybow szeregowania. w czasie dzialania programu bedziemy testowac wszystkie
    vector<int> sched_options = get_sched_params();
	

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
    CHECK((mqd_t)-1 != mq);

    int receive_code = 0;
    // kolejnosc: SCHED_OTHER -> SCHED_FIFO -> SCHED_RR
    for(int i=0; i<sched_options.size(); i++)
    {
        /*
	struct sched_param sp = { .sched_priority = sched_get_priority_max(SCHED_OTHER) };
	int ret;

	//choose policy
	ret = sched_setscheduler(pid, SCHED_OTHER, &sp);
        */
        struct sched_param sched_option = { .sched_priority = sched_get_priority_max(sched_options[i]) };

        int active_policy = set_scheduler(sched_options[i], &sched_option);
        string sched_option_str = get_sched_name(active_policy);

        ofstream time_log_file;
        vector<double> durations;
        vector<double> wait_times;

        string filename = sched_option_str+"_time_log.csv";

        time_log_file.open(filename);

        time_log_file << "transfer_duration[us],waiting_time[ms]\n";
        cout <<"log file " << filename << " created\n" << "loop started \n...";

        size_t n_loops = N_LOOPS;
        high_resolution_clock::time_point loop_begin_t = high_resolution_clock::now();

        for(size_t i=0; i<=N_LOOPS; ++i)
        {
            high_resolution_clock::time_point wait_begin = high_resolution_clock::now();
            receive_code = mq_receive(mq, (char *) &msg_in, sizeof(msg_in)+1, NULL);
            high_resolution_clock::time_point wait_end = high_resolution_clock::now();
            CHECK((mqd_t)-1 != receive_code);
            Mat img_received(msg_in.rows, msg_in.cols, msg_in.cv_type);
            memcpy(img_received.data, msg_in.image_data, msg_in.total_size);
            durations.push_back(duration_cast<microseconds>(high_resolution_clock::now() - msg_in.send_time).count());
            wait_times.push_back(duration_cast<milliseconds>(wait_end- wait_begin).count());
        }
        cout << "done\n";
        for(int i=0; i<N_LOOPS; i++)
        {
            time_log_file << durations[i] << "," << wait_times[i] << endl;
        }
        time_log_file.close();
        cout << "loop finished\tavarage receive frequency: " << 1e-6 * duration_cast<microseconds>(high_resolution_clock::now() - loop_begin_t).count()/N_LOOPS << endl;
    }

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
