#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char letters[20] = "abcdefghijklmnoprstv";

void* procthread13(void *arg)
{
	const int flag = *(int*)arg;
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	int k, j;
	for (k = 0; k < 20; k++)
	{
		if (flag == 1)
		{
			for (j = 0; j < flag * 2; j++)
			{
				printf("\033[%d;%dH\033[1;34m%c", k + 1, j + 1 + 20, letters[k]);
			}
			usleep(1100000);
		}
		else
		{
			if (k == 12)
			{
				pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
			}
			for (j = 0; j < flag * 2; j++)
			{
				printf("\033[%d;%dH\033[31m%c", k + 1, j + 1 + 60, letters[k]);
			}
			usleep(1200000);
		}
	}
}

void* procthread2(void *arg)
{
	int k, j;
	for (k = 0; k < 20; k++)
	{
		for (j = 0; j < 2 * 2; j++)
		{
			printf("\033[%d;%dH\033[1;32m%c", k + 1, j + 1 + 40, letters[k]);
		}
		usleep(1300000);
	}
}

int main(void)
{
	int k;
	int rc;
	system("clear");
	pthread_t tid1, tid2, tid3;
	int *num1 = malloc(sizeof(int));
	int i;
	*num1 = 1;
	rc = pthread_create(&tid1, NULL, procthread13, num1);
	rc = pthread_create(&tid2, NULL, procthread2, NULL);
	int *num3 = malloc(sizeof(int));
	*num3 = 3;
	rc = pthread_create(&tid3, NULL, procthread13, num3);
	for (k = 0; k < 20; k++)
	{
		printf("\033[%d;1H\033[37m%c: \n", k + 1, letters[k]);
		if (k == 5)
		{
			pthread_cancel(tid1);
			printf("\033[26;1H\033[34mПопытка отмены первой нити");
		}
		if (k == 10)
		{
			pthread_cancel(tid3);
			printf("\033[26;1H\033[31mПопытка отмены второй нити");
		}
		usleep(1500000);
	}
	printf("\033[25;1H\033[0mПрограмма завершена, для продолжения нажмите любую клавишу...\n");
	getchar();
	printf("\033[0m");
	system("clear");
	return 0;
}
