/*
 * xml.c
 *
 * Created at:  Thu 19 Jul 2007 04:05:53 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>

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
		void(*f)(int i, const xmlNode *node))
{
	int i = 0;

	for (node = node->children; node; node = node->next)
		if (node->type == XML_ELEMENT_NODE && !strcmp((char *)node->name, name)) {
			f(i, node);
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

static char *_dup_child_node_value(const xmlNode *node, const char *tag)
{
	const xmlNode *n;

	n = libxmlutil_child_node_by_name(node, NULL, tag);

	if (n)
		return libxmlutil_dup_value(n);
	else
		return NULL;
}

int libxmlutil_count_by_tag_name(const xmlNode *node, const char *name)
{
	int n = 0;

	for (node = node->children; node; node = node->next)
		if (node->type == XML_ELEMENT_NODE && !strcmp((char *)node->name, name))
			n++;
	return n;
}

static void _enclosure_iterator(int i, const xmlNode *node)
{
	const char *url;
	const char *downloadtime;

	url = libxmlutil_attr_as_string(node, "url");
	downloadtime = libxmlutil_attr_as_string(node, "downloadtime");
	printf("url: %s\ndownload time: %s\n", url, downloadtime);
}

static void _item_iterator(int i, const xmlNode *node)
{
	const xmlNode *enclosure;
	const xmlNode *mrss_content;
	const xmlNode *mrss_group;
	char *item_title;
	char *item_link;
	char *item_desc;
	char *en_url;
	long en_length;
	char *en_type;

	item_title = _dup_child_node_value(node, "title");
	item_link = _dup_child_node_value(node, "link");
	item_desc = _dup_child_node_value(node, "description");

	printf("item <%d>:\n\ttitle: %s\n\tlink: %s\n\tdesc: %s\n",
			i, item_title, item_link, item_desc);

	enclosure = libxmlutil_child_node_by_name(node, NULL, "enclosure");
	if (enclosure) {
		en_url = libxmlutil_dup_attr(enclosure, "url");
		en_length = libxmlutil_attr_as_long(enclosure, "length");
		en_type = libxmlutil_dup_attr(enclosure, "type");
	}
	printf("enclosure:\n\turl: %s\n\tlength: %d\n\ttype: %s\n",
			en_url, en_length, en_type);
}

static void _photo_iterator(int i, const xmlNode *node)
{
	printf("photo <%d>:\n\tid: %s\n\towner: %s\n\ttitle: %s\n\thost: %d\n\tdir: %s\n\tfilename: %s\n",
			i,
			libxmlutil_dup_attr(node, "id"),
			libxmlutil_dup_attr(node, "owner"),
			libxmlutil_dup_attr(node, "title"),
			libxmlutil_attr_as_long(node, "host"),
			libxmlutil_dup_attr(node, "dir"),
			libxmlutil_dup_attr(node, "filename"));
}

static xmlEntityPtr _get_entity(void *ctxt, const xmlChar *name)
{
	xmlEntityPtr entity;
	char *contents;

	entity = xmlGetPredefinedEntity(name);

	printf("%s:name=%s\n", name);

	return entity;
}

int rss_parse(const char *url, const xmlNode *root)
{
	const char *version_string;
	const xmlNode *channel;
	int num_items;
	char *ch_title;
	char *ch_link;
	char *ch_desc;
	char *ch_lang;

	if (strcmp((char *)root->name, "rss")) {
		printf("Error parsing RSS file %s: Unrecognized top-level element %s.\n",
				url, (char *)root);
		return -1;
	}

	version_string = libxmlutil_attr_as_string(root, "version");
	printf("RSS version: %s\n", version_string);

	channel = libxmlutil_child_node_by_name(root, NULL, "channel");
	printf("Channel: %08x\n\ttype: %d\n\tname: %s\n\tcontent: %s\n\tline: %d\n\textra: %s\n",
			channel, channel->type, channel->name, channel->content, channel->line, channel->extra);

	if (channel) {
		num_items = libxmlutil_count_by_tag_name(channel, "item");
		ch_title = _dup_child_node_value(channel, "title");
		ch_link = _dup_child_node_value(channel, "link");
		ch_desc = _dup_child_node_value(channel, "description");
		ch_lang = _dup_child_node_value(channel, "language");

		printf("\tnum_item: %d\n\ttitle: %s\n\tlink: %s\n\tdescription: %s\n\tlang: %s\n",
				num_items, ch_title, ch_link, ch_desc, ch_lang);
		libxmlutil_iterate_by_tag_name(channel, "item", _item_iterator);
	}

	return 0;
}

int rsp_open(const char *file)
{
	xmlDocPtr doc;
	xmlNode *root = NULL;
	const xmlNode *result = NULL;
	const xmlNode *photos = NULL;
	const char *s;
	int num_items;

	doc = xmlReadFile(file, NULL, 0);
	if(!doc) {
		printf("Error parsing channel file %s.\n", file);
		return -1;
	}
	printf("doc: %08x\n\tname: %s\n\tcompression: %d\n\tversion: %s\n\tencoding: %s\n\tURL: %s\n",
			doc, doc->name, doc->compression, doc->version, doc->encoding, doc->URL);

	root = xmlDocGetRootElement(doc);
	if (!root) {
		xmlFreeDoc(doc);
		printf("Error parsing channel file %s(step2).\n", file);
		return -1;
	}
	printf("RootElement: %08x\n\ttype: %d\n\tname: %s\n\tcontent: %s\n\tline: %d\n\textra: %s\n",
			root, root->type, root->name, root->content, root->line, root->extra);

	s = libxmlutil_attr_as_string(root, "stat");
	if(!s) {

		xmlFreeDoc(doc);
		printf("Error parsing channel file %s(step3).\n", file);
		return -1;
	}
	printf("stat: %s\n", s);

	result = libxmlutil_child_node_by_name(root, NULL, "result");
	printf("result: page=%d, pages=%d, prepage=%d, total=%d\n",
			libxmlutil_attr_as_long(result, "page"),
			libxmlutil_attr_as_long(result, "pages"),
			libxmlutil_attr_as_long(result, "prepage"),
			libxmlutil_attr_as_long(result, "total"));
	photos = libxmlutil_child_node_by_name(result, NULL, "photos");
	num_items = libxmlutil_count_by_tag_name(photos, "photo");
	printf("num photos: %d\n", num_items);
	libxmlutil_iterate_by_tag_name(photos, "photo", _photo_iterator);

	return 0;
}

int cast_open(const char *file)
{
	xmlDocPtr doc;
	xmlNode *root = NULL;
	const char *s;

	doc = xmlReadFile(file, NULL, 0);
	if(!doc) {
		printf("Error parsing channel file %s.\n", file);
		return -1;
	}
	printf("doc: %08x\nname: %s\ncompression: %d\nversion: %s\nencoding: %s\nURL: %s\n",
			doc, doc->name, doc->compression, doc->version, doc->encoding, doc->URL);

	root = xmlDocGetRootElement(doc);
	if (!root) {
		xmlFreeDoc(doc);
		printf("Error parsing channel file %s(step2).\n", file);
		return -1;
	}
	printf("RootElement: %08x\ntype: %d\nname: %s\ncontent: %s\nline: %d\nextra: %s\n",
			root, root->type, root->name, root->content, root->line, root->extra);

	s = libxmlutil_attr_as_string(root, "rsslastfetched");
	if(s) {
		printf("rsslastfetched:%s\n", s);
		libxmlutil_iterate_by_tag_name(root, "enclosure", _enclosure_iterator);

		xmlFreeDoc(doc);
	}

	return 0;
}

int rss_open(const char *file)
{
	xmlParserCtxtPtr ctxt;
	xmlDocPtr doc;
	xmlNode *root = NULL;

	ctxt = xmlNewParserCtxt();
	//ctxt->sax->getEntity = _get_entity;
	doc = xmlSAXParseFile(ctxt->sax, file, 0);
	printf("doc: %08x\n\ttype: %d\n\tname: %s\n\tcompression: %d\n\tversion: %s\n\tencoding: %s\n\tURL: %s\n",
			doc, doc->name, doc->compression, doc->version, doc->encoding, doc->URL);
	if (!doc) {
		printf("Error pasring RSS file %s.\n", file);
		xmlFreeParserCtxt(ctxt);
		return -1;
	}

	root = xmlDocGetRootElement(doc);
	printf("RootElement: %08x\n\ttype: %d\n\tname: %s\n\tcontent: %s\n\tline: %d\n\textra: %s\n",
			root, root->type, root->name, root->content, root->line, root->extra);
	if (!root) {
		xmlFreeDoc(doc);
		xmlFreeParserCtxt(ctxt);
		printf("Error parsing Rss file %s(step 2).\n", file);
		return -1;
	}

	rss_parse(file, root);

	xmlFreeDoc(doc);
	xmlFreeParserCtxt(ctxt);

	return 0;
}

int main(int argc, char **argv)
{
	//cast_open(argv[1]);
	//rss_open(argv[1]);
	rsp_open(argv[1]);

	return 0;
}


/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

