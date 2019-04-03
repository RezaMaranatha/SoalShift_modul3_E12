#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
  
int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char hello[400];
    char ss[20];
    strcpy(ss,"exit");
    char cek1[10];
    char cek2[10];
    strcpy(cek1,"jual");
    strcpy(cek2,"beli");
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    //read(sock,buffer,1024);
	while(scanf("%s",hello)){
        	send(sock , hello , strlen(hello) , 0 );
        	if(strcmp(ss,hello)==0){
                	break;
        	}
		else if(strcmp(cek2,hello)==0){
                        valread = read(sock , buffer, 1024);
                        printf("%s\n",buffer);
                        memset(buffer,0,strlen(buffer));
                }
		memset(buffer,0,strlen(buffer));
		memset(hello, '\0', strlen(hello));
    	}
    /*else if(strcmp(cek2,buffer)==0){
	memset(buffer,0,strlen(buffer));
	while(scanf("%s",hello)){
        	send(sock , hello , strlen(hello) , 0 );
                if(strcmp(ss,hello)==0){
                        break;
                }
                else if(strcmp(cek2,hello)==0){
			valread = read(sock , buffer, 1024);
                        printf("%s\n",buffer);
			memset(buffer,0,strlen(buffer));
                }
                memset(hello, '\0', strlen(hello));
        }
    }*/
return 0;
}
