#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){

    int res = system("./all_processes.sh");

    printf("%d \n", res);

    sleep(2);

    for(int i = 0; i < 5; i++)
        printf("%d", i);

    sleep(2);

    for(int j = 0; j < 5; j++)
        printf("%d", j);

    return 0;
}