#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include<iostream>

#define QUEUE_NAME  "/test_queue"
#define MAX_QUEUE_SIZE 2000000
#define QUEUE_SIZE_CEILING 5000000
#define MSG_STOP    "exit"
#define MAX_IMAGE_SIZE 900000
#define MAX_MSGS 2
#define PRODUCER_RATE 10000    //Hz
#define N_LOOPS 10000


#define CHECK(x) \
    do { \
        if (!(x)) { \
            fprintf(stderr, "%s:%d:", __func__, __LINE__); \
            perror(#x); \
            printf("errno code:%d\n", errno);\
            exit(-1); \
        } \
    } while (0) \

int print_current_mq_attributes(mqd_t mq);
int set_rlimit();
std::string get_sched_name(int policy);
int set_scheduler(int sched, sched_param *sp);
std::vector<int> get_sched_params();


#endif /* #ifndef COMMON_H_ */