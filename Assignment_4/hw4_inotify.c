#include <assert.h>
#include <dirent.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/inotify.h>
#include <unistd.h>
#define BUFLEN 10 * (sizeof(struct inotify_event) + NAME_MAX + 1)
#define MAX_DIRSIZE 1010
#define MAX_LEN 256

char wname[1000][4096];
int cntDir = 0;
char dir[MAX_DIRSIZE][MAX_LEN];

void printInotifyEvent(struct inotify_event *event) {
  char buf[4096] = "";
  sprintf(buf, "[%s]", wname[event->wd]);
  strncat(buf, "{", 4096);
  if (event->mask & IN_ACCESS)
    strncat(buf, "ACCESS, ", 4096);
  if (event->mask & IN_ATTRIB)
    strncat(buf, "ATTRIB, ", 4096);
  if (event->mask & IN_CLOSE_WRITE)
    strncat(buf, "CLOSE_WRITE, ", 4096);
  if (event->mask & IN_CLOSE_NOWRITE)
    strncat(buf, "CLOSE_NOWRITE, ", 4096);
  if (event->mask & IN_CREATE)
    strncat(buf, "CREATE, ", 4096);
  if (event->mask & IN_DELETE)
    strncat(buf, "DELETE, ", 4096);
  if (event->mask & IN_DELETE_SELF)
    strncat(buf, "DELETE_SELF, ", 4096);
  if (event->mask & IN_MODIFY)
    strncat(buf, "MODIFY, ", 4096);
  if (event->mask & IN_MOVE_SELF)
    strncat(buf, "MOVE_SELF, ", 4096);
  if (event->mask & IN_MOVED_FROM)
    strncat(buf, "MOVED_FROM, ", 4096);
  if (event->mask & IN_MOVED_TO)
    strncat(buf, "MOVED_TO, ", 4096);
  if (event->mask & IN_OPEN)
    strncat(buf, "OPEN, ", 4096);
  if (event->mask & IN_IGNORED)
    strncat(buf, "IGNORED, ", 4096);
  if (event->mask & IN_ISDIR)
    strncat(buf, "ISDIR, ", 4096);
  if (event->mask & IN_Q_OVERFLOW)
    strncat(buf, "Q_OVERFLOW, ", 4096);
  buf[strlen(buf) - 2] = 0;
  strncat(buf, "}", 4096);
  sprintf(buf, "%s cookie=%d", buf, event->cookie);
  if (event->len > 0)
    sprintf(buf, "%s name = %s\n", buf, event->name);
  else
    sprintf(buf, "%s name = null\n", buf);
  printf("%s", buf);
}

// compare the filename character
int cmp(const void *a, const void *b) {
  const char *c_a = (const char *)a;
  const char *c_b = (const char *)b;
  return strcmp(c_a, c_b);
}

// recursively list all the directory
void listDir(char *pathName) {
  DIR *curDir = opendir(pathName);
  assert(curDir != NULL);
  char *newPathName = (char *)malloc(PATH_MAX);
  char tmpDir[MAX_DIRSIZE][MAX_LEN];
  struct dirent entry;
  struct dirent *result;
  int ret, cnt = 0;
  int type[1000];
  ret = readdir_r(curDir, &entry, &result);
  while (result != NULL) {
    if (strcmp(entry.d_name, ".") == 0 || strcmp(entry.d_name, "..") == 0) {
      ret = readdir_r(curDir, &entry, &result);
      assert(ret == 0);
      continue;
    }
    assert(ret == 0);
    if (entry.d_type == DT_DIR) {
      strcpy(tmpDir[cnt], entry.d_name);
      cnt++;
    }
    ret = readdir_r(curDir, &entry, &result);
    assert(ret == 0);
  }
  qsort(tmpDir, cnt, sizeof(tmpDir[0]), cmp);
  for (int i = 0; i < cnt; i++) {
    sprintf(dir[cntDir], "%s/%s", pathName, tmpDir[i]);
    cntDir++;
  }
  for (int i = 0; i < cnt; i++) {
    sprintf(newPathName, "%s/%s", pathName, tmpDir[i]);
    listDir(newPathName);
  }
  closedir(curDir);
}

int main(int argc, char *argv[]) {
    // list all the directory
  for (int i = 1; i < argc; i++)
    listDir(argv[i]);
  int fd, num, ret, i;
  char *p;
  char inotify_entity[BUFLEN];

  // inotify all the events in the directory and sub-directory
  fd = inotify_init();
  ret = inotify_add_watch(fd, "./", IN_ALL_EVENTS);
  strcpy(wname[ret], argv[1]);
  for (i = 0; i < cntDir; i++) {
    ret = inotify_add_watch(fd, dir[i], IN_ALL_EVENTS);
    strcpy(wname[ret], dir[i]);
  }
  while (1) {
    num = read(fd, inotify_entity, BUFLEN);
    for (p = inotify_entity; p < inotify_entity + num;) {
      printInotifyEvent((struct inotify_event *)p);
      p += sizeof(struct inotify_event) + ((struct inotify_event *)p)->len;
    }
  }
  return 0;
}