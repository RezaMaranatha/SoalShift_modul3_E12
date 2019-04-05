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

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char beli[20];
    strcpy(beli,"beli");
    char keluar[20];
    strcpy(keluar,"exit");
    //char cek[10];
    //strcpy(cek,"beli");
    char ye[30];
    char no[30];
    strcpy(ye,"transaksi berhasil");
    strcpy(no,"transaksi gagal");
    
    key_t key = 1234;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);
  
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

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    //send(new_socket,cek,strlen(cek),0);
    while(read(new_socket , buffer, 2048)){
        strtok(buffer,"\n");
        if(strcmp(keluar,buffer)==0){
                //send(new_socket , ss , strlen(ss) , 0 );
		shmdt(value);
		break;
        }
        else if(strcmp(beli,buffer)==0){
                countr= *value;
		//printf("%d\n",countr);
		if(countr<=0){
			send(new_socket,no,strlen(no),0);
		}
		else{
			countr--;
			send(new_socket,ye,strlen(ye),0);
		}
               // printf("%d\n",countr);
                *value=countr;
        }
        else{
                printf("Enter beli atau exit\n");
		//send(new_socket,no,strlen(no),0);
        }
        //printf("%s\n",buffer);
        memset(buffer,0,strlen(buffer));
        //printf("%s\n",buffer);
    }
return 0;
}
