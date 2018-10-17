#include <signal.h> 
#include <stdio.h>
#include <sys/wait.h>
#include <errno.h> 
static void signal_handler(int);
int i, pid1, pid2, status;

int main(int argc, char *argv[], char *env[])
{
	int exit_status;

	// SIG_ERR : Error�� �߻��Ͽ����� ��Ÿ��
	// SIGUSR1, SIGUSR2 : ���μ������� Communicate�� ���� ���� �ٸ� Signal

	// �Ʒ� ���� signal()�� ���� signal_handler�� SIGUSR1�� SIGUSR2�� ����
	if (signal(SIGUSR1, signal_handler) == SIG_ERR)
	{
		printf("P?ent: Unable to create handler for SIGUSR1\n");
	}
	if (signal(SIGUSR2, signal_handler) == SIG_ERR) 
	{ 
		printf("P?ent: Unable to create handler for SIGUSR2\n"); 
	}

	printf("Parent pid = %d\n", pid1 = getpid());

	// ���� ���μ����� ���� fork()�� ����
	if ((pid2 = fork()) == 0) 
	{
		// Child �б�
		// pid1(Parent)���� SIGUSR1 signal�� ����
		// �̶� SIGUSR1�� signal_handler(int)�� �����
		printf("Child pid = %d\n", getpid());         
		printf("Child: sending parent SIGUSR1\n", getpid());
		kill(pid1, SIGUSR1);             
		for (;;);
	}
	else {         

		// Parent�� Child �� ����Ǵ� ���� ��ٸ���.
		wait(&status);

		// process ������� �б�. process ���ᰡ ������������ �׷��� ���� ��������� �б�.
		if (WIFEXITED(status)) {             
			exit_status = WEXITSTATUS(status);      
			if (exit_status > 128) { exit_status -= 256; }
			printf("Child return - %d\n", WEXITSTATUS(status));
		}
		else {  
			/* Well it didn't exit properly.  Was it a signal? */             
			if (WIFSIGNALED(status)) 
			{                                                 
				printf("Child died on signal - %d\n", WTERMSIG(status));
			} 
		}
	}
	return 0;
}

static void signal_handler(int signo)
{
	// signal_handler�� main()����  signal()�� ���� SIGUSR1, SIGUSR2�� ����ȴ�.
	// switch���� ���� SIGUSR1�� SIGUSR2�� � signal�� ����
	// �ڵ鷯�� ȣ��� ������ �б⸦ ������ �ִ�.
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
			printf("Process %d will terminate itself using SIGINT\n", getpid());
			kill(getpid(), SIGINT);

			// ���� �ڵ� ��� �Ʒ��� �ڵ带 �̿��� child�� ���� ���Ḧ �����ϸ�
			// parent�� �ٸ� �б⹮���� �̵��ϵ��� �� �� �ִ�.

			//printf("child will return properly using \"exit(0)\"\n");
			//exit(0);
			return;
		}
		break;
	default:                 
		break;
	}
	return;
}