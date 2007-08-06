/*
 * md5.c - MD5 encrypt and decrypt examples, using OpenSSL.
 * by Jick Nan @ Aug-24, 2006
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

char *md5(char *in)
{
    MD5_CTX x;
    int i;
    char *out = NULL;
    unsigned char d[16];

    MD5_Init(&x);
    MD5_Update (&x, in, strlen(in));
    MD5_Final(d, &x);

    out = malloc(35);
    memset(out, 0x00, 35);
    strcpy(out, "$1$");
    for (i = 0; i < 16; i++) {
	sprintf (out + (i*2), "%02x", d[i]);
    }

    return out;
}

int main(int argc, char *argv[])
{
    char password[68] = {0};
    int i = 0, len;
    char *text = "abc";

    printf("TEXT: %s\nMD5ed: %s\n", text, md5(text));

#if 0
    if (argc != 2) {
	printf("Usage: %s <message>(16~64)\n", argv[0]);
	return -1;
    }

    strcpy(password, argv[1]);
    len = strlen(password);
    if ( len < 16 || len > 64) {
	printf("message length: 16 <= len <= 64\n");
	return -1;
    }

    // padding
    if (len < 64) {
	for (i = 64/len; i >= 0; i--) {
	    strcat(tmp, password);
	}
	strncpy(password, tmp, 64);
    }
#endif


    return 0;
}
