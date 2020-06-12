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
#include <mqueue.h>
#include <sched.h>

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

std::string get_sched_name(int policy)
{
    std::string ret;
    switch(policy) 
    {
	    case SCHED_OTHER:   ret = "SCHED_OTHER"; break;
	    case SCHED_RR:   ret="SCHED_RR"; break;
	    case SCHED_FIFO:  ret="SCHED_FIFO"; break;
	    default:   ret="Unknown";
	}
    return ret;
}

int set_scheduler(int sched, sched_param *sp)
{
    pid_t pid = getpid();
    int ret;

	//choose policy
	ret = sched_setscheduler(pid, sched, sp);
	if (ret == -1) {
	  perror("sched_setscheduler ERROR");
	}
	int policy = sched_getscheduler(pid);

	std::cout << get_sched_name(policy) << std::endl;
    return policy;
}


std::vector<int> get_sched_params()
{
    // wektor 3 trybow szeregowania. w czasie dzialania programu bedziemy testowac wszystkie
    std::vector<int> sched_options = {SCHED_OTHER, SCHED_FIFO, SCHED_RR};
    return sched_options;
}