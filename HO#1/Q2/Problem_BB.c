#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *foo(void *vargp)
{
	int id;
	// ���� �����ϱ� ������ i����
	// main�� for�� �ݺ� Ƚ���� ���� �޶�����.
	id = *((int *)vargp);

	//���� ��°���� ������ �� ����.
	printf("Thread %d\n", id);
}

int main()
{
	pthread_t tid[2];
	int i;

	// i�� for �� �ȿ��� 0,1,2 ������ �����Ѵ�.
	// �̶� ù��° �ݺ������� �����Ǵ� thread��
	// thread ���� �ڵ� ���� �� ����
	// 0,1,2 ��� ���� ����� �� �ִ�.
	// �ι�° �ݺ������� �����Ǵ� thread ����
	// ù��° �ݺ������� �����Ǵ� thread�� ��� �̻�, 2 ������ ����
	// ����� �� �ִ�.
	for (i = 0; i < 2; i++)
	{
		// �ΰ��� ������� ���� ���� i(�ּ�)�� �Ű������� ������
		pthread_create(&tid[i], NULL, foo, &i);

	}
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
}