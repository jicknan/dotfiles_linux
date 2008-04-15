/*
 * libget.c
 *
 * Created at:  Tue 24 Jul 2007 09:41:19 AM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <openssl/md5.h>
#include "libget.h"

//#define DEBUG
/*
 * get file section
 */
int urlget_file(const char *url, FILE *fp, long resume_from)
{
	CURL *c;
	CURLcode success;
	char errbuf[CURL_ERROR_SIZE];
	int ret = 0;

	c = curl_easy_init();

	if (c) {
		curl_easy_setopt(c, CURLOPT_URL, url);
		curl_easy_setopt(c, CURLOPT_ERRORBUFFER, errbuf);
		curl_easy_setopt(c, CURLOPT_WRITEDATA, fp);
		curl_easy_setopt(c, CURLOPT_FOLLOWLOCATION, 1);
		if (resume_from)
			curl_easy_setopt(c, CURLOPT_RESUME_FROM_LARGE,
					(curl_off_t)resume_from);
#ifdef DEBUG
		curl_easy_setopt(c, CURLOPT_VERBOSE, 1);
#endif

		success = curl_easy_perform(c);
		curl_easy_cleanup(c);

		if (success) {
			fprintf(stderr, "Error retrieving %s: %s\n", url, errbuf);
			ret = 1;
		}
	} else
		ret = 1;

	return ret;
}

/*
 * XML utility section
 */

char *libxmlutil_dup_attr(const xmlNode *node, const char *name)
{
	xmlChar *s;

	s = xmlGetProp((xmlNode *)node, (const xmlChar *)name);

	if (s)
		return strdup((char *)s);
	else
		return NULL;
}

const char *libxmlutil_attr_as_string(const xmlNode *node, const char *name)
{
	return (const char *)xmlGetProp((xmlNode *)node, (const xmlChar *)name);
}

long libxmlutil_attr_as_long(const xmlNode *node, const char *name)
{
	xmlChar *s;

	s = xmlGetProp((xmlNode *)node, (const xmlChar *)name);

	if (s)
		return strtol((char *)s, (char **)NULL, 10);
	else
		return -1;
}

void libxmlutil_iterate_by_tag_name(const xmlNode *node, const char *name,
		void(*f)(int i, const xmlNode *node, struct yupoo_info *yupoo), struct yupoo_info *yupoo)
{
	int i = 0;

	for (node = node->children; node; node = node->next)
		if (node->type == XML_ELEMENT_NODE && !strcmp((char *)node->name, name)) {
			f(i, node, yupoo);
			i++;
		}
}

const xmlNode *libxmlutil_child_node_by_name(const xmlNode *node, const char *ns,
		const char *name)
{
	for (node = node->children; node; node = node->next)
		if (node->type == XML_ELEMENT_NODE && !strcmp((char *)node->name, name)
				&& (!ns || !strcmp((char *)node->ns->href, ns))){
			return node;
		}
	return NULL;
}

char *libxmlutil_dup_value(const xmlNode *node)
{
	xmlChar *s;

	s = xmlNodeListGetString(node->doc, node->xmlChildrenNode, 1);

	if (s)
		return strdup((char *)s);
	else
		return NULL;
}

#if 0
static char *_dup_child_node_value(const xmlNode *node, const char *tag)
{
	const xmlNode *n;

	n = libxmlutil_child_node_by_name(node, NULL, tag);

	if (n)
		return libxmlutil_dup_value(n);
	else
		return NULL;
}
#endif

int libxmlutil_count_by_tag_name(const xmlNode *node, const char *name)
{
	int n = 0;

	for (node = node->children; node; node = node->next)
		if (node->type == XML_ELEMENT_NODE && !strcmp((char *)node->name, name))
			n++;
	return n;
}

/*
 * Other utility section
 */

int libget_write_by_tmpfile(char **used_filename,
		int(*writer)(FILE *f, char *user_data), char *user_data)
{
	int ret;
	FILE *f;
	int fd;
	char tmpfile[32] = "/tmp/get_yupoo.XXXXXX";

	fd = mkstemp(tmpfile);
	if (fd < 0) {
		perror("Error opening temporary file");
		return -1;
	}

	f = fdopen(fd, "w");
	if (!f) {
		perror("Error opening temporary file stream");
		close(fd);
		return -1;
	}

	ret = writer(f, user_data);

	fclose(f);
	close(fd);

	*used_filename = strdup(tmpfile);

	return ret;
}

char *libget_md5(char *in)
{
	int i;
	MD5_CTX x;
	char *out = NULL;
	unsigned char d[16];

	MD5_Init(&x);
	MD5_Update (&x, in, strlen(in));
	MD5_Final(d, &x);

	out = malloc(35);
	memset(out, 0x00, 35);
	strcpy(out, "$1$");
	for (i = 0; i < 16; i++) {
		sprintf(out + (i*2), "%02x", d[i]);
	}

	return out;
}


/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

