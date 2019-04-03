#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int WakeUp_Status=0, Spirit_Status=100, wcount=0, scount=0, statI=1, statI_block=0, statA=1, statA_block=0;
time_t timeIraj, timeAgmal;
struct tm beginIraj;
struct tm beginAgmal;

void *status(void *a)
{
	char * cmd;
	cmd = (char *) a;
	
	char* syscmd1 = malloc(sizeof(char));
	strcpy(syscmd1, "All Status");

	if(strcmp(cmd,syscmd1) == 0)
	{
		printf("Agmal WakeUp_Status = %d\n", WakeUp_Status);
		printf("Iraj Spirit_Status = %d\n\n", Spirit_Status);
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

	if(wcount == 3) 
	{
		printf("Fitur Iraj Ayo Tidur disabled for 10s\n");
		timeIraj = time(NULL);
		beginIraj = *localtime(&timeIraj);
		statI=0;
		statI_block = 1;
		wcount = 0;
	}	

	if(WakeUp_Status >= 100) 
	{			
		printf("Agmal Terbangun, mereka bangun pagi dan berolahraga\n");
		exit(0);
	}
}

void *iraj(void *a)
{
	if (statI==1){
		char * cmd2;
		cmd2 = (char *) a;

		char* syscmd3 = malloc(sizeof(char));
		strcpy(syscmd3, "Iraj Ayo Tidur");	

		if(strcmp(cmd2,syscmd3) == 0)
		{
			Spirit_Status = Spirit_Status - 20;
			scount++;
		}

		if(scount == 3) 
		{
			printf("Fitur Agmal Ayo Bangun disabled for 10s\n");
			timeAgmal = time(NULL);
			beginAgmal = *localtime(&timeAgmal);
			statA=0;
			statA_block = 1;
			scount = 0;
		}	

		if(Spirit_Status <= 0)
		{ 
			printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
			exit(0);
		}
	}
}

int main(){

	pthread_t tid1, tid2, tid3;
	while(1)
	{	
		if(statI_block == 1)
		{
			time_t timeIraj2 = time(NULL);
			struct tm endIraj = *localtime(&timeIraj2);
			double second1 = difftime( mktime(&endIraj), mktime(&beginIraj));
		
			if(second1 >= 10.0) 
			{		
				statI_block=0;
				statI = 1;
			}
		}

		if(statA_block == 1)
		{
			time_t timeAgmal2 = time(NULL);
			struct tm endAgmal = *localtime(&timeAgmal2);
			double second2 = difftime( mktime(&endAgmal), mktime(&beginAgmal));
		
			if(second2 >= 10.0) 
			{		
				statA_block=0;
				statA = 1;
			}
		}
	
		char* cmd = malloc(sizeof(char));
		
		scanf("%[^\n]%*c",cmd);

		pthread_create(&tid1, NULL, status, (void *) cmd);
		pthread_create(&tid2, NULL, agmal, (void *) cmd);
		pthread_create(&tid3, NULL, iraj, (void *) cmd);

	}	
	
} 

