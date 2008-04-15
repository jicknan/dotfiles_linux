/*
 * Filename:	libget.h
 * $Id: h.skel,v 1.1.1.1 2006/04/25 10:57:15 jick Exp $
 * Created at:	Tue 24 Jul 2007 09:42:54 AM CST
 */
#ifndef LIBGET_H
#define LIBGET_H

#include <curl/curl.h>
#include <libxml/parser.h>

extern struct yupoo_info *yupoo;

int urlget_file(const char *url, FILE *fp, long resume_from);

char *libxmlutil_dup_attr(const xmlNode *node, const char *name);
const char *libxmlutil_attr_as_string(const xmlNode *node, const char *name);
long libxmlutil_attr_as_long(const xmlNode *node, const char *name);
void libxmlutil_iterate_by_tag_name(const xmlNode *node, const char *name,
	void(*f)(int i, const xmlNode *node, struct yupoo_info *yupoo), struct yupoo_info *yupoo);
const xmlNode *libxmlutil_child_node_by_name(const xmlNode *node, const char *ns,
		const char *name);
char *libxmlutil_dup_value(const xmlNode *node);
int libxmlutil_count_by_tag_name(const xmlNode *node, const char *name);

int libget_write_by_tmpfile(char **used_filename,
		int(*writer)(FILE *f, char *user_data), char *user_data);

char *libget_md5(char *in);
#endif /* LIBGET_H */
/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

