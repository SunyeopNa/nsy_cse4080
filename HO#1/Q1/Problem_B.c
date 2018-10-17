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
	// �⺻���� sa_handler�� ��� signum �ϳ��� ���ڸ� ����� �� �ִ�. �̸� SA_SIGINFO�� �ٲٸ�
	// siginfo_t ����ü�� Ȱ���� ���� �ִ�.
	sVal.sa_flags = SA_SIGINFO;
	sVal.sa_sigaction = HandleS
	// PID�� �����´�
	myPID = getpid();
	// PGID = Process Group ID
	// getpgid() : ���ڷ� ���� PID�� PGID�� ��´�.
	myG_PID = getpgid(myPID);
	printf("\nMy process id = %d.\n", myPID);
	printf("My process group id = %d.\n", myG_PID);
	if (fork() == 0)
	{
		myPID = getpid();
		myG_PID = getpgid(myPID);
		printf("\nChild: My process id = %d.\n", myPID);
		printf("Child: My process group id = %d.\n", myG_PID);
		
		// setpgid() : �� process�� �����ϴ� Process Group�� ����    
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
