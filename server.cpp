#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <pthread.h>

int listenfd = 0, connfd[4] = {0};
struct sockaddr_in serv_addr; 
char recvBuff[100];
time_t ticks; 
int numTrackers = 4;

void *server(void *id_data)
{
  int sender_id = *((int*)id_data);
  printf("Started server 1--4\n");
  while (1)
  {

	int n = 0;
	if ((n = read(connfd[sender_id], recvBuff, sizeof(recvBuff) - 1)) > 0)
	{		
		recvBuff[n] = 0;
		printf("Sender ID: %d    Receiver ID: %s\n", sender_id, recvBuff);
		int receiver_id = (int)recvBuff[0] - 48;
			
		char* sendBuff = "SIG";
		write(connfd[receiver_id], sendBuff, sizeof(sendBuff) - 1);
		}
  }
}

int main(int argc, char *argv[])
{
    

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(recvBuff, '0', sizeof(recvBuff));  

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 
    printf("Server Listening...\n");

    for (int i=0; i<numTrackers; i++)
    {
        connfd[i] = accept(listenfd, (struct sockaddr*)NULL, NULL);
        printf("Accepted connection!\n");         
     }
    
     printf("All Trackers Ready...\n");

     pthread_t threads[4];
     int thread_id[4];
     for (int i =0; i<numTrackers; i++)
     {
     int *sender_id = new int;
     *sender_id	 = i; 
     if (thread_id[i] = pthread_create(&threads[i], NULL, server, sender_id))
    	{
    		printf("Error starting server thread!!!");
    		return 0;
    	}
     }

     for (int i =0; i<numTrackers; i++)
     {
     pthread_join( threads[i], NULL);
     }


  printf("Server shutdown!!!\n");
}
