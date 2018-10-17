#include <stdio.h>
#include <pthread.h>


void *thread(void *vargp)
{
	int *ptr = (int*)vargp;
	// 전달받은 값(예제에서는 42)를 그대로 join 매개변수에 전달하게 된다.
	pthread_exit((void*)*ptr);
}

void *thread2(void *vargp)
{
	int *ptr = (int*)vargp;
	// *를 통해 dereference 하기 때문에 main의 i값이 변경된다.
	*ptr = 0;
	
	// main의 join에서는 31을 받게 될 변수가 NULL이기 때문에 이 매개변수 31은 무시된다.
	pthread_exit((void*)31);

}

int main()
{
	int i = 42;
	pthread_t tid, tid2;
	// thread() 스레드를 생성하면서 i변수 주소가 전달된다.
	pthread_create(&tid, NULL, thread, (void*)&i);
	// thread2() 스레드를 생성하면서 i변수 주소가 전달된다.
	pthread_create(&tid2, NULL, thread2, (void*)&i);

	// join은 반드시 순서대로 일어나지만, thread2() 내부의 *ptr = 0이 언제
	// 실행되는지에 대해 예측할 수 없다.
	pthread_join(tid, (void**)&i);
	pthread_join(tid2, NULL);
	printf("%d\n", i);
}