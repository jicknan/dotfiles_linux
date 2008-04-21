#include <stdio.h>
#include <sys/inotify.h>
#include <errno.h>
char * monitored_files[] = {
	"/tmp",
	"/tmp/ddd",
	"/mnt/d"
};
struct wd_name {
	int wd;
	char * name;
};
#define WD_NUM 3
struct wd_name wd_array[WD_NUM];
char * event_array[] = {
	"File was accessed",
	"File was modified",
	"File attributes were changed",
	"writtable file closed",
	"Unwrittable file closed",
	"File was opened",
	"File was moved from X",
	"File was moved to Y",
	"Subfile was created",
	"Subfile was deleted",
	"Self was deleted",
	"Self was moved",
	"",
	"Backing fs was unmounted",
	"Event queued overflowed",
	"File was ignored"
};
#define EVENT_NUM 16
#define MAX_BUF_SIZE 1024
	
int main(void)
{
	int fd;
	int wd;
	char buffer[1024];
	char * offset = NULL;
	struct inotify_event * event;
	int len, tmp_len;
	char strbuf[16];
	int i = 0;
	
	fd = inotify_init();
	if (fd < 0) {
		printf("Fail to initialize inotify.\n");
		exit(-1);
	}
	for (i=0; i<WD_NUM; i++) {
		wd_array[i].name = monitored_files[i];
		wd = inotify_add_watch(fd, wd_array[i].name, IN_ALL_EVENTS);
		if (wd < 0) {
			printf("Can't add watch for %s.\n", wd_array[i].name);
			exit(-1);
		}
		wd_array[i].wd = wd;
	}
	while(len = read(fd, buffer, MAX_BUF_SIZE)) {
		offset = buffer;
		printf("Some event happens, len = %d.\n", len);
		event = (struct inotify_event *)buffer;
		while (((char *)event - buffer) < len) {
			printf("Object type: %s\n", (event->mask & IN_ISDIR)?"Direcotory":"File");
			for (i=0; i<WD_NUM; i++) {
				if (event->wd != wd_array[i].wd) continue;
				printf("Object name: %s\n", wd_array[i].name);
				break;
			}
			printf("Event mask: %08X\n", event->mask);
			for (i=0; i<EVENT_NUM; i++) {
				if (event_array[i][0] == '\0') continue;
				if (event->mask & (1<<i)) {
					printf("Event: %s\n", event_array[i]);
				}
			}
			tmp_len = sizeof(struct inotify_event) + event->len;
			event = (struct inotify_event *)(offset + tmp_len); 
			offset += tmp_len;
		}
	}
}
