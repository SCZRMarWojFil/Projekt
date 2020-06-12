#include<iostream>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <mqueue.h>

#include "../include/structures.h"



int set_rlimit()
{
    rlimit limits;
    limits.rlim_max = QUEUE_SIZE_CEILING;
    limits.rlim_cur = MAX_QUEUE_SIZE;
    CHECK(setrlimit(RLIMIT_MSGQUEUE, &limits) != -1);

    int res = getrlimit(RLIMIT_MSGQUEUE,  &limits);

    printf("rlim_cur: %lu  rlim_max: %lu\n", limits.rlim_cur, limits.rlim_max);
    return 0;
}

int print_current_mq_attributes(mqd_t mq)
{
    struct mq_attr attr;
    mq_getattr(mq, &attr);
    printf("max_msgs: %lu, max_msg_size: %lu, current_msgs: %lu\n\n", attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
    return 0;
}