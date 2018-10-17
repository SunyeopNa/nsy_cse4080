#include <signal.h> 
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h> 
static void signal_handler(int);
int i, pid1, pid2, status;

int main(int argc, char *argv[], char *env[])
{
	int exit_status;

	// SIG_ERR : Error가 발생하였음을 나타냄
	// SIGUSR1, SIGUSR2 : 프로세스간에 Communicate를 위한 서로 다른 Signal

	// 아래 사용된 signal()에 의해 signal_handler는 SIGUSR1과 SIGUSR2와 연결
	if (signal(SIGUSR1, signal_handler) == SIG_ERR)
	{
		printf("P?ent: Unable to create handler for SIGUSR1\n");
	}
	if (signal(SIGUSR2, signal_handler) == SIG_ERR) 
	{ 
		printf("P?ent: Unable to create handler for SIGUSR2\n"); 
	}

	printf("Parent pid = %d\n", pid1 = getpid());

	// 현재 프로세스에 대해 fork()를 진행
	if ((pid2 = fork()) == 0) 
	{
		// Child 분기
		// pid1(Parent)에게 SIGUSR1 signal을 보냄
		// 이때 SIGUSR1는 signal_handler(int)와 연결됨
		printf("Child pid = %d\n", getpid());         
		printf("Child: sending parent SIGUSR1\n", getpid());
		kill(pid1, SIGUSR1);             
		for (;;);
	}
	else {         

		// Parent가 Child 가 종료되는 것을 기다린다.
		wait(&status);

		// process 종료상태 분기. process 종료가 정상종료인지 그렇지 않은 경우인지의 분기.
		if (WIFEXITED(status)) {             
			/*               
			* Now we know the process exited properly so we can get the              
			* return value              
			*              
			* Note that WEXITSTATUS only retuns the lower 8 bits!  That means              
			* that if we ever expect a negative number then we have to count              
			* the 8th bit as a sign bit.              
			*/
			exit_status = WEXITSTATUS(status);
			/*               
			* Since we expect negative numbers...              
			*              
			* If the exit_status is greater than 2^7 (128), th? the eigth bit              
			* is a 1, so we subtract 2^8 (256) from it to make it look like               
			* a negative number.              
			*/             
			if (exit_status > 128) { exit_status -= 256; }
			printf("Child return - %d\n", WEXITSTATUS(status));
		}
		else {  
			/* Well it didn't exit properly.  Was it a signal? */             
			if (WIFSIGNALED(status)) 
			{                 
				/*                   
				* Yes. A signal killed the child process.  Now we can extract                  
				* the signal information from status                  
				*/                                  
				printf("Child died on signal - %d\n", WTERMSIG(status));
			} 
		}

		/*           
		* There are two other macros most UNIXes use.  They are:          
		*  WIFSTOPPED() and WSTOPSIG().  See the man pages on the dells for          
		*  more information.          
		*          
		*  To wait on a particular pid - see waitpid()          
		*/
	}
	return 0;
}

static void signal_handler(int signo)
{
	/* signo contains the signal number that was received */
	switch (signo)
	{
	/* Signal is a SIGUSR1 */
	case SIGUSR1:
		printf("Process %d: received SIGUSR1 \n", getpid());
		/* it is the parent */
		if (pid1 == getpid())	
		{
			printf("Process %d is passing SIGUSR1 to %d...\n", getpid(), pid2);
			kill(pid2, SIGUSR1);
		}
		/* it is the child */
		else 
		{
			printf("Process %d is passing SIGUSR2 to itself...\n", getpid());
			kill(getpid(), SIGUSR2);
		}
		break;
	/*  It's a SIGUSR2 */
	case SIGUSR2:
		printf("Process %d: received SIGUSR2 \n", getpid());
		/* it is the parent */
		if (pid1 == getpid()) 
		{
			printf("Process %d is passing SIGUSR2 to %d...\n", getpid(), pid2);
			kill(pid2, SIGUSR2);
		}
		/* it is the child */
		else 
		{
			//printf("Process %d will terminate itself using SIGINT\n", getpid());
			//kill(getpid(), SIGINT);

			printf("child will return properly using \"exit(0)\"\n");
			exit(0);
			return;
		}
		break;
	default:                 
		break;
	}
	return;
}