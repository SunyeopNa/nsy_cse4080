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
	// Thread ����. ID�� &tid�� ���� �� �� ������, *thread ��� �Լ��� ����
	pthread_create(&tid, NULL, thread, NULL);
	// tid�� thread�� ����� �� ���� ����
	// i�� pthread_exit()�� ���� pass�� ��
	pthread_join(tid, (void **)&i);

	printf("%d\n", i);
}