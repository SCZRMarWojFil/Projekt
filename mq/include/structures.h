#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 

#include "common.h"
#include <opencv2/core/core.hpp>



// structure for message queue 
struct msg_buffer { 
  size_t total_size;
  int cv_type;
  int rows;
  int cols;
	char msg_type; 
	char msg_text[MAX_IMAGE_SIZE]; 
}; 




struct queue_info_ {
    struct ipc_perm msg_perm;     /* Ownership and permissions */
    time_t          msg_stime;    /* Time of last msgsnd(2) */
    time_t          msg_rtime;    /* Time of last msgrcv(2) */
    time_t          msg_ctime;    /* Time of last change */
    unsigned long   __msg_cbytes; /* Current number of bytes in
                                     queue (nonstandard) */
    msgqnum_t       msg_qnum;     /* Current number of messages
                                     in queue */
    msglen_t        msg_qbytes;   /* Maximum number of bytes
                                     allowed in queue */
    pid_t           msg_lspid;    /* PID of last msgsnd(2) */
    pid_t           msg_lrpid;    /* PID of last msgrcv(2) */
} queue_info;
