// g++ data_processing.cpp pshm.h -o data_processing `pkg-config opencv --cflags --libs` -lrt -pthread
#include "pshm.h"
#include <time.h>
#include <ctype.h>
#include <opencv2/opencv.hpp>
#include <sys/stat.h>
#include <sys/types.h>
#include <sched.h>
#include <iostream>
#include <fstream>

#define BILLION 1000000000L

int main(){
	
	shm_unlink(SHM_PATH2);
	
	pid_t pid = getpid();
	
	struct sched_param sp = { .sched_priority = sched_get_priority_max(SCHED_OTHER) };
	int ret;

	//choose policy
	ret = sched_setscheduler(pid, SCHED_OTHER, &sp);
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

	/* Create shared memory object and set its size to the size
		  of our structure */
	int fd2 = shm_open(SHM_PATH2, O_CREAT | O_EXCL | O_RDWR,
		      S_IRUSR | S_IWUSR);
	if (fd2 == -1)
	errExit("shm_open");

	// Truncating file to size of the proper structure
	if (ftruncate(fd2, sizeof(shmbuf)) == -1)
	errExit("ftruncate");

	// Map the object into the caller's address space
	struct shmbuf *shmp2 = (shmbuf *)mmap(NULL, sizeof(struct shmbuf),
		               PROT_READ | PROT_WRITE,
		               MAP_SHARED, fd2, 0);

	if (shmp2 == MAP_FAILED)
        errExit("mmap");

	/* Initialize semaphores as process-shared, with value 0 */
	if (sem_init(&shmp2->sem1, 1, 0) == -1)
	errExit("sem_init-sem1");
	if (sem_init(&shmp2->sem2, 1, 0) == -1)
	errExit("sem_init-sem2");

	
	/* Open the existing shared memory object and map it
		  into the caller's address space */

	int fd = shm_open(SHM_PATH, O_RDWR, 0);
	if (fd == -1)
	errExit("shm_open");

	struct shmbuf *shmp = (shmbuf *)mmap(NULL, sizeof(struct shmbuf),
		               PROT_READ | PROT_WRITE,
		               MAP_SHARED, fd, 0);

	if (shmp == MAP_FAILED)
	errExit("mmap");

	cv::Mat image(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, cv::Scalar(0,0,255));

	char *name = (char *)malloc(sizeof(char)*200);


	FILE * file = fopen("1_recive_OTHER.txt", "w");

	struct timespec start, stop;
	double time;
	int count = 0;
	
	// Sending loop
	while(count < 202){

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
	
	// save time
	if ( clock_gettime (CLOCK_REALTIME, &start ) == -1 ){
		perror ("clock gettime");
		exit(EXIT_FAILURE);
	}
	time = start.tv_sec  + (double)(start.tv_nsec) / BILLION;
	
	if (file != NULL) fprintf(file, "%f\n", time);

	if (sem_post(&shmp->sem2) == -1)
	    errExit("sem_post");

	cv::blur(image, image, cv::Size(7, 7), cv::Point(-1,-1));

        for(int i = 0; i < image.rows; i++){
        cv::Vec3b* ptr = image.ptr<cv::Vec3b>(i);
            for(int j = 0; j < image.cols; j++){
                memcpy(&shmp2->img_data[i][j], &ptr[j], sizeof(cv::Vec3b));
            }
        }

        /* Tell peer that it can now access shared memory */

        if (sem_post(&shmp2->sem1) == -1)
            errExit("sem_post");


        /* Wait until peer says that it has finished accessing
                  the shared memory */

        if (sem_wait(&shmp2->sem2) == -1)
            errExit("sem_wait");
	
	count++;
	}

	fclose(file);

	free(name);
	shm_unlink(SHM_PATH2);
	exit(EXIT_SUCCESS);

	return 0;
}

