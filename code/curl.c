/*
 * curl.c - test the usage of libcurl.
 *
 * compile:
 *	gcc -o curl -lcurl curl.c
 */

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <curl/curl.h>

#define MAX_RATE	204800 // 100K
#define CURL_MAX_WRITE_SIZE 16384

FILE *fp = NULL;
struct timeval lastrecvtime;
static long recvpersecond = MAX_RATE;

/* Return the current time in a timeval struct */
struct timeval tvnow(void)
{
  struct timeval now;
  (void)gettimeofday(&now, NULL);
  return now;
}

/*
 * Make sure that the first argument is the more recent time, as otherwise
 * we'll get a weird negative time-diff back...
 *
 * Returns: the time difference in number of milliseconds.
 */
long tvdiff(struct timeval newer, struct timeval older)
{
  return (newer.tv_sec-older.tv_sec)*1000+
    (newer.tv_usec-older.tv_usec)/1000;
}

static void go_sleep(long ms)
{
	struct timeval timeout;

	timeout.tv_sec = ms/1000;
	ms = ms%1000;
	timeout.tv_usec = ms * 1000;

	select(0, NULL, NULL, NULL, &timeout);
}

size_t write_data(void *ptr, size_t sz, size_t nmemb, void *stream)
{

	off_t size = (off_t)(sz * nmemb);

	if(recvpersecond) {
		struct timeval now;
		long timediff;
		long sleep_time;

		static off_t addit = 0;

		now = tvnow();
		timediff = tvdiff(now, lastrecvtime); /* ms */

		if((recvpersecond > CURL_MAX_WRITE_SIZE) && (timediff < 100) ) {
			addit += size;
		}
		else {
			size += addit;
			addit = 0;

			if (size*1000 > recvpersecond*timediff) {
				sleep_time = (long)(size*1000/recvpersecond - timediff);
				fprintf(stderr, "sleep_time=%ld\n", sleep_time);

				if (sleep_time > 0) {
					go_sleep(sleep_time);
					now = tvnow();
				}
			}
			lastrecvtime = now;
		}
	}

	if (!fp) {
		fp = fopen("/dev/null", "w");
		if (!fp) {
			fprintf(stderr, "Fail to open file!\n");
			return -1;
		}
	}
	//fprintf(stderr, "#");
	int written = fwrite(ptr, sz, nmemb, (FILE *)fp);

	return written;
}

int main(int argc, char *argv[])
{
	CURL *curl;
	CURLcode res;

	if (argc != 2) {
		printf("USAGE: %s <url>\n", argv[0]);
		return -1;
	}

	printf("%s\n", curl_version());
	curl = curl_easy_init();
	if (curl == NULL) {
		printf("Error init libcurl!\n");
		return -1;
	}

	lastrecvtime = tvnow();
	curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, MAX_RATE);
	curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, MAX_RATE);
	curl_easy_setopt(curl, CURLOPT_MAX_SEND_SPEED_LARGE, MAX_RATE);
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

