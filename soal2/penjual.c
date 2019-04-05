#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define PORT 8080

int *value;
int countr = 0;
int new_socket;

void* print(void *arg){
	key_t key = 1234;
	int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
	value = shmat(shmid, NULL, 0);

	while(1){
		printf("Stok Sekarang : %d\n", *value);
	        sleep(5);
	}
	shmdt(value);
}

void* sock(void *arg){
	char buffer[2048] = {0};
	char jual[20];
	strcpy(jual,"tambah");
	char keluar[20];
	strcpy(keluar,"jancok");
	//char ss[20];
	//strcpy(ss,"keluar");
    while(read(new_socket , buffer, 2048)){
	strtok(buffer,"\n");
	if(strcmp(keluar,buffer)==0){
                //send(new_socket , ss , strlen(ss) , 0 );
		break;
        }
	else if(strcmp(jual,buffer)==0){
		countr= *value;
		countr++;
		//printf("%d\n",countr);
		*value=countr;
	}
	else{
		printf("Enter tambah atau exit\n");
	}
	printf("%s\n",buffer);
	memset(buffer,0,strlen(buffer));
	//printf("%s\n",buffer);
    }
}

int main(int argc, char const *argv[]) {

    pthread_t thread1,thread2;
	pthread_create(&thread2,NULL,print,NULL);

    char buffer[2048] = {0};
        char jual[20];
        strcpy(jual,"tambah");
        char keluar[20];
        strcpy(keluar,"exit");
	char cek[10];
	strcpy(cek,"jual");
    int server_fd, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    //char *hello = "Hello from server";
    	
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 0) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
        //char ss[20];
        //strcpy(ss,"keluar");
    //send(new_socket,cek,strlen(cek),0);
    while(read(new_socket , buffer, 2048)){
        strtok(buffer,"\n");
        if(strcmp(keluar,buffer)==0){
                //send(new_socket , ss , strlen(ss) , 0 );
		break;
        }
        else if(strcmp(jual,buffer)==0){
                countr= *value;
                countr++;
               // printf("%d\n",countr);
                *value=countr;
        }
        else{
                printf("Enter tambah atau exit\n");
        }
        //printf("%s\n",buffer);
        memset(buffer,0,strlen(buffer));
        //printf("%s\n",buffer);
    }
//pthread_create(&thread2,NULL,print,NULL);
//pthread_create( &thread1, NULL, sock, NULL);
//pthread_exit(NULL);
//pthread_join(thread1,NULL);
return 0;
}
