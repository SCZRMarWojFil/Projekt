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

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "../include/common.h"
#include "../include/structures.h"

using namespace cv;
using namespace std;

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

    rlimit limits;
    limits.rlim_max = QUEUE_SIZE_CEILING;
    limits.rlim_cur = MAX_QUEUE_SIZE;
    CHECK(setrlimit(RLIMIT_MSGQUEUE, &limits) != -1);

    int res = getrlimit(RLIMIT_MSGQUEUE,  &limits);

    printf("rlim_cur: %lu  rlim_max: %lu\n", limits.rlim_cur, limits.rlim_max);

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


    mq_getattr(mq, &attr);
    printf("max_msgs: %lu, max_msg_size: %lu, current_msgs: %lu\n\n", attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

    string image_path = "data/grafika-joker.jpg";
    Mat image = get_image(image_path);
    cout << "img size: " << image.size() <<endl;

    //strcpy(msg_out.msg_text, "elo elo 320");
    msg_out.msg_type = 'L';

    cout <<  "image.data size:" << sizeof(image.data)<< endl;
    size_t sizeInBytes = image.total() * image.elemSize();
    cout << "image total byte size: " << image.total() << endl;
    msg_out.total_size = sizeInBytes;

    memcpy(msg_out.msg_text, image.data, sizeInBytes);
    msg_out.cols = image.cols;
    msg_out.rows = image.rows;
    msg_out.cv_type = image.type();

    cout << "data copied\nsizeof(msg_out)=" << sizeof(msg_out) <<endl;
//    printf("Address of mat.data is %p\n", (void *)image.data); 
    //n = mq_receive(mq, (char *) &buf, sizeof(buf), NULL);
//(const char *)
    CHECK(mq_send(mq,  (const char *) &msg_out, sizeof(msg_out), 0) != (mqd_t)-1);

    string c;
    cin >> c;
    /* cleanup */
    CHECK((mqd_t)-1 != mq_close(mq));
    cout << "closing queue\n";
    CHECK((mqd_t)-1 != mq_unlink(QUEUE_NAME));
    cout << "unlinking queue\n";

    return 0;
}