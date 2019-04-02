#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>

int prime_arr[1000];
pthread_t tid[50];


struct range{
int low,high;
};

void* tulis(void* args){
    struct range*extract =(struct range*)args;
    printf("[ Range %d sampai %d ]\n",extract->low,extract->high);

    for(int i =extract->low; i <=extract->high; i++){
        int isPrime = 0;

        for(int j = 2; j <=i/2; j++){
            if(i % j == 0){
                isPrime = i;
                break;
            }
        }

        if(isPrime==0){
            prime_arr[i]= i;
        }
    }
    for(int i=extract->low; i < extract->high; i++){ //print prime per thread
        if(prime_arr[i]!=0){
            printf("%d ",prime_arr[i]);
        }
   }
   printf("\n");
}

int main(){
    int n,t;
    scanf("%d %d",&n, &t);
    if(n==0||t==0){
	printf("input > 0\n");
	scanf("%d %d",&n, &t);
    }
    struct range rentang;
    rentang.low=2;
    rentang.high=n/t;

    for(int i=0;i<t; i++){
        pthread_create(&tid[i], NULL, &tulis,(void *)&rentang);
        pthread_join(tid[i],NULL);
	rentang.low=1+rentang.high;
        if(i==t-2){
	rentang.high=n;	
	}
	else{
	rentang.high+=(n/t);
	}
    }
return 0;
}
