#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int hasil;

int cmparray(const void *a, const void *b)
{
	return ( *(int*)a - *(int*)b);
}

void *factorial(void *a)
{
	int result = 1;
	int fact = *((int*) a);
	while(fact > 1){
		result = result * fact;
		fact--;
	}
	
	hasil = result;
}
		

int main(int argc, char **argv)
{
	int number[500];
	//printf("%d\n", argc);
	for(int i=1; i < argc; i++)
	{
		number[i-1] = atoi(argv[i]);
	}
	
	qsort(number, argc-1, sizeof(int), cmparray);

	//for(int i=0; i<argc-1; i++) printf("%d\n", number[i]);
	for (int i=0; i < argc-1; i++)
	{
		hasil = 0;
		pthread_t tid;
		int *temp = malloc(sizeof(*temp));
		temp = &number[i];
		pthread_create(&tid, NULL, factorial, temp);
		pthread_join(tid,NULL);
		printf("%d! = %d\n", number[i], hasil);
	}

	return 0; 
} 

	
