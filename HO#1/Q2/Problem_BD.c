#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>


sem_t s;
/* semaphore s */
void *foo(void *vargp)
{
	int id;
	id = *((int *)vargp);
	// id에 매개변수를 입력하고 난 다음에야
	// vargp(main()에서의 i)에 대해서 다른 thread가 접근할 수 있다.
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
		
		// main은 다음 반복을 진행하지 않고
		// 위에서 생성한 스레드가 signal을 보낼 때 까지 대기한다.
		sem_wait(&s);
		// 이후에 새로운 thread가 생성되므로 race가 일어나지 않는다.
	}
	pthread_join(tid[0], 0);
	pthread_join(tid[1], 0);
}