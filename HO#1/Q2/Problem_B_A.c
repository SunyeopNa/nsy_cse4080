#include <stdio.h>
#include <pthread.h>

void *foo(void *vargp)
{
	int myid; myid = *((int *)vargp);
	Free(vargp);
	printf("Thread %d\n", myid);
}

int main()
{
	pthread_t tid[2];
	int i, *ptr;
	for (i = 0; i < 2; i++)
	{
		ptr = Malloc(sizeof(int));
		*ptr = i;
		Pthread_create(&tid[i], 0, foo, ptr);
	}
	Pthread_join(tid[0], 0);
	Pthread_join(tid[1], 0);
}
