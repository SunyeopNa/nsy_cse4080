#include <stdio.h>
#include <pthread.h>

void *thread(void *vargp)
{
	pthread_exit((void*)42);
}

int main()
{
	int i; 
	pthread_t tid;
	// Thread 생성. ID는 &tid을 통해 알 수 있으며, *thread 라는 함수를 생성
	pthread_create(&tid, NULL, thread, NULL);
	// tid의 thread가 종료될 때 까지 멈춤
	// i는 pthread_exit()를 통해 pass된 값
	pthread_join(tid, (void **)&i);

	printf("%d\n", i);
}