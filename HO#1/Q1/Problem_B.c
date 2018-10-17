#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h> 
#include <unistd.h> 

void HandleSignal(int sig, siginfo_t *si, void *context); 
int main(int argc, char *argv[])
{
	struct sigaction sVal;
	pid_t myPID;
	pid_t myG_PID;
	// 기본값인 sa_handler의 경우 signum 하나의 인자를 사용할 수 있다. 이를 SA_SIGINFO로 바꾸면
	// siginfo_t 구조체를 활용할 수도 있다.
	sVal.sa_flags = SA_SIGINFO;
	sVal.sa_sigaction = HandleS
	// PID를 가져온다
	myPID = getpid();
	// PGID = Process Group ID
	// getpgid() : 인자로 받은 PID의 PGID를 얻는다.
	myG_PID = getpgid(myPID);
	printf("\nMy process id = %d.\n", myPID);
	printf("My process group id = %d.\n", myG_PID);
	if (fork() == 0)
	{
		myPID = getpid();
		myG_PID = getpgid(myPID);
		printf("\nChild: My process id = %d.\n", myPID);
		printf("Child: My process group id = %d.\n", myG_PID);
		
		// setpgid() : 이 process를 포함하는 Process Group을 생성    
		setpgid(0, 0);
		myPID = getpid();
		myG_PID = getpgid(myPID);
		printf("\nChild: My process id = %d.\n", myPID);
		printf("Child: My process group id = %d.\n", myG_PID);

		return (0);
	}
	else
	{
		// Register for SIGINT       
		sigaction(SIGINT, &sVal, NULL);

		// Register for SIGCHLD 
		sigaction(SIGCHLD, &sVal, NULL);
		myPID = getpid();
		myG_PID = getpgid(myPID);

		printf("\nParent: My process id = %d.\n", myPID);
		printf("Parent: My process group id = %d.\n", myG_PID);
		while (1)
		{
		}
	}
	return(0);
}

void HandleSignal(int sig, siginfo_t *si, void *context)
{
	switch (sig)
	{
	case SIGINT:
		printf("\nControl-C was pressed: mypid = %d, mypgid = %d\n", getpid(), getpgid(getpid()));
		_exit(0);
		break;
	case SIGCHLD:
		printf("\nSIGCHLD. mypid = %d, mypgid = %d\n", getpid(), getpgid(getpid()));
		if (si->si_code == CLD_EXITED || si->si_code == CLD_KILLED)
		{
			printf("   Process %d is done!\n", si->si_pid);
		}
		break;
	}
}
