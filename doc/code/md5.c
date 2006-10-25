/*
 * md5.c - MD5 encrypt and decrypt examples, using OpenSSL.
 * by Jick Nan @ Aug-24, 2006
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

int main(int argc, char *argv[])
{
    char password[68] = {0};
    MD5_CTX x;
    int i = 0, len;
    char *out = NULL;
    unsigned char d[16];
    unsigned char tmp[128] = { 0 };

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

    if (len < 64) {
	for (i = 64/len; i >= 0; i--) {
	    strcat(tmp, password);
	}
	strncpy(password, tmp, 64);
    }

    MD5_Init(&x);
    MD5_Update (&x, (char *) password, strlen(password));
    MD5_Final(d, &x);
    out = malloc(35);
    memset(out, 0x00, 35);
    strcpy(out, "$1$");
    printf ("MD5(\"%s\") = ", password);
    for (i = 0; i < 16; i++) {
	sprintf (out + (i*2), "%02X", d[i]);
    }
    printf ("%s(%d)\n", out, strlen(out));

    printf ("MD5(\"%s\") = ", password);
    for (i = 0; i < 16; i++) {
	printf ("%02X", d[i]);
    }
    printf ("(%d)\n", strlen(d));

    return 0;
}
