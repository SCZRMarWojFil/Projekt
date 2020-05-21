#include<stdio.h> 
#include<string.h> 
#include<unistd.h> 
#include<fcntl.h> 

int main(){
    int fd = 1;
    char message[] = "hello geeks\n";
    write(1, message, strlen(message));
    return 0;
}