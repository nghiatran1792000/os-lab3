#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sys/wait.h" 

int main(int argc, char* argv[]) {
    pid_t child;
    child = fork(); //create A and B, B is child of A
    if (child == -1) {
        perror("Error");
        exit(1);
    }
    else if (child == 0) { //inside B process
        pid_t childB;
        childB = fork(); //create E is child of B
        if (childB == -1) {
            perror("Error B");
            exit(1);
        }
        else if (childB == 0) { //inside E process
            printf("E"); //print E
            fflush(stdout);
        }
        else {  //inside B process
            pid_t childB1;
            childB1 = fork(); // create F is child of B
            if (childB1 == 0) {
                wait(NULL);  // wait E is child of B process complete              A
                printf("F");    /*print F                                        / | \          */
                fflush(stdout);    //                                          B   C   D
            }                      /*                                         / \  |            */
            else {                 /*                                        E   F G            */
                wait(NULL);  /* wait F is child of B process complete              |            */
                printf("B"); //print B                                             I
                fflush(stdout);
            }
        }
    }
    else {  //inside A process
        wait(NULL);  //wait B is child of A process complete
        pid_t child1;
        child1 = fork();   //create C is child of A
        if (child1 == -1) {
            perror("Error C");
            exit(1);
        }
        else if (child1 == 0) {   //inside C process       
            pid_t childC; 
            childC = fork(); //create G is child of C
            if (childC == -1) {
                perror("Error G");
                exit(1);
            }
            else if (childC == 0){   //inside G process
                pid_t childG;
                childG = fork();    //create I is child of G
                if (childG == -1) {
                    perror("Error I");
                    exit(1);
                }
                else if (childG == 0){  //inside I process
                    printf("I");    //print I
                    fflush(stdout);
                }
                else {
                    wait(NULL);     //wait I is child of G process complete
                    printf("G");    //print G
                    fflush(stdout);
                }
            }
            else {
                wait(NULL);     //wait G is child of C process complete
                printf("C");    //print C
                fflush(stdout);
            }
        }
        else {      //inside A process
            wait(NULL);     //wait C is child of A process complete
            pid_t child2;
            child2 = fork(); //create D is child of A
            if (child2 == -1) {
                perror("Error D");
                exit(1);
            }
            else if (child2 == 0) { //inside D process
                printf("D");    //print D
                fflush(stdout);
            }
            else {
                wait(NULL);     //wait D is child of A process complete
                printf("A");    //print A
                fflush(stdout);
            }            
        }        
    }
    return 0;
}