#include <stdio.h>
#include <pthread.h>

// Shared Memory
int i = 42;

void *thread(void *vargp)
{
	printf("%d\n", i);
}

void *thread2(void *vargp)
{
	// thread에 Shared Memory를 접근하는 형태의 코드가 작성되었다.
	i = 31;
}
int main()
{
	pthread_t tid, tid2;
	pthread_create(&tid2, NULL, thread2, (void*)&i);
	pthread_create(&tid, NULL, thread, (void*)&i);
	// thread와 thread2이 각각 어떤 순서로 실행 될 것인지 알 수 없다.
	// 먼저 thread가 실행 되어 i를 출력(42)한 후 thread2가 i를 31로 바꾸는 경우와,
	// 먼저 thread2가 실행되어 i를 31로 바꾼 후 thread1이 i를 출력(31)를 하는 경우가 있다.
	pthread_join(tid, (void**)&i);
	pthread_join(tid2, NULL);
}






