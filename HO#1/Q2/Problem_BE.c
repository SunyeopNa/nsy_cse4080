#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t s;
/* semaphore s */
void *foo(void *vargp)
{
	int id;
	sem_wait(&s);
	id = *((int *)vargp);
	sem_post(&s);
	printf("Thread %d\n", id);
}

int main()
{
	pthread_t tid[2];
	int i;
	sem_init(&s, 0, 1);
	/* S=1 INITIALLY */
	for (i = 0; i < 2; i++)
	{
		pthread_create(&tid[i], 0, foo, &i);
		sleep(1);
	}
	pthread_join(tid[0], 0);
	pthread_join(tid[1], 0);
}