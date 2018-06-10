#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
//#include<cstdlib>
#include<time.h>



int arr[64];
int pos1=1;
int pos2=1;
	
int win=0;

int player1()
{
	int min1=1;
	int max1=6;
	int dice;
	dice=(min1 +(rand()%(max1-min1+1))); 
		printf("dice value for palyer 1 is %d\n",dice);
	//printf("position 1 = %d\n",pos1);
	if(pos1+dice>1&&pos1+dice<=64)
			{
				pos1=pos1+dice;
				if(pos1==64)
				{
					win =1;
					printf("\nPlayer 1 wins");
					
				}
					printf("1 player position is = %d\n",pos1);
				if(pos1+arr[pos1]>=1&&pos1+arr[pos1]<=64)
				{
					pos1=pos1+arr[pos1];
				}
				if(pos1==64)
				{
					win =1;
					printf("\nPlayer 1 wins");
					
				}
				
			}
				printf("1 player position is = %d\n",pos1);
	return dice;
}

void player2(int d)
{
	
	int min1=1;
	int max1=6;
	int dice;
	dice=d;
			printf("dice value for player 2 is %d\n",dice);
			if(pos2+dice>1&&pos2+dice<=64)
			{
				pos2=pos2+dice;
				if(pos2==64)
				{
					win =1;
				printf("\nPlayer 2 wins");
					
				}
			printf("2 player position is = %d\n",pos2);
				if(pos2+arr[pos2]>=1&&pos2+arr[pos2]<=64)
				{
					pos2=pos2+arr[pos2];
				}
				if(pos2==64)
				{
					win =1;
					printf("\nPlayer 2 wins");
					
				}
				
			}
			printf("2 player position is = %d\n",pos2);
			
}

void value()
{
	int i;
int max_value =10;
int min_value =-10;
	srand(time(NULL));
	printf("\n");
	for(i=1;i<=64;i++)
	{
		arr[i]=(min_value +(rand()%(int)(max_value-min_value+1)));

		
	}
	arr[1]=100;
	/*for( i=1;i<=64;i++)
	{
		printf("\t %d \t",arr[i]);
	}*/
	
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
	exit(1);
}

int main(int argc, char *argv[])
{
 	if(argc<2)
	{
		fprintf(stderr, "Port no. not provided. Program terminated\n");
		exit(1);
	}

	int sockfd, newsockfd, portno,n;
       // char buffer[255];
        struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;
	
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if(sockfd<0)
	{
		error("Error opening socket");
	}

//	bzero((char *) &serv_addr,sizeof(serv_addr));
	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
		error("Binding Failed.");

	listen(sockfd , 5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if(newsockfd<0)
	error("Error on accept");
	value();
	//int i=64;
	int j;
	int n1;
	int n2;
	for( j=1;j<=64;j++)
	{
		 n1 = arr[j];
		n2=write(newsockfd,&n1,sizeof(int));
		if(n2<0)
		{
			printf("\nerror in Writing");
		}
	}
	printf("\nWELCOME TO SNAKE AND LADDER GAME");
	printf("\nYou Are Player 1");
	display();
	while(win!=1)
	{
		n1=player1();
	//printf("\tn1 for server=%d\n",n1);
		n2=write(newsockfd,&n1,sizeof(int));
//printf("\tn2 for server=%d\n",n2);
		if(n2<0)
		{
			printf("\nerror in Writing");
		}
{
		n1=read(newsockfd,&n2,sizeof(int));
//printf("\tn1 from client=%d\n",n1);
		if(n1<0)
		{
			printf("\nError in reading");
		}
else{
		player2(n2);}}
	}
	
	close(newsockfd);
	close(sockfd);
	return 0;

}
