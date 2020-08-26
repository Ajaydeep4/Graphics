#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define port 8090

int clientCount = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct client{

	int index;
	int sockID;
	//int interest;
	
	struct sockaddr_in clientAddr;
	int len;

};
int interest[1024][1024];
//char interest;
int count = 0;
struct client Client[1024];
pthread_t thread[1024];

void * func(void * ClientDetail){

	count++;

	struct client* clientDetail = (struct client*) ClientDetail;
	int index = clientDetail -> index;
	int clientSocket = clientDetail -> sockID;

	printf("Client %d connected.\n",index + 1);

	while(1){

		char data[1024];
		int n[1024];
		int read = recv(clientSocket,&n[index],1024,0);
		//data[read] = '\0';
		int id;
		
		// if(strcmp(data,"LIST
		//if(strcmp(data,"SEND") == 0)
		{
			for (int i = 0; i < n[index]; ++i)
			{
				read = recv(clientSocket,data,1024,0);
				data[read] = '\0';

			

			 id = atoi(data) - 1;

				interest[index][i]=id;
			}
			//clientDetail->interest=id;
			//strcpy(clientDetail->interest, data);

			read = recv(clientSocket,data,1024,0);
			data[read] = '\0';
			if(strcmp(data,"SEND") == 0)
			{
				read = recv(clientSocket,data,1024,0);
			data[read] = '\0';
			


			id = atoi(data) - 1;
			//char intr[1024];
			char ss[1];
			ss[0]=index;
			//strcpy(ss)
read = recv(clientSocket,data,1024,0);
					data[read] = '\0';

			for(int i=0; i<index; ++i)
			{
				for (int i = 0; i < n[index]; ++i)
				{


					if(interest[i][index] == id)
					{
						
						send(Client[i].sockID,ss,1024,0);
						send(Client[i].sockID,data,1024,0);			
					}
				}
			}

		}

	}
}

	return NULL;

}

int main(){

	int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htons(INADDR_ANY);


	if(bind(serverSocket,(struct sockaddr *) &serverAddr , sizeof(serverAddr)) == -1) return 0;

	if(listen(serverSocket,1024) == -1) return 0;

	//printf("Server started listenting on port 8080 ...........\n");

	while(1){

		Client[clientCount].sockID = accept(serverSocket, (struct sockaddr*) &Client[clientCount].clientAddr, &Client[clientCount].len);
		Client[clientCount].index = clientCount;

		pthread_create(&thread[clientCount], NULL, func, (void *) &Client[clientCount]);

		clientCount ++;
 
	}

	for(int i = 0 ; i < clientCount ; i ++)
		pthread_join(thread[i],NULL);

}