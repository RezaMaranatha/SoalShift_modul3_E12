#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

pthread_t id1, id2,id3,id4,id5,id6;
int s1,s2,s3,s4,s5,s6;
int status;

void* simpan1(void *arg){
	s3=0;
//	while(s1!=1){
	
//	}
	chdir("/home/reza/Documents/FolderProses1");
        system("ps aux | head -n 10 > SimpanProses1.txt");
	s3=1;
	//return NULL;
}

void* simpan2(void *arg){
        s4=0;
//	while(s2!=1);

//	}
	chdir("/home/reza/Documents/FolderProses2");
        system("ps aux | head -n 10 > SimpanProses2.txt");
        s4=1;
}

void* kompres1(void *arg){
        s5=0;
        while(s3!=1){
        
	}
	chdir("/home/reza/Documents/FolderProses1");
	system("zip KompresProses1.zip SimpanProses1.txt && rm SimpanProses1.txt");
        printf("\nMenunggu 15 detik untuk mengekstrak kembali\n");
	s5=1;
	sleep(15);
}

void* kompres2(void *arg){
        s6=0;
        while(s4!=1){

        }
	chdir("/home/reza/Documents/FolderProses2");
        system("zip KompresProses2.zip SimpanProses2.txt && rm SimpanProses2.txt");
	printf("\nMenunggu 15 detik untuk mengekstrak kembali\n");
	s6=1;
	sleep(15);
}

void* decom1(void *arg){
        while(s5!=1){

        }
	chdir("/home/reza/Documents/FolderProses1");
	system("unzip KompresProses1.zip");
}

void* decom2(void *arg){
        while(s6!=1){

        }
	chdir("/home/reza/Documents/FolderProses2");
	system("unzip KompresProses2.zip");
}

int main(void){
	char a[100];
	char b[100];
	strcpy(a,"/home/reza/Documents/FolderProses1");
	strcpy(b,"/home/reza/Documents/FolderProses2");	

	mkdir(a,S_IRWXU | S_IRWXG | S_IRWXO);
	mkdir(b,S_IRWXU | S_IRWXG | S_IRWXO);
	
	pthread_create(&id1, NULL,simpan1, NULL);
	pthread_create(&id2, NULL,simpan2, NULL);
	pthread_create(&id3, NULL,kompres1, NULL);
	pthread_create(&id4, NULL,kompres2, NULL);
	pthread_create(&id5, NULL,decom1, NULL);
	pthread_create(&id6, NULL,decom2, NULL);


	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	pthread_join(id3, NULL);
	pthread_join(id4, NULL);
	pthread_join(id5, NULL);
	pthread_join(id6, NULL);
 //system("mkdir /home/reza/Documents/FolderProses1");
    return 0;
}

