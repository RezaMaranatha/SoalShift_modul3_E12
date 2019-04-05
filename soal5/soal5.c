#define cls system("clear")
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

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

int hunger=200, food=10, hygiene=100, health=300, flag=0;
time_t time1;
struct tm begin;
clock_t cooldown;
double timer;

void* autoo(void *a)
{
	while(1){
		while (flag == 3){}
		time_t time2 = time(NULL);
		struct tm end = *localtime(&time2);
		int second = difftime( mktime(&end), mktime(&begin));

		if(second > 0 && second % 10 == 0)
		{ 
			hunger = hunger - 5;
			health = health + 5;
			sleep(1);
		}

		if(second > 0 && second % 30 == 0)
		{ 
			hygiene = hygiene - 10;
			sleep(1);
		}
	}
}
			

void* standby(void *a)
{
	while(1){
		while(flag != 0){}
		cls;		
		printf("Standby Mode\n");
		printf("Health    : %d\n", health);
		printf("Hunger    : %d\n", hunger);
		printf("Hygiene   : %d\n",hygiene);
		printf("Food left : %d\n", food);
		timer = 20.0 - ((double)clock()-cooldown)/CLOCKS_PER_SEC;
		if (timer < 0) timer = 0;
		if(timer > 0) printf("Bath will be ready in [%lf]s\n", timer);
		if(timer == 0) printf("Bath is ready\n");
		printf("Choice\n1. Eat\n2. Bath\n3. Battle\n4. Shop\n5. Exit\n\n");

		int c = getch();
		//scanf("%d", &flag);
		flag = c -'0';
		if(timer > 0 && flag == 2) flag = 0;
		if (flag == 5) exit(0);
	}
}
void* eat(void *a)
{
	while(1){
		while(flag != 1){}
		cls;
		if(food > 0)
		{
			hunger = hunger + 15;
			food--;
		}
		flag = 0;
	}
}

void* bath(void *a)
{
	while(1){
		while(flag != 2){}
		cls;
		hygiene = hygiene + 30;
		flag = 0;
		cooldown = clock();
		sleep(20);
	}
}

void* battle(void *a)
{
	while(1){
		while(flag != 3){}
		cls;
		int health_NPC = 100;
		int input = 0;
		while(input != 2)
		{
			cls;
			printf("Battle Mode\n");
			printf("Monster's Health : %d\n", health);
			printf("Enemy's Health   : %d\n", health_NPC);
			printf("Choices \n1. Attack\n2. Run\n\n");

			int c = getch();
			//scanf("%d", &input);
			input = c - '0';
			if(input == 1)
			{
				health = health - 20;
				health_NPC = health_NPC - 20;
			}
			if(health_NPC <= 0 && health <= 0) {
				printf("Draw!!!\n");
				sleep(2);
				break;
			}
			if(health_NPC > 0 && health <= 0) {
				printf("Your pet was defeated\n");
				sleep(2);
				break;
			}
			if(health_NPC <= 0 && health > 0) {
				printf("Congrats! You defeat your foe\n");
				sleep(2);
				break;
			}
		}
		flag = 0;
	}
}

/*void* shop(void *a)
{
	while(flag != 4){}
	printf("Shop Mode\n");
	printf("Shop food stock: \n", food); 	
}*/

int main(){
	time1 = time(NULL);
	begin = *localtime(&time1);

	cooldown = clock()-20*CLOCKS_PER_SEC;
	
	pthread_t tid0,tid1,tid2,tid3,tid4;

	pthread_create(&tid0, NULL, autoo, NULL);
	pthread_create(&tid1, NULL, standby, NULL);
	pthread_create(&tid2, NULL, eat, NULL);
	pthread_create(&tid3, NULL, bath, NULL);
	pthread_create(&tid4, NULL, battle, NULL);

	while(1){
		if(hunger <= 0)
		{
			printf("You lose\n\n");
			exit(0);
		}
		
		if(hygiene <= 0)
		{
			printf("You lose\n\n");
			exit(0);
		}
		
	}
}
