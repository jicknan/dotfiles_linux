/*
 * xmltest.c
 *
 * Created at:  Wed 30 Apr 2008 04:50:02 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <libxml/parser.h>

int main(int argc, char *argv[])
{
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(argv[1]);

	if (doc == NULL) {
		fprintf(stderr, "Document not parsed successfully. \n");
		return -1;
	}

	cur = xmlDocGetRootElement(doc);

	if (cur == NULL) {
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		return -1;
	}

	printf("root node:%s\n", cur->name);
	cur = cur->xmlChildrenNode;
	while (cur != NULL) {
		printf("node name:%s\n", cur->name);
		cur = cur->next;
	}

	return 0;
}


/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

