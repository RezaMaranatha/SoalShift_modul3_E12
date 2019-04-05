#define cls system("clear")
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int *stok;
int stokctr=0;

int getch()
{
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt= oldt;
        newt.c_lflag &= ~(ICANON| ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch= getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
}

int main()
{
        key_t key = 1234;
        int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
        stok = shmat(shmid, NULL, 0);
        while(1){
          //      while(flag != 4){}
                cls;
                int input = 0;
                while(input!=2){
                        cls;
                        printf("Shop\n");
                        printf("Shop Food Stock: %d\n", *stok);
//                        printf("Your food stock: %d\n", food);
                        printf("Choices \n1. Restock\n2. Exit\n\n");

                        int c = getch();
                        //scanf("%d", &input);
                        input = c - '0';

                        if(input==1){
				stokctr = *stok;
				stokctr++;
				*stok = stokctr;
				printf("Food Restocked!\n");
				sleep(1);
                        }
                        else if(input==2){
				printf("Exiting Shop.\n");
                                shmdt(stok);
				break;
                        }
                }
	break;
        }
        //shmdt(stok);
}
