/*
 * play_yupoo.c
 *
 * Created at:  Mon 16 Jul 2007 10:11:48 PM CST
 *
 * $Id: c.skel,v 1.3 2006/06/01 10:02:05 jick Exp $
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "libget.h"

#define DEBUG
#define REST_URI	"http://www.yupoo.com/api/rest/"
#define AUTH_URI	"http://www.yupoo.com/services/auth/"
#define	API_KEY		"4217c1ab35eda9cc9a900191b6b4d189"
#define SHARED_SECRET	"y8lwthomokfdtgat"
#define	FORMAT		"rest"
#define DOWN_DIR	"/home/jick/all_yupoo"

struct yupoo_info {
	char *frob;
	char *auth_token;
	const char *userid;
	const char *username;
	const char *nickname;
	char *perms;
};

struct photo_info {
	char *id;
	char *dir;
	char *filename;
	long host;
	const char *secret;
	const char *originalformat;
	char *owner; // userid
	char *title;
};

int yupoo_photos_getInfo(struct photo_info *photo, struct yupoo_info *yupoo);

static void _photo_iterator(int i, const xmlNode *node, struct yupoo_info *yupoo)
{
	struct photo_info *photo;
	int ret;
	char url[256];
	char file[128];
	FILE *fp;
	int resume = 0;
	long resume_from = 0;

	photo = malloc(sizeof(struct photo_info));
	photo->id = libxmlutil_dup_attr(node, "id");
	photo->dir = libxmlutil_dup_attr(node, "dir");
	photo->filename = libxmlutil_dup_attr(node, "filename");
	photo->host = libxmlutil_attr_as_long(node, "host");
	photo->owner =	libxmlutil_dup_attr(node, "owner");
	photo->title = libxmlutil_dup_attr(node, "title");

	ret = yupoo_photos_getInfo(photo, yupoo);
	if (ret < 0)
		return;
	//sprintf(url, "http://photo%ld.yupoo.com/%s/%s_%s.%s",
	sprintf(url, "http://photo%ld.yupoo.com/%s/%s/%s/",
			photo->host, photo->dir, photo->filename,
			photo->secret);
			//photo->secret, photo->originalformat);
	sprintf(file, "%s/%s.%s",
			DOWN_DIR, photo->filename, photo->originalformat);
#ifdef DEBUG
	printf("photo <%d>: owner: %s\ttitle: %s\n\turl: %s\nfile: %s\n",
			i, photo->owner, photo->title, url, file);
#endif
	if (resume) {
		/* We're told to continue from where we are now. Get the
		 * size of the file as it is now and open it for append instead.
		 * Stolen from curl.
		 */
		struct stat fileinfo;

		if (0 == stat(file, &fileinfo))
			/* set offset to current file size: */
			resume_from = fileinfo.st_size;
		else
			/* let offset be 0: */
			resume_from = 0;
	}
	printf("Photo <%d>: %s\n\t=> %s (resume from: %ld)\n", i+1, url, file, resume_from);

	fp = fopen(file, resume_from?"ab":"wb");
	if (fp == NULL) {
		printf("Failed to open file <%s>.\n", file);
		return;
	}
	ret = urlget_file(url, fp, resume_from);
	if (ret != 0) {
		printf("Download failed.\n");
		return;
	}
}

xmlNode *rsp_open_file(const char *file)
{
	xmlDocPtr doc;
	xmlNode *root = NULL;
	const char *s;

	doc = xmlReadFile(file, NULL, 0);
	if(!doc) {
		printf("Error parsing channel file %s.\n", file);
		return NULL;
	}
#ifdef DEBUG_
	printf("doc: %p\n\tname: %s\n\tcompression: %d\n\tversion: %s\n\tencoding: %s\n\tURL: %s\n",
			doc, doc->name, doc->compression, doc->version, doc->encoding, doc->URL);
#endif

	root = xmlDocGetRootElement(doc);
	if (!root) {
		xmlFreeDoc(doc);
		printf("Error parsing channel file %s(step2).\n", file);
		return NULL;
	}
#ifdef DEBUG_
	printf("RootElement: %p\n\ttype: %d\n\tname: %s\n\tcontent: %s\n\tline: %d\n\textra: %d\n",
			root, root->type, root->name, root->content, root->line, root->extra);
#endif

	s = libxmlutil_attr_as_string(root, "stat");
	if(!s) {

		xmlFreeDoc(doc);
		printf("Error parsing channel file %s(step3).\n", file);
		return NULL;
	}
#ifdef DEBUG_
	printf("stat: %s\n", s);
#endif
	if (!strcmp(s, "fail")) {
		const xmlNode *err;
		err = libxmlutil_child_node_by_name(root, NULL, "err");
		printf("OOPS! I get an error <code: %ld, msg: %s>.\n",
				libxmlutil_attr_as_long(err, "code"),
				libxmlutil_attr_as_string(err, "msg"));
		return NULL;
	}


	return root;
}

static int _rsp_open_url_cb(FILE *fp, char *url)
{
	return urlget_file(url, fp, 0);
}

xmlNode *rsp_open_url(char *url)
{
	char *rsp_filename;
	xmlNode *ret;

	if (libget_write_by_tmpfile(&rsp_filename, _rsp_open_url_cb, url)) {
		printf("Error:%s:%d\n", __FILE__, __LINE__);
		return NULL;
	}

#ifdef DEBUG
	printf("%d:url=%s,filename=%s\n", __LINE__, url, rsp_filename);
#endif
	ret = rsp_open_file(rsp_filename);

	unlink(rsp_filename);

	return ret;
}

int yupoo_auth_getFrob(struct yupoo_info *yupoo)
{
	char *method = "yupoo.auth.getFrob";
	char *sig_txt = NULL;
	char *api_sig = NULL;
	char url[256];
	xmlNode *root = NULL;
	const xmlNode *result = NULL;

	sig_txt = malloc(256);
	memset(sig_txt, 0x00, 256);
	sprintf(sig_txt, "%sapi_key%smethod%s", SHARED_SECRET, API_KEY, method);
	api_sig = libget_md5(sig_txt);

	sprintf(url, "%s?method=%s&api_key=%s&api_sig=%s",
			REST_URI, method, API_KEY, api_sig);

	root = rsp_open_url(url);
	if (root == NULL) {
		return -1;
	}
	result = libxmlutil_child_node_by_name(root, NULL, "frob");
	yupoo->frob = libxmlutil_dup_value(result);
	return 0;

}

int yupoo_photos_search(struct yupoo_info *yupoo)
{
	//char *method = "yupoo.favorites.getList";
	char *method = "yupoo.photos.search";
	char url[256];
	xmlNode *root = NULL;
	const xmlNode *result = NULL;
	const xmlNode *photos = NULL;
	int num_items;
	long page = 1, pages, total, perpage;
	char *sig_txt = NULL;

	sig_txt = malloc(256);
	memset(sig_txt, 0x00, 256);
	sprintf(sig_txt, "%sapi_key%sauth_token%smethod%spage%lduser_id%s",
			SHARED_SECRET, API_KEY, yupoo->auth_token, method, page, yupoo->userid);

	sprintf(url, "%s?method=%s&api_key=%s&auth_token=%s&user_id=%s&page=%ld&api_sig=%s",
			REST_URI, method, API_KEY, yupoo->auth_token,
			yupoo->userid, page, libget_md5(sig_txt));
	root = rsp_open_url(url);
	if (root == NULL) {
		return -1;
	}
	result = libxmlutil_child_node_by_name(root, NULL, "result");
	page = libxmlutil_attr_as_long(result, "page");
	pages = libxmlutil_attr_as_long(result, "pages");
	perpage = libxmlutil_attr_as_long(result, "perpage");
	total = libxmlutil_attr_as_long(result, "total");
#ifdef DEBUG
	printf("result: page=%ld, pages=%ld, perpage=%ld, total=%ld\n",
			page, pages, perpage, total);
#endif
	printf("%s, you have %ld photos totally. We get %ld photos on time, "
			"so we need to get %ld times.\n",
			yupoo->nickname, total, perpage, pages);
	photos = libxmlutil_child_node_by_name(result, NULL, "photos");
	num_items = libxmlutil_count_by_tag_name(photos, "photo");
	printf("Now round <%ld> start, we'll get %d photos this time.\n", page, num_items);
	libxmlutil_iterate_by_tag_name(photos, "photo", _photo_iterator, yupoo);

#if 1
	for (page = 2; page <= pages; page++) {
		sig_txt = malloc(256);
		memset(sig_txt, 0x00, 256);
		sprintf(sig_txt, "%sapi_key%sauth_token%smethod%spage%lduser_id%s",
				SHARED_SECRET, API_KEY, yupoo->auth_token, method, page, yupoo->userid);

		sprintf(url, "%s?method=%s&api_key=%s&auth_token=%s&user_id=%s&page=%ld&api_sig=%s",
				REST_URI, method, API_KEY, yupoo->auth_token,
				yupoo->userid, page, libget_md5(sig_txt));
		root = rsp_open_url(url);
		if (root == NULL) {
			return -1;
		}
		result = libxmlutil_child_node_by_name(root, NULL, "result");
		photos = libxmlutil_child_node_by_name(result, NULL, "photos");
		num_items = libxmlutil_count_by_tag_name(photos, "photo");
		printf("Now round <%ld> start, we'll get %d photos this time.\n", page, num_items);
		libxmlutil_iterate_by_tag_name(photos, "photo", _photo_iterator, yupoo);
	}
#endif

	return 0;
}

int yupoo_auth_getToken(struct yupoo_info *yupoo)
{
	char *method = "yupoo.auth.getToken";
	char *sig_txt = NULL;
	char *api_sig = NULL;
	char url[256];
	xmlNode *root = NULL;
	const xmlNode *result = NULL;
	const xmlNode *token = NULL, *perms = NULL, *user = NULL;

	sig_txt = malloc(256);
	memset(sig_txt, 0x00, 256);
	sprintf(sig_txt, "%sapi_key%sfrob%smethod%s",
			SHARED_SECRET, API_KEY, yupoo->frob, method);
	api_sig = libget_md5(sig_txt);

	sprintf(url, "%s?method=%s&api_key=%s&frob=%s&api_sig=%s",
			REST_URI, method, API_KEY, yupoo->frob, api_sig);
	root = rsp_open_url(url);
	if (root == NULL) {
		return -1;
	}
	result = libxmlutil_child_node_by_name(root, NULL, "auth");
	token = libxmlutil_child_node_by_name(result, NULL, "token");
	yupoo->auth_token = libxmlutil_dup_value(token);
	perms = libxmlutil_child_node_by_name(result, NULL, "perms");
	user = libxmlutil_child_node_by_name(result, NULL, "user");
	yupoo->userid = libxmlutil_attr_as_string(user, "id");
	yupoo->username = libxmlutil_dup_attr(user, "username");
	yupoo->nickname = libxmlutil_dup_attr(user, "nickname");
	yupoo->perms = libxmlutil_dup_value(perms);

#ifdef DEBUG
	printf("Token: %s\nperms: %s\nUser:\n\tid: %s\n\tusername: %s\n\tnickname: %s\n",
			yupoo->auth_token, yupoo->perms, yupoo->userid,
			yupoo->username, yupoo->nickname);
#endif
	printf("%s, I get token from you, and have the \"%s\" perms of your Yupoo account.\n"
			"Can I call you %s from now on? :-)\n",
		yupoo->username, yupoo->perms, yupoo->nickname);

	return 0;
}

int yupoo_auth(char *frob, char *perms)
{
	char *sig_txt = NULL;
	char *api_sig = NULL;
	char cmd[256];

	sig_txt = malloc(256);
	memset(sig_txt, 0x00, 256);
	sprintf(sig_txt, "%sapi_key%sfrob%sperms%s",
			SHARED_SECRET, API_KEY, frob, perms);
	api_sig = libget_md5(sig_txt);

	sprintf(cmd, "opera \"%s?api_key=%s&frob=%s&perms=%s&api_sig=%s\"",
			AUTH_URI, API_KEY, frob, perms, api_sig);
#ifdef DEBUG
	printf("CMD: %s\n", cmd);
#endif
	printf("Loading web browser to complete auth process. "
			"If you get an error here, just try again please.\n");
	system(cmd);

	return 0;
}

int main(void)
{
	int ret;
	struct yupoo_info *yupoo;

	printf("Hi, guy, I'll help you to get photos from your Yupoo account. Let's start.\n");
	yupoo = malloc(sizeof(struct yupoo_info));

	ret = yupoo_auth_getFrob(yupoo);
	if (ret < 0) {
		printf("getFrob failed.");
		return -1;
	}
	yupoo_auth(yupoo->frob, "read");
	//yupoo_auth(yupoo->frob, "delete");
	ret = yupoo_auth_getToken(yupoo);
	if (ret < 0) {
		printf("getToken failed.");
		return -1;
	}
#ifdef DEBUG
	printf("Frob: %s\ntoken: %s\nuserid: %s\n", yupoo->frob, yupoo->auth_token, yupoo->userid);
#endif
	yupoo_photos_search(yupoo);

	return 0;
}

int yupoo_photos_getInfo(struct photo_info *photo, struct yupoo_info *yupoo)
{
	char *method = "yupoo.photos.getInfo";
	char url[256];
	xmlNode *root = NULL;
	const xmlNode *result = NULL;
	char *sig_txt = NULL;

	sig_txt = malloc(256);
	memset(sig_txt, 0x00, 256);
	sprintf(sig_txt, "%sapi_key%sauth_token%smethod%sphoto_id%s",
			SHARED_SECRET, API_KEY, yupoo->auth_token, method, photo->id);

	sprintf(url, "%s?method=%s&api_key=%s&auth_token=%s&photo_id=%s&api_sig=%s",
			REST_URI, method, API_KEY, yupoo->auth_token, photo->id, libget_md5(sig_txt));
	root = rsp_open_url(url);
	if (root == NULL) {
		return -1;
	}
	result = libxmlutil_child_node_by_name(root, NULL, "photo");
	photo->secret = libxmlutil_attr_as_string(result, "secret");
	photo->originalformat = libxmlutil_attr_as_string(result, "originalformat");

	return 0;
}
/*
 * vim:foldmethod=marker:shiftwidth=8:tabstop=8:filetype=c:norl:
 */

