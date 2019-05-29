#include <assert.h>
#include <dirent.h>
#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#define MAX_DIRSIZE 1010
#define MAX_LEN 256

int level = 0;

// compare the filename character
int cmp(const void *a, const void *b) { 
  const char *c_a=(const char *)a;
  const char *c_b=(const char *)b;
  return strcmp(c_a,c_b);   
}

// print out the files
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
  int type[MAX_DIRSIZE];
  int cntFile, cntDir;
  char file[MAX_DIRSIZE][MAX_LEN], dir[MAX_DIRSIZE][MAX_LEN];
  ret = readdir_r(curDir, &entry, &result);
  cntFile=0; cntDir=0;
  while (result != NULL) {
    // ignore . and ..
    if (strcmp(entry.d_name, ".") == 0 || strcmp(entry.d_name, "..") == 0) {
      ret = readdir_r(curDir, &entry, &result);
      assert(ret == 0);
      continue;
    }
    assert(ret == 0);
    // file type:link, equal to regular file
    if (entry.d_type == DT_LNK) {
      strcpy(file[cntFile], entry.d_name);
      type[cntFile] = 1;
      cntFile++;
    }
    // file type: regular file
    else if (entry.d_type == DT_REG) {
      strcpy(file[cntFile], entry.d_name);
      type[cntFile] = 2;
      cntFile++;
    }
    // file type: directory
    else if (entry.d_type == DT_DIR) {
      strcpy(dir[cntDir], entry.d_name);
      cntDir++;
    }
    ret = readdir_r(curDir, &entry, &result);
    assert(ret == 0);
  }
  qsort(file, cntFile, sizeof(file[0]), cmp);
  qsort(dir, cntDir, sizeof(dir[0]), cmp);
  // differentiate between link file and regular file
  for (int i = 0; i < cntFile; i++) {
    if (type[i] == 1)
      printName("l", file[i]);
    else if (type[i] == 2)
      printName("f", file[i]);
    else
      printf("error\n");
  }
  for (int i = 0; i < cntDir; i++) {
    printName("d", dir[i]);
    sprintf(newPathName, "%s/%s", pathName, dir[i]);
    printf("%s\n", newPathName);
    listDir(newPathName);
  }
  closedir(curDir);
  level--;
}

int main(int argc, char *argv[]) { 
    listDir(argv[1]);
    return 0; 
}