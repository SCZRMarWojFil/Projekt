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
#include <thread>
#include <unistd.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../include/common.h"
#include "../include/structures.h"

using namespace cv;
using namespace std;
using namespace chrono;

Mat get_image(string image_path)
{
    Mat image;
    image = imread(image_path, CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << endl ;
    }
    return image;
}




int main(int argc, char **argv)
{
    vector<int> sched_options = get_sched_params();
    mqd_t mq;
    struct mq_attr attr;
    msg_buffer msg_out;

    /* initialize the queue attributes */
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MSGS;
    attr.mq_msgsize = sizeof(msg_out);
    attr.mq_curmsgs = 0;

    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0666, &attr);
    CHECK((mqd_t)-1 != mq);

    string image_path = "data/grafika-joker.jpg";
    Mat image = get_image(image_path);
    cout << "img size: " << image.size() <<endl;

    cout <<  "image.data size:" << sizeof(image.data)<< endl;
    size_t sizeInBytes = image.total() * image.elemSize();
    cout << "image total byte size: " << image.total() << endl << "loop started ... ";

    int rate = strtol(argv[1], NULL, 10);


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

        cout <<"active_policy " << get_sched_name(active_policy) << endl;

        high_resolution_clock::time_point loop_begin_t = high_resolution_clock::now();

        for(size_t i=0; i<=N_LOOPS; ++i)
        {
            msg_out.total_size = sizeInBytes;
            memcpy(msg_out.image_data, image.data, sizeInBytes);
            msg_out.cols = image.cols;
            msg_out.rows = image.rows;
            msg_out.cv_type = image.type();
            msg_out.send_time = high_resolution_clock::now();
            CHECK(mq_send(mq,  (const char *) &msg_out, sizeof(msg_out), 0) != (mqd_t)-1);
            this_thread::sleep_for(milliseconds(1000/rate));
            //cout << "msg sent\n";
        }
        cout <<"done\n";
        cout << "loop finished\tavarage publish frequency: " << 1e-6 * duration_cast<microseconds>(high_resolution_clock::now() - loop_begin_t).count()/N_LOOPS << endl;
    }
        
        
        // wait for user to close queue
    /* cleanup */
//    CHECK((mqd_t)-1 != mq_close(mq));
//    cout << "closing queue\n";
//    CHECK((mqd_t)-1 != mq_unlink(QUEUE_NAME));
//    cout << "unlinking queue\n";

    return 0;
}