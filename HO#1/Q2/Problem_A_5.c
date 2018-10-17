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
	// thread�� Shared Memory�� �����ϴ� ������ �ڵ尡 �ۼ��Ǿ���.
	i = 31;
}
int main()
{
	pthread_t tid, tid2;
	pthread_create(&tid2, NULL, thread2, (void*)&i);
	pthread_create(&tid, NULL, thread, (void*)&i);
	// thread�� thread2�� ���� � ������ ���� �� ������ �� �� ����.
	// ���� thread�� ���� �Ǿ� i�� ���(42)�� �� thread2�� i�� 31�� �ٲٴ� ����,
	// ���� thread2�� ����Ǿ� i�� 31�� �ٲ� �� thread1�� i�� ���(31)�� �ϴ� ��찡 �ִ�.
	pthread_join(tid, (void**)&i);
	pthread_join(tid2, NULL);
}






