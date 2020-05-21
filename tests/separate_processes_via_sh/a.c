#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // notice this! you need it for sleep!

//TODO: fix that number of seconds (in practice it's not in seconds ...)
void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
        ; 
} 

int main(){
    delay(1000);
    for(int i=0; i < 5; i++)
        printf("a: %d \n", i);
    sleep(5);
    printf("Done waiting ... \n");
    return 0;
}