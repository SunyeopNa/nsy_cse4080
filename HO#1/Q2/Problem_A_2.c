#include <stdio.h>
#include <pthread.h>

void *thread(void *vargp)
{
	// thread는 child process 개념이 아니기 때문에
	// 아래의 line이 실행되면 프로세스 자체가 종료된다.
	// 따라서 main()의 pthread_join 이후의 print는 진행되지 않는다
	exit(42);
}

int main()
{
	int i;
	pthread_t tid;
	pthread_create(&tid, NULL, thread, NULL);
	pthread_join(tid, (void **)&i);
	// 여기에 도달하지 못하고 exit에 의해 프로세스 자체가 종료된다.
	printf("%d\n", i);
}
