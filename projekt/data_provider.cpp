// g++ data_provider.cpp pshm.h -o data_provider `pkg-config opencv --cflags --libs` -lrt -pthread
// ./data_provider 0.5
#include <time.h>
#include <ctype.h>

#include "pshm.h"

void delay(double number_of_seconds) 
{ 
    // Converting time into ticks per second
    int ticks_per_sec = 1000000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + ticks_per_sec) 
        ; 
}

int main(int argc, char *argv[]){

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s sending-frequency[Hz]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *ptr = argv[1];
    int dotts = 0;

    // Checking if argument is double
    for(int i = 0; i < strlen(argv[1]); i++){
        if(isdigit(*(ptr+i)) == 0 && *(ptr+i) != '.'){
            fprintf(stderr, "Sending-frequency[Hz] needs to be a double value\n");
            exit(EXIT_FAILURE);
        }else if(*(ptr+i) == '.'){
            dotts++;
            if(dotts > 1){
                fprintf(stderr, "Sending-frequency[Hz] needs to be a double value\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    double freq = atof(argv[1]);
    
    if(freq == 0.0){
        fprintf(stderr, "Sending-frequency[Hz] cannot be equal to 0\n");
        exit(EXIT_FAILURE);
    }

     /* Create shared memory object and set its size to the size
                  of our structure */
    int fd = shm_open(SHM_PATH, O_CREAT | O_EXCL | O_RDWR,
                      S_IRUSR | S_IWUSR);
    if (fd == -1)
        errExit("shm_open");

    // Truncating file to size of the proper structure
    if (ftruncate(fd, sizeof(shmbuf)) == -1)
        errExit("ftruncate");

    // Map the object into the caller's address space
    struct shmbuf *shmp = (shmbuf *)mmap(NULL, sizeof(struct shmbuf),
                               PROT_READ | PROT_WRITE,
                               MAP_SHARED, fd, 0);

    if (shmp == MAP_FAILED)
        errExit("mmap");

    /* Initialize semaphores as process-shared, with value 0 */
    if (sem_init(&shmp->sem1, 1, 0) == -1)
        errExit("sem_init-sem1");
    if (sem_init(&shmp->sem2, 1, 0) == -1)
        errExit("sem_init-sem2");

    char *name = (char *)malloc(sizeof(char)*200);
    int counter = 1;
    cv::Mat image;

    // Sending loop
    while(!_kbhit()){

        if(counter > 3)
            counter = 1;

        sprintf(name, "dog%d", counter);
        name = strcat(name, ".jpg\0");

        image = cv::imread(name, cv::IMREAD_COLOR);

        // Checking for invalid input
        if(!image.data)
        {
            printf("Could not open or find the image\n");
            return -1;
        }

        clock_t start = clock();

        for(int i = 0; i < image.rows; i++){
        cv::Vec3b* ptr = image.ptr<cv::Vec3b>(i);
            for(int j = 0; j < image.cols; j++){
                memcpy(&shmp->img_data[i][j], &ptr[j], sizeof(cv::Vec3b));
            }
        }

        /* Tell peer that it can now access shared memory */

        if (sem_post(&shmp->sem1) == -1)
            errExit("sem_post");

        delay(1/freq);

        /* Wait until peer says that it has finished accessing
                  the shared memory */

        if (sem_wait(&shmp->sem2) == -1)
            errExit("sem_wait");

        clock_t end = clock();
        double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("for loop took %f seconds to execute \n", cpu_time_used);

        counter ++;
    }

    free(name);
    shm_unlink(SHM_PATH);
    exit(EXIT_SUCCESS);

    return 0;
}