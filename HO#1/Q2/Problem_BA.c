#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *foo(void *vargp)
{
	// vargp�� 0 �Ǵ� 1
	int myid; 
	myid = *((int *)vargp);
	free(vargp);

	printf("Thread %d\n", myid);
}

int main()
{
	pthread_t tid[2];
	int i, *ptr;
	for (i = 0; i < 2; i++)
	{
		// �޸� �Ҵ�
		// �ݺ����� ���� �ι�° ���� �� �� ���� �Ҵ�� �޸𸮿� ���ؼ�
		// ���̻� main���� �����ϱ�� ��ƴ�

		ptr = malloc(sizeof(int));

		// ptr���� ���� 0,1 ���� �Էµȴ�.
		*ptr = i;

		//�����尡 vargp �Ű������� ���� 0,1�� �ԷµǾ� �����ȴ�
		pthread_create(&tid[i], 0, foo, ptr);

		// ������ �ΰ��� ������� Ȯ���ϰ� ���� �ٸ� �޸𸮸� �����ϰ��ִ�.
	}
	pthread_join(tid[0], 0);
	pthread_join(tid[1], 0);
}
