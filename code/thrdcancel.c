/*
 * thrdcancel.c - Illustrate thread cancellation
 *
 * Created at:  Thu 12 Jun 2008 10:16:21 AM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void task1(int *counter);
void task2(int *counter);
void cleanup(int counter1, int counter2);

int g1 = 0;
int g2 = 0;

int main(int argc, char *argv[])
{
	pthread_t thrd1, thrd2;
	int ret;

	/* Create the first thread */
	ret = pthread_create(&thrd1, NULL, (void *)task1, (void *)&g1);
	if (ret) {
		perror("pthread_create: task1");
		return -1;
	}

	/* Create the 2nd thread */
	ret = pthread_create(&thrd2, NULL, (void *)task2, (void *)&g2);
	if (ret) {
		perror("pthread_create: task2");
		return -1;
	}

	pthread_join(thrd2, NULL);
	pthread_cancel(thrd1); // Cancel the 1st thread
	pthread_join(thrd1, NULL);

	cleanup(g1, g2);

	return 0;
}

void task1(int *counter)
{
	/* Disable thread cancelation */
	//pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	while (*counter < 5) {
		printf("task1 count: %d\n", *counter);
		(*counter)++;
		sleep(1);
	}

	/* Enable thread cancellation */
	//pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
}

void task2(int *counter)
{
	while (*counter < 5) {
		printf("task2 count: %d\n", *counter);
		(*counter)++;
	}
}

void cleanup(int c1, int c2)
{
	printf("total iterations: %d\n", c1 + c2);
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

