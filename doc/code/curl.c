/*
 * curl.c - test the usage of libcurl.
 *
 * compile:
 * 	gcc -o curl -lcurl curl.c
 *
 * Created at:  Wed 06 Dec 2006 08:03:38 PM UTC
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */

#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

int main(int argc, char *argv[])
{
	CURL *curl;
	CURLcode res;
	FILE *fp = NULL;

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

	fp = fopen("/dev/null", "w");
	curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
	//curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(curl, CURLOPT_BUFFERSIZE, 10240);
	//curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 10240);
	//curl_easy_setopt(curl, CURLOPT_MAX_RECV_PER_SECOND, 10240);
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

