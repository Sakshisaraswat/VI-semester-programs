#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include <semaphore.h>
#include <pthread.h>
//#include <string.h>
//#include <sys/wait.h>
//#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>


sem_t *sp01, *sp02, *sp03, *sp04,*forks1;

int count=5;

void process(int i)
{ 
	printf("in child\n");

	  while(count>0)
	  {
	        if(i==0||i==1)                //for process number 1 and 2
		{ sleep(1);
		     printf("\n %d philosopher is hungry",i+1);
		     if(sem_wait(sp01)==0)
		     {
	                sem_wait(forks1);
			printf("\n%d philosopher is eating with spoon 1 and fork",i+1);
                        count--;
			sleep(3);
		        sem_post(forks1);
		        if(sem_post(sp01)==0)
			printf("\n %d philosopher is thinking",i+1);
		        sleep(3);	
		      }
		 }


		 if(i==2||i==3)          //for process number 3 and 4
		  {sleep(1);
		       printf("\n %d philosopher is hungry",i+1);
		       if(sem_wait(sp02)==0)
		       {
	                   sem_wait(forks1);
			   printf("\n%d philosopher is eating with spoon 2 and fork",i+1);count--;
		           sleep(3);
		           sem_post(forks1);
		           if(sem_post(sp02)==0)
			     printf("\n %d philosopher is thinking",i+1);
			     sleep(3);	
			}
		  }


		 if(i==4||i==5)
	         {sleep(1);
		      printf("\n %d philosopher is hungry",i+1);
		      if(sem_wait(sp03)==0)
		       {
		           sem_wait(forks1);
			   printf("\n%d philosopher is eating with spoon 3 and fork",i+1);count--;
		           sleep(3);
		           sem_post(forks1);
		           if(sem_post(sp03)==0)
			     printf("\n %d philosopher is thinking",i+1);
			     sleep(3);	
			}
		}

		 if(i==6||i==7)
		  {sleep(1);
		        printf("\n %d philosopher is hungry",i+1);
			if(sem_wait(sp04)==0)
			{
			   sem_wait(forks1);
		           printf("\n%d philosopher is eating with spoon 4 and fork",i+1);count--;
		           sleep(3);
		           sem_post(forks1);
		           if(sem_post(sp04)==0)
			   printf("\n %d philosopher is thinking",i+1);
		           sleep(3);	
			}
		 }	
	} //while loop closed


}



int main()
{

		 
		sp01 = sem_open("/spoons001",O_CREAT | O_EXCL, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP),1);
		sp02 = sem_open("/spoons002",O_CREAT | O_EXCL, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP),1);
		sp03 = sem_open("/spoons003",O_CREAT | O_EXCL, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP),1);
		sp04 = sem_open("/spoons004",O_CREAT | O_EXCL, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP),1);
                forks1 = sem_open("/forks05",O_CREAT | O_EXCL, (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP),5);
	       	  int i; 
		  pid_t pid;
		  for(i=0;i<8;i++)
		  {
		    pid = fork();
		     if(pid==0)
		    {
		      
		     
		      break;
		    }
		    else if(pid<0)
		    {
		    	//unlink()
		      perror("Child process can't be created");
		      _exit(0);
		    }
		  
		  }
		  if (pid==0)
		{
			 process(i);
			 exit(0);
		}
		  else if(pid!=0)
		  {
		  	while(pid=waitpid(-1,NULL,0))
		  	{
		  		if(errno==ECHILD)
		  			break;
		  	}
		  	printf("child done\n");
		  	sem_unlink("/spoons001");
		  	 sem_close(sp01);
			sem_unlink("/spoons002");
			sem_close(sp02);
			sem_unlink("/spoons003");
			 sem_close(sp03);
			sem_unlink("/spoons004");
			 sem_close(sp04);
			sem_unlink("/forks05");
		  	

 					
                   
                  
                  
                   sem_close(forks1);
                   exit(0);

		  }
                 

		


		return 0;
}



