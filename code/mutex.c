/*
 * mutex.c - Using mutexes
 *
 * Created at:  Thu 12 Jun 2008 10:36:44 AM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define	INDEX	10000000

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
long int ticks;
time_t end_time;

/* An "index" thread to increment a counter */
void idx_th(void *arg);

/* A "monitor" thread to check the counter's value */
void mon_th(void *arg);

int main(int argc, char *argv[])
{
	pthread_t idx_th_id;
	pthread_t mon_th_id;
	int ret;

	end_time = time(NULL) + 30; // 30s runtime

	/* Create two threads */
	ret = pthread_create(&idx_th_id, NULL, (void *)idx_th, NULL);
	if (ret != 0) {
		perror("pthread_create: idx_th");
		return -1;
	}

	ret = pthread_create(&mon_th_id, NULL, (void *)mon_th, NULL);
	if (ret != 0) {
		perror("pthread_create: mon_th");
		return -1;
	}

	pthread_join(idx_th_id, NULL);
	pthread_join(mon_th_id, NULL);

	return 0;
}

void idx_th(void *arg)
{
	long l;

	while (time(NULL) < end_time) {
		/* Lock the mutex */
		if (pthread_mutex_lock(&mutex) != 0) {
			perror("pthread_mutex_lock");
			exit(-1);
		}

		/* Increment the counter */
		for (l = 1; l < INDEX; ++l)
			++ticks;

		/* Now we're done, so unlock the mutex */
		if (pthread_mutex_unlock (&mutex) != 0) {
			perror("pthread_mutex_unlock");
			exit(-1);
		}
		sleep(1);
	}
}

void mon_th(void *arg)
{
	int nolock = 0;
	int ret;

	while(time(NULL) < end_time) {
		/* Wake up every two seconds */
		sleep(3);
		/* Try to lock the mutex */
		ret = pthread_mutex_trylock(&mutex);
		if (ret != EBUSY) {
			if (ret != 0) {
				perror("pthread_mutex_trylock");
				exit(-1);
			}
			printf("mon_th: got lock at %ld ticks\n", ticks);
			if (pthread_mutex_unlock(&mutex) != 0) {
				perror("pthread_mutex_unlock");
				exit(-1);
			}
		} else {
			/* Number of times mutex was locked */
			nolock++;
		}
	}
	printf("mon_th missed lock %d times\n", nolock);
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

