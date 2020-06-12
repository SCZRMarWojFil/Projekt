#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_NAME  "/test_queue"
#define MAX_QUEUE_SIZE 2000000
#define QUEUE_SIZE_CEILING 5000000
#define MSG_STOP    "exit"
#define MAX_IMAGE_SIZE 900000
#define MAX_MSGS 2
#define PRODUCER_RATE 100    //Hz
#define N_LOOPS 1000


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

#endif /* #ifndef COMMON_H_ */