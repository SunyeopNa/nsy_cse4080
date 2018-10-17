#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *foo(void *vargp)
{
	int id;
	// 값을 복사하기 이전의 i값이
	// main의 for문 반복 횟수에 따라 달라진다.
	id = *((int *)vargp);

	//따라서 출력결과를 예상할 수 없다.
	printf("Thread %d\n", id);
}

int main()
{
	pthread_t tid[2];
	int i;

	// i가 for 문 안에서 0,1,2 순서로 증가한다.
	// 이때 첫번째 반복문에서 생성되는 thread는
	// thread 내부 코드 실행 에 따라
	// 0,1,2 모든 값을 출력할 수 있다.
	// 두번째 반복문에서 생성되는 thread 또한
	// 첫번째 반복문에서 생성되는 thread의 출력 이상, 2 이하의 값을
	// 출력할 수 있다.
	for (i = 0; i < 2; i++)
	{
		// 두개의 스레드는 서로 같은 i(주소)를 매개변수로 가진다
		pthread_create(&tid[i], NULL, foo, &i);

	}
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
}