#include <stdio.h>
#include <pthread.h>


void *thread(void *vargp)
{
	int *ptr = (int*)vargp;
	// ���޹��� ��(���������� 42)�� �״�� join �Ű������� �����ϰ� �ȴ�.
	pthread_exit((void*)*ptr);
}

void *thread2(void *vargp)
{
	int *ptr = (int*)vargp;
	// *�� ���� dereference �ϱ� ������ main�� i���� ����ȴ�.
	*ptr = 0;
	
	// main�� join������ 31�� �ް� �� ������ NULL�̱� ������ �� �Ű����� 31�� ���õȴ�.
	pthread_exit((void*)31);

}

int main()
{
	int i = 42;
	pthread_t tid, tid2;
	// thread() �����带 �����ϸ鼭 i���� �ּҰ� ���޵ȴ�.
	pthread_create(&tid, NULL, thread, (void*)&i);
	// thread2() �����带 �����ϸ鼭 i���� �ּҰ� ���޵ȴ�.
	pthread_create(&tid2, NULL, thread2, (void*)&i);

	// join�� �ݵ�� ������� �Ͼ����, thread2() ������ *ptr = 0�� ����
	// ����Ǵ����� ���� ������ �� ����.
	pthread_join(tid, (void**)&i);
	pthread_join(tid2, NULL);
	printf("%d\n", i);
}