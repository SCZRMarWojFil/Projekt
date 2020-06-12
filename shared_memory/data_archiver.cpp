// g++ data_archiver.cpp pshm.h -o data_archiver `pkg-config opencv --cflags --libs` -lrt -pthread
#include "pshm.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sched.h>

#define SCHED SCHED_FIFO

int main()
{
	const int core_id = 2;
	const pid_t pid = getpid();
	cpu_set_t  cpuset;
	CPU_ZERO(&cpuset);
	CPU_SET(core_id, &cpuset);
	
	const int set_result = sched_setaffinity(pid, sizeof(cpu_set_t), &cpuset);
	if (set_result != 0) {printf("sched_setaffinity ERROR: %d \n", set_result);exit(1);}
	
	const int get_affinity = sched_getaffinity(pid, sizeof(cpu_set_t), &cpuset);
	if (get_affinity != 0) {printf("sched_getaffinity ERROR: %d \n", get_affinity);exit(1);}
	
	if (CPU_ISSET(core_id, &cpuset)) {
    		printf("Successfully set thread %d to affinity to CPU %d\n in client process", pid, core_id);
	} else {
   		printf("Failed to set thread %d to affinity to CPU %d\n in client process", pid, core_id);
	}
	
	struct sched_param sp = { .sched_priority = sched_get_priority_max(SCHED) };
	int ret;

	//choose policy
	ret = sched_setscheduler(pid, SCHED, &sp);
	if (ret == -1) {
	  perror("sched_setscheduler");
	}
	int policy = sched_getscheduler(pid);

	switch(policy) {
		case SCHED_OTHER:   printf("SCHED_OTHER\n"); break;
		case SCHED_RR:   printf("SCHED_RR\n"); break;
		case SCHED_FIFO:  printf("SCHED_FIFO\n"); break;
		default:   printf("Unknown...\n");
	}

	/* Open the existing shared memory object and map it
		  into the caller's address space */
	int fd = shm_open(SHM_PATH2, O_RDWR, 0);
	if (fd == -1)
	errExit("shm_open");

	struct shmbuf *shmp = (shmbuf *)mmap(NULL, sizeof(struct shmbuf),
		               PROT_READ | PROT_WRITE,
		               MAP_SHARED, fd, 0);

	if (shmp == MAP_FAILED)
	errExit("mmap");

	cv::Mat image(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, cv::Scalar(0,0,255));

	char *name = (char *)malloc(sizeof(char)*200);
	int counter = 0;
	int count = 0;

	// Sending loop
	while(count < 1010){
	++counter;
	sprintf(name, "/home/archive_sczr/%d", counter);
	name = strcat(name, ".jpg\0");

	/* Wait for 'sem1' to be posted by peer before touching
		    shared memory */

	if (sem_wait(&shmp->sem1) == -1)
	    errExit("sem_wait");

	for(int i = 0; i < IMG_HEIGHT; i++){
	cv::Vec3b* ptr = image.ptr<cv::Vec3b>(i);
	    for(int j = 0; j < IMG_WIDTH; j++){
		ptr[j] = shmp->img_data[i][j];
	    }
	}

	if (sem_post(&shmp->sem2) == -1)
	    errExit("sem_post");

	imwrite(name, image);
	
	count++;
	}

	free(name);
	exit(EXIT_SUCCESS);

	return 0;

}
