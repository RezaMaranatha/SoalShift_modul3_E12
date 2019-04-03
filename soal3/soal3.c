#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

int WakeUp_Status=0, Spirit_Status=100, wcount=0, scount=0;

void *status(void *a)
{
	char * cmd;
	cmd = (char *) a;
	
	char* syscmd1 = malloc(sizeof(char));
	strcpy(syscmd1, "All Status");

	if(strcmp(cmd,syscmd1) == 0)
	{
		printf("Agmal WakeUp_Status = %d\n", WakeUp_Status);
		printf("Iraj Spirit_Status = %d\n", Spirit_Status);
	}

}

void *agmal(void *a)
{
	char * cmd1;
	cmd1 = (char *) a;

	char* syscmd2 = malloc(sizeof(char));
	strcpy(syscmd2, "Agmal Ayo Bangun");

	if(strcmp(cmd1,syscmd2) == 0)
	{
		WakeUp_Status = WakeUp_Status + 15;
		wcount++;
	}

	if(scount == 3)
	{
		printf("Fitur Agmal Ayo Bangun disabled 10 s\n");
		sleep(30);
		scount = 0;
	}
}

void *iraj(void *a)
{
	char * cmd2;
	cmd2 = (char *) a;

	char* syscmd3 = malloc(sizeof(char));
	strcpy(syscmd3, "Iraj Ayo Tidur");	

	if(strcmp(cmd2,syscmd3) == 0)
	{
		Spirit_Status = Spirit_Status - 20;
		scount++;
	}

	if(wcount == 3)
	{
		printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
		sleep(30);
		wcount = 0;
	}
}

int main(){
	while(WakeUp_Status < 100 && Spirit_Status > 0)
	{
		pthread_t tid1, tid2, tid3;
		char* cmd = malloc(sizeof(char));
		
		scanf("%[^\n]%*c",cmd);

		pthread_create(&tid1, NULL, status, (void *) cmd);

		pthread_create(&tid2, NULL, agmal, (void *) cmd);

		pthread_create(&tid3, NULL, iraj, (void *) cmd);


	}
	return 0;
} 

