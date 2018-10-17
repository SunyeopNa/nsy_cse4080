#include <stdio.h>
#include <pthread.h>

// �Լ��� �Ű������� pointer��������, �̴� �Է�����
// �ּҰ��� ���� ����� �� ����Ѵ�. ������ �ش� ����������
// �Ű������� �������� �Է��Ͽ���.

// ��������δ� main�� �ΰ��� ������ ������ ��� ����
// �����ϴ� �޸𸮸� ���� �ʾ� race ���°� �ƴϴ�.
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
		// reference ���°� �ƴ� �� �����̹Ƿ�
		// main, �� ������ ��� �ٸ� �޸𸮸� ���� �ȴ�.
		pthread_create(&tid[i], 0, foo, i);
	// �ش� ���������� �ٸ� �޸𸮸� �����ϹǷ� join���� ����
	pthread_join(tid[0], 0);
	pthread_join(tid[1], 0);
}
