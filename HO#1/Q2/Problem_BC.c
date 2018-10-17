#include <stdio.h>
#include <pthread.h>

void *foo(void *vargp)
{
	vargp = 1000;
	int id;
	id = (int)vargp;
	printf("Thread %d\n", id);
}

int main()
{
	pthread_t tid[2];
	int i;
	for (i = 0; i < 2; i++)
		// reference 형태가 아닌 값 복사이므로
		// main, 두 스레드 모두 다른 메모리를 보게 된다.
		pthread_create(&tid[i], 0, foo, i);
	pthread_join(tid[0], 0);
	pthread_join(tid[1], 0);
}
