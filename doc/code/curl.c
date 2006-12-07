/*
 * curl.c - test the usage of libcurl.
 *
 * compile:
 *	gcc -o curl -lcurl curl.c
 */

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

#define MAX_RATE	102400 // 100K
FILE *fp = NULL;

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
	if (!fp) {
		fp = fopen("/dev/null", "w");
		if (!fp) {
			fprintf(stderr, "Fail to open file!\n");
			return -1;
		}
	}
	int written = fwrite(ptr, size, nmemb, (FILE *)fp);

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

	curl = curl_easy_init();
	if (curl == NULL) {
		printf("Error init libcurl!\n");
		return -1;
	}

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

