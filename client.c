#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
int arr[64];
int pos1=1;
int pos2=1;

int win=0;
void player1(int d)
{
	int min1=1;
	int max1=6;
	int dice;
	dice=d; 
		printf("dice value for palyer 1 is %d\n",dice);
//	if(win!=1){	printf("position 1 = %d\n",pos1);}
	if(pos1+dice>1&&pos1+dice<=64)
			{
				pos1=pos1+dice;
				if(pos1==64)
				{
					win =1;
					printf("\nPlayer 1 wins");
					//exit(0);
				}
					printf("1 player position is = %d\n",pos1);
				if(pos1+arr[pos1]>=1&&pos1+arr[pos1]<=64)
				{
					pos1=pos1+arr[pos1];
				}
				if(pos1==64 )
				{
					win =1;
					printf("\nPlayer 1 wins");
					//exit(0);
				}
				
			}
			
						printf("1 player position is = %d\n",pos1);
	
}

int player2()
{
	
	int min1=1;
	int max1=6;
	int dice;
	dice=(min1 +(rand()%(max1-min1+1)));
				printf("dice value for player 2 is %d\n",dice);

			if(pos2+dice>1&&pos2+dice<=64)
			{
				pos2=pos2+dice;
				if(pos2==64)
				{
					win =1;
					printf("\nPlayer 2 wins");
					//exit(0);
				}
						printf("2 player position is = %d\n",pos2);
				if(pos2+arr[pos2]>=1&&pos2+arr[pos2]<=64)
				{
					pos2=pos2+arr[pos2];
				}
				if(pos2==64 )
				{
					win =1;
					printf("\nPlayer 2 wins");
					//exit(0);
				}
				
			}
				printf("2 player position is = %d\n",pos2);
			return dice;
}

void display()
{	int i=64;
	int count=0;
	int c1=0; 
	printf("\n\n\n");
printf("__________________________________________________________________________________________________________________________________\n");
	while(i>0)
	{
	
		while(count<8)
		{
		
			printf("|\t%d\t|",arr[i]);
			i--;
			count++;

		}
printf("\n__________________________________________________________________________________________________________________________________\n");
		if(count>=8)
		{
			c1=0;
			i=i-7;
			while(c1<8)
			{
			printf("|\t%d\t|",arr[i]);
			i++;
			c1++;

		
			}
		
printf("\n__________________________________________________________________________________________________________________________________");
		}
			if(c1==8)
			{
				count=0;
				i=i-9;
			
			}
		printf("\n");

	}
	
}
void error(const char *msg)
{
perror(msg);
exit(0);
}

int main(int argc ,char *argv[])
{  
   int sockfd,portno,n,newsockfd;
   struct sockaddr_in serv_addr;
   struct hostent *server;

 

  //// char buffer[9];
   //char val[9];

    if(argc<3)
    { 
     fprintf(stderr,"PORT NO. NOT PROVIDED");
     exit(1);
    }
 portno=atoi(argv[2]);
 sockfd=socket(AF_INET,SOCK_STREAM,0);
   if(sockfd<0)
      error("ERROR OPENING SOCKET");
   
  server=gethostbyname(argv[1]);
   if(server==NULL)
   {
      fprintf(stderr,"ERROR ,NO SUCH HOST");
    }
   
  // bzero((char*) & serv_addr,sizeof(serv_addr));
   serv_addr.sin_family=AF_INET;
  bcopy((char*) server->h_addr, (char*)&serv_addr.sin_addr.s_addr,server->h_length);
  serv_addr.sin_port=htons(portno);
  

  if(connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0)
  error("CONNECTION FAILED");

int i=1;
int n1,n2;
for(i=1;i<=64;i++)
{
	n1=read(sockfd,&n2,sizeof(int));
	if(n1<0)
	{
		printf("\nError in reading");
	}
	arr[i]=n2;
}
/*for(i=1;i<=64;i++)
{
	printf("\t%d",arr[i]);
}*/
printf("\nWELCOME TO SNAKE AND LADDER GAME");
	printf("\nYou Are Player 2");
display();
while(win!=1)
{
	n1=read(sockfd,&n2,sizeof(int));
	if(n1<0)
	{
		printf("\nError in reading");
	}
else{	player1(n2);}
{	n1=player2();

		n2=write(sockfd,&n1,sizeof(int));
		if(n2<0)
		{
			printf("\nerror in Writing");
		}}
}
}
