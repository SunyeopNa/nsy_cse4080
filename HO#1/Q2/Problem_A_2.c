#include <stdio.h>
#include <pthread.h>

void *thread(void *vargp)
{
	// thread�� child process ������ �ƴϱ� ������
	// �Ʒ��� line�� ����Ǹ� ���μ��� ��ü�� ����ȴ�.
	// ���� main()�� pthread_join ������ print�� ������� �ʴ´�
	exit(42);
}

int main()
{
	int i;
	pthread_t tid;
	pthread_create(&tid, NULL, thread, NULL);
	pthread_join(tid, (void **)&i);
	// ���⿡ �������� ���ϰ� exit�� ���� ���μ��� ��ü�� ����ȴ�.
	printf("%d\n", i);
}
