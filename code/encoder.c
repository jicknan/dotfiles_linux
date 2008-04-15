/*
 * encoder.c - package protected code generator.
 *
 * Created at:  Mon 24 Sep 2007 03:00:22 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 *
 * Compile:
 *	gcc -Wall encoder.c -o encoder -lcrypto
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <openssl/aes.h>
#include <openssl/md5.h>

#define MSG "SErCOmMsDCcPunAs" // 16-byte

#define DEBUG
#define jprintf printf

#define BUFSIZE 1024*16
int generate_md5sum(char *file, unsigned char *md)
{
	int ret=0, i;
	int fd;
	MD5_CTX c;
	static unsigned char buf[BUFSIZE];

	jprintf(">>%s:%d:generating md5sum...\n", __FILE__, __LINE__);
	fd = open(file, O_RDONLY);
	if ( fd == -1) {
		perror(file);
		return -1;
	}

	MD5_Init(&c);
	for (;;) {
		i = read(fd, buf, BUFSIZE);
		if (i <= 0) break;
		MD5_Update(&c,buf,(unsigned long)i);
	}
	ret = MD5_Final(&(md[0]), &c);

	printf("MD5(%s)\t=\t", file);
	for (i=0; i<16; i++)
		printf("%02X", md[i]);
	printf("\n");

	return ret;
}

int aes_encrypt(const unsigned char *msg, const unsigned char *key, unsigned char *md)
{
	int ret;
	AES_KEY aes_key;

	// AES encrypting
	ret = AES_set_encrypt_key((const unsigned char *)key, 128, &aes_key);
	if (ret < 0 ) {
		jprintf("L%d: AES_set_encrypt_key error!\n", __LINE__);
		return -1;
	}
	AES_encrypt((const unsigned char *)msg, (unsigned char *)md, &aes_key);


	return 0;
}

int aes_decrypt(const unsigned char *md, const unsigned char *key, unsigned char *msg)
{
	int ret;
	AES_KEY aes_key;

	// AES decrypting
	ret = AES_set_decrypt_key((const unsigned char *)key, 128, &aes_key);
	if (ret < 0 ) {
		jprintf("L%d: AES_set_decrypt_key error!\n", __LINE__);
		return -1;
	}
	AES_decrypt((const unsigned char *)md, (unsigned char *)msg, &aes_key);

	return 0;
}

int generate_key(unsigned char *md)
{
	int i, ret;
	char key[16] = MSG;

	jprintf(">>%s:%d:generating key...\n", __FILE__, __LINE__);

	jprintf("key[16]\t=\t%s(STR)\n", key);
	jprintf("key[16]\t=\t");
	for (i = 0; i < 16; i++){
		jprintf("%02X", key[i]);
	}
	jprintf("(HEX)\n");

	ret = aes_encrypt((const unsigned char *)key, (const unsigned char *)key, md);
	jprintf("MD[16]\t=\t");
	for (i = 0; i < 16; i++) {
		jprintf("%02X", md[i]);
	}
	jprintf("(HEX)\n");

	return 0;
}

int main(int argc, char **argv)
{
	int ret,i;
	unsigned char key[16];
	unsigned char md5sum[16];
	unsigned char md[16];
	unsigned char tmp[16];

	if (argc != 2) {
		printf("Usage: %s <package_file>\n", argv[0]);
		return -1;
	}

	ret = generate_md5sum(argv[1], md5sum);
	ret = generate_key(key);

	jprintf(">>%s:%d:checking md5sum and key...\n", __FILE__, __LINE__);
	jprintf("MD5sum\t=\t");
	for (i = 0; i < 16; i++) {
		jprintf("%02X", md5sum[i]);
	}
	jprintf("(HEX)\n");
	jprintf("Key\t=\t");
	for (i = 0; i < 16; i++) {
		jprintf("%02X", key[i]);
	}
	jprintf("(HEX)\n");

	ret = aes_encrypt((const unsigned char *)md5sum, (const unsigned char *)key, md);
	jprintf("MD\t=\t");
	for (i = 0; i < 16; i++) {
		jprintf("%02X", md[i]);
	}
	jprintf("(HEX)\n");

	ret = aes_decrypt((const unsigned char *)md, (const unsigned char *)key, tmp);
	jprintf("DM\t=\t");
	for (i = 0; i < 16; i++) {
		jprintf("%02X", tmp[i]);
	}
	jprintf("(HEX)\n");

	return 0;
}


/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

