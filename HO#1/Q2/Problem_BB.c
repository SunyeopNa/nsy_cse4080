#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

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
	{
		// 두개의 스레드는 서로 같은 i(주소)를 매개변수로 가진다
		pthread_create(&tid[i], NULL, foo, &i);

	}
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
}