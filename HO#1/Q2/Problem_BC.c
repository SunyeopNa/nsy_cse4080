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
		// reference ���°� �ƴ� �� �����̹Ƿ�
		// main, �� ������ ��� �ٸ� �޸𸮸� ���� �ȴ�.
		pthread_create(&tid[i], 0, foo, i);
	pthread_join(tid[0], 0);
	pthread_join(tid[1], 0);
}
