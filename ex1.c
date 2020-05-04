#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sys/wait.h"

int main(int argc, char** argv) {
    int a[100];
    int size = 0;
    char temp[79];
    int tempInt;
    FILE* in = fopen("numbers.txt", "r+");
    if (in == NULL) printf("Failed");
    while(!feof(in)) {
        fgets(temp, 79, in);
        tempInt = atoi(temp);
        a[size] = tempInt;
        size++;
    }
    pid_t child_pid;
    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }
    else if (child_pid == 0) {
        int count = 0;
        for (int i = 0; i < size; i++) {
            if (a[i] % 3 == 0) count++;
        }
        printf("%d (Talented class answer: %d)\n", child_pid + 3, count);
        fflush(stdout);
    }
    else {
        pid_t child_pid1;
        child_pid1 = fork();
        if (child_pid1 == 0) {
            wait(NULL);
            int count = 0;
            for (int i = 0; i < size; i++) {
                if (a[i] % 7 == 0) count++;
            }
            printf("%d (Talented class answer: %d)\n", child_pid1 + 2, count);
            fflush(stdout);
        }
        else {
            wait(NULL);
            int count = 0;
            for (int i = 0; i < size; i++) {
                if (a[i] % 11 == 0) count++;
            }
            printf("%d (Talented class answer: %d)\n", child_pid1 - child_pid1 + 1, count);
            fflush(stdout);
        }        
    }
    return 0; 
}