#pragma once
#include <stdint.h>
#include <stdbool.h>

#define O_APPEND 02000//以追加模式打开文件，即打开文件后，文件描述符的偏移量指向文件的末尾，若不含此标志，则指向文件的开头；如果该标志单独出现默认可读
#define O_CREAT 0100//如果传入的文件路径不存在，就创建这个文件，但如果这个文件的父目录不存在，就创建失败；如果文件已存在就正常打开
#define O_TRUNC 01000// 如果传入的文件路径是存在的文件，并且同时还带有可写（O_WRONLY和O_RDWR）的标志，就清空这个文件
#define O_RDONLY 00//read only
#define O_WRONLY 01//write only 
#define O_RDWR 02//read and write

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

typedef struct node {
  enum { FNODE, DNODE } type;
  struct node **dirents; // if DTYPE child dir
  void *content;
  int nrde;//num of dirents
  char *name;
  int size;
} node;

typedef struct FD {
  bool used;
  int offset;
  int flags;
  node *f;
} FD;

typedef intptr_t ssize_t;
typedef uintptr_t size_t;
typedef long off_t;

int ropen(const char *pathname, int flags);
int rclose(int fd);
ssize_t rwrite(int fd, const void *buf, size_t count);
ssize_t rread(int fd, void *buf, size_t count);
off_t rseek(int fd, off_t offset, int whence);
int rmkdir(const char *pathname);
int rrmdir(const char *pathname);
int runlink(const char *pathname);
void init_ramfs();
void close_ramfs();
node *find(const char *pathname,node *current_dir);