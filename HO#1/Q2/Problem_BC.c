#include <stdio.h>
#include <pthread.h>

// 함수의 매개변수가 pointer형이지만, 이는 입력으로
// 주소값이 오길 기대할 때 사용한다. 하지만 해당 예제에서는
// 매개변수로 정수값을 입력하였다.

// 결과적으로는 main과 두개의 생성된 스레드 모두 서로
// 공유하는 메모리를 갖지 않아 race 상태가 아니다.
void *foo(void *vargp)
{
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
	// 해당 예제에서는 다른 메모리를 참조하므로 join과는 무관
	pthread_join(tid[0], 0);
	pthread_join(tid[1], 0);
}
