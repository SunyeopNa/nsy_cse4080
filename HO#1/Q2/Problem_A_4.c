#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread(void *vargp)
{
	pthread_detach(pthread_self());
	printf("MAKE DELAY 1\n");
	printf("MAKE DELAY 2\n");
	printf("MAKE DELAY 3\n");
	printf("MAKE DELAY 4\n");
	int www = 0;
	for (int i = 0; i < 10000; i++)
	{
		www++;
	}
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

