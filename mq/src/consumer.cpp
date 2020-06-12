#include <sys/stat.h>
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


int main(int argc, char **argv)
{
    mqd_t mq;
    struct mq_attr attr;
    msg_buffer msg_in;

    /* create the message queue */
    mq = mq_open(QUEUE_NAME, O_RDONLY, 0666);
    if((mqd_t)-1 == mq)
    {
        cout << "Meesage queue with given name doesn't exist.\nSpawn producer first\n";
        return -1;
    }

    int receive_code = mq_receive(mq, (char *) &msg_in, sizeof(msg_in)+1, NULL);
    cout << "bytes received: " << receive_code << endl;
    CHECK((mqd_t)-1 != receive_code);

    cout << " struct received: \n type: " << msg_in.msg_type << "  byte_total_size: " << msg_in.total_size << endl;

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    //Mat img_received(buf.rows, buf.cols, buf.type);
   // Size img_size(msg_in.cols, i_in.rows)
    Mat img_received(msg_in.rows, msg_in.cols, msg_in.cv_type);

    memcpy(img_received.data, msg_in.msg_text, msg_in.total_size);

    imshow( "Display window", img_received);                   // Show our image inside it.
    waitKey(0);                                          // Wait for a keystroke in the window

    return 0;
}
