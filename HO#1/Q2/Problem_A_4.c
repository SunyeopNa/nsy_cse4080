#include <stdio.h>
#include <pthread.h>

void *thread(void *vargp)
{
	pthread_detach(pthread_self());
	printf("MAKE DELAY 1");
	printf("MAKE DELAY 2");
	printf("MAKE DELAY 3");
	printf("MAKE DELAY 4");
	pthread_exit((void*)42);
}

int main()
{
	int i = 0;
	pthread_t tid;
	pthread_create(&tid, NULL, thread, (void*)&i);
	pthread_join(tid, (void**)&i);
	printf("%d\n", i);
}

