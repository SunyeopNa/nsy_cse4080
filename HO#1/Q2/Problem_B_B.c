#include <stdio.h>
#include <pthread.h>

void *foo(void *vargp)
{
	int id;
	id = *((int *)vargp);
	printf("Thread %d\n", id);
}

int main()
{
	pthread_t tid[2];
	int i;
	for (i = 0; i < 2; i++)
		Pthread_create(&tid[i], NULL, foo, &i);
	Pthread_join(tid[0], NULL);
	Pthread_join(tid[1], NULL);
}