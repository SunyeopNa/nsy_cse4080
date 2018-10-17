#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


sem_t s;
/* semaphore s */
void *foo(void *vargp)
{
	int id;
	id = *((int *)vargp);
	// id�� �Ű������� �Է��ϰ� �� ��������
	// vargp(main()������ i)�� ���ؼ� �ٸ� thread�� ������ �� �ִ�.
	sem_post(&s);
	printf("Thread %d\n", id);
}

int main()
{
	pthread_t tid[2];
	int i;
	sem_init(&s, 0, 0);
	/* S=0 INITIALLY */
	for (i = 0; i < 2; i++)
	{
		pthread_create(&tid[i], 0, foo, &i);
		
		// main�� ���� �ݺ��� �������� �ʰ�
		// ������ ������ �����尡 signal�� ���� �� ���� ����Ѵ�.
		sem_wait(&s);
		// ���Ŀ� ���ο� thread�� �����ǹǷ� race�� �Ͼ�� �ʴ´�.
	}
	pthread_join(tid[0], 0);
	pthread_join(tid[1], 0);
}