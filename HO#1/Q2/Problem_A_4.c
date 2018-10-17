#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread(void *vargp)
{
	// pthread_detach�� ���� ������ ���� ���̴�
	// �����尡 ����� ���Ŀ� �������� �ڿ��� �����ϴ� Ÿ�̹��̴�.

	// detach�� �ϰԵǸ� join�� ������ �ʾƵ� �����尡 ������ �ڿ��� �����ϸ�
	// �׷��� ���� ��� join�� ������ �� �ڿ��� �����Ѵ�.
	pthread_detach(pthread_self());

	pthread_exit((void*)42);
}

int main()
{
	int i = 0;
	pthread_t tid;
	pthread_create(&tid, NULL, thread, (void*)&i);
	sleep(1);
	pthread_join(tid, (void**)&i);
	printf("%d\n", i);
}

