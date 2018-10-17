#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *foo(void *vargp)
{
	// vargp는 0 또는 1
	int myid; 
	myid = *((int *)vargp);
	free(vargp);

	printf("Thread %d\n", myid);
}

int main()
{
	pthread_t tid[2];
	int i, *ptr;
	for (i = 0; i < 2; i++)
	{
		// 메모리 할당
		// 반복문에 의해 두번째 실행 될 때 이전 할당된 메모리에 대해선
		// 더이상 main에서 접근하기는 어렵다

		ptr = malloc(sizeof(int));

		// ptr에는 각각 0,1 값이 입력된다.
		*ptr = i;

		//스레드가 vargp 매개변수로 각각 0,1이 입력되어 생성된다
		pthread_create(&tid[i], 0, foo, ptr);

		// 생성될 두개의 스레드는 확실하게 서로 다른 메모리를 접근하고있다.
	}
	pthread_join(tid[0], 0);
	pthread_join(tid[1], 0);
}
