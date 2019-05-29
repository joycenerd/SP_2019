#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int level = 0;
int cmp(const void *a, const void *b) { return strcmp((char *)a, (char *)b); }
void printName(char *type, char *name) {
  printf("%s", type);
  for (int i = 0; i < level; i++)
    printf("  ");
  if (strcmp("d", type) == 0)
    printf("+");
  else
    printf("|");
  printf("%s\n", name);
}

void listDir(char *pathName) {
  level++;
  DIR *curDir = opendir(pathName);
  assert(curDir != NULL);
  char *newPathName = (char *)malloc(PATH_MAX);
  struct dirent entry;
  struct dirent *result;
  int ret;
  unsigned short type[1000];
  int file_count = 0, dir_count = 0;
  char file[1000][50], dir[1000][50];
  ret = readdir_r(curDir, &entry, &result);
  while (result != NULL) {
    // ignore . and ..
    if (strcmp(entry.d_name, ".") == 0 || strcmp(entry.d_name, "..") == 0) {
      ret = readdir_r(curDir, &entry, &result);
      assert(ret == 0);
      continue;
    }
    assert(ret == 0);
    if (entry.d_type == DT_LNK) {
      strcpy(file[file_count], entry.d_name);
      type[file_count] = 1;
      file_count++;
    }
    if (entry.d_type == DT_REG) {
      strcpy(file[file_count], entry.d_name);
      type[file_count] = 2;
      file_count++;
    }
    if (entry.d_type == DT_DIR) {
      strcpy(dir[dir_count], entry.d_name);
      dir_count++;
      // printName("d", entry.d_name);
      // sprintf(newPathName, "%s/%s", pathName, entry.d_name);
      // printf("%s\n", newPathName);
      // listDir(newPathName);
    }
    ret = readdir_r(curDir, &entry, &result);
    assert(ret == 0);
  }
  qsort(file, file_count, sizeof(file[0]), cmp);
  qsort(dir, dir_count, sizeof(dir[0]), cmp);
  for (int i = 0; i < file_count; i++) {
    if (type[i] == 1)
      printName("l", file[i]);
    else if (type[i] == 2)
      printName("f", file[i]);
    else
      printf("error\n");
  }
  for (int i = 0; i < dir_count; i++) {
    printName("d", dir[i]);
    sprintf(newPathName, "%s/%s", pathName, dir[i]);
    printf("%s\n", newPathName);
    listDir(newPathName);
  }
  closedir(curDir);
  level--;
}

int main(int argc, char **argv) { listDir(argv[1]); }