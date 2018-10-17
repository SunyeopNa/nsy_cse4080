#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread(void *vargp)
{
	// pthread_detach의 존재 유무에 따른 차이는
	// 스레드가 종료된 이후에 스레드의 자원을 해제하는 타이밍이다.

	// detach를 하게되면 join을 만나지 않아도 스레드가 끝나면 자원을 해제하며
	// 그렇지 않을 경우 join을 만났을 때 자원을 해제한다.
	pthread_detach(pthread_self());

	pthread_exit((void*)42);
}

int main()
{
	int i = 0;
	pthread_t tid;
	pthread_create(&tid, NULL, thread, (void*)&i);
	sleep(1);
	pthread_join(tid, (void**)&i);
	printf("%d\n", i);
}

