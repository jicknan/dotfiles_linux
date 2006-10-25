/*
 * aes.c - AES encrypt and decrypt examples, using OpenSSL.
 * by Jick Nan @ Aug-24, 2006
 *
 * Process:
 *	1) Get INTERFACE's MAC Address (last 3 bytes);
 *	2) Padding it to 16 bytes(key16);
 *	3) Generate key used to encrypt, using key16 by AES-way;
 *	4) AES encrypt, using key16 as message(out);
 *	5) Generate key used to decrypt, using key16;
 *	4) AES decypt, using out as message(key16).
 *
 * Compile:
 *	gcc -Wall aes.c -o aes -lcrypto
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <openssl/aes.h>

#define	INTERFACE	"eth0"
#define PAD_SIZE	32

int main(void)
{
	int skfd;
	int i, ret, j;
	struct ifreq ifr;
	unsigned char pmac[34] = { 0 };	// MAC Address (last 3 bytes)
	unsigned char tmp[128] = { 0 };
	unsigned char key16[16] = { 0 };// Message to encrypt.
				// *CAREFUL* this also used as AES key!
	unsigned char out[16] = { 0 }; // Message after encrypted.
	unsigned char sout[34] = { 0 }; // String style, rather than HEX
	AES_KEY key;	// key in AES way

	// get MAC address (last three bytes)
	skfd = socket(AF_INET, SOCK_STREAM, 0);
	if (skfd == -1) {
		printf("L%d: Open socket error!\n", __LINE__);
		return -1;
	}

	strcpy(ifr.ifr_name, INTERFACE);
	ret = ioctl(skfd, SIOCGIFHWADDR, &ifr);
	if (ret < 0) {
		printf("L%d: ioctl error!\n", __LINE__);
		return -1;
	}
	sprintf(pmac, "%02X%02X%02X", (ifr.ifr_hwaddr.sa_data[3] & 0377),
			(ifr.ifr_hwaddr.sa_data[4] & 0377),
			(ifr.ifr_hwaddr.sa_data[5] & 0377));

	printf("pmac(%d)\t\t=\t%s(STR)\n", strlen(pmac), pmac);

	// padding to PAD_SIZE bytes
	printf("\n>>Padding...\n");
	for (i = PAD_SIZE/6; i >= 0; i--) {
		strcat(tmp, pmac);
	}
	strncpy(pmac, tmp, PAD_SIZE);
	printf(" tmp(%d)\t=\t%s(STR)\npmac(%d)\t=\t%s(STR)\n",
			strlen(tmp), tmp, strlen(pmac), pmac);
	// convert string to hex.
	for (i = 0, j = 0; i < 32; i+=2, j++) {
		tmp[0]='\0';
		strncat(tmp, (const char *)(pmac+i), 2);
		key16[j] = strtol(tmp, NULL, 16);
	}
	printf("key16[16]\t=\t");
	for (i = 0; i < 16; i++){
		printf("%02X", key16[i]);
	}
	printf("(HEX)\n");

	// AES encryption
	printf("\n>>AES encryption...\n");
	ret = AES_set_encrypt_key((const unsigned char *)key16, 128, &key);
	if (ret < 0 ) {
		printf("L%d: AES_set_encrypt_key error!\n", __LINE__);
		return -1;
	}
	AES_encrypt((const unsigned char *)key16, (unsigned char *)out, &key);
	printf("  out[16]\t=\t");
	for (i = 0; i < 16; i++) {
		printf("%02X", out[i]);
	}
	printf("(HEX)\n");
	// convert Hex. to string
	for (i = 0; i < 16; i++) {
		tmp[0] = '\0';
		sprintf(tmp, "%02X", out[i]);
		strcat(sout, tmp);
	}
	printf("sout(%d)\t=\t%s(STR)\n", strlen(sout), sout);

	// AES decryption
	printf("\n>>AES decryption...\n");
	ret = AES_set_decrypt_key((const char *)key16, 128, &key);
	if (ret < 0 ) {
		printf("L%d: AES_set_decrypt_key error!\n", __LINE__);
		return -1;
	}
	key16[0] = '\0'; // Init it as we used it for decryption.
	AES_decrypt((const unsigned char *)out, (unsigned char *)key16, &key);
	printf("key16[16]\t=\t");
	for (i = 0; i < 16; i++){
		printf("%02X", key16[i]);
	}
	printf("(HEX)\n");

	return 0;
}

/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

