#pragma once
#include <stdint.h>
#include <stdbool.h>

#define O_APPEND 02000//以追加模式打开文件，即打开文件后，文件描述符的偏移量指向文件的末尾，若不含此标志，则指向文件的开头；如果该标志单独出现默认可读
#define O_CREAT 0100//如果传入的文件路径不存在，就创建这个文件，但如果这个文件的父目录不存在，就创建失败；如果文件已存在就正常打开
#define O_TRUNC 01000// 如果传入的文件路径是存在的文件，并且同时还带有可写（O_WRONLY和O_RDWR）的标志，就清空这个文件
#define O_RDONLY 00//read only
#define O_WRONLY 01//write only 
#define O_RDWR 02//read and write
// 64 O_CREAT：仅创建
// 0  RDONLY: 仅可读
// 1 O_WRONLY: 仅可写
// 2 O_RDWR：可读写
// 66 O_CREAT | O_RDWR：创建与读写
// 64 O_CREAT | O_RDONLY：创建与只读
// 65 O_CREAT | O_WRONLY：创建与只写
// 67  O_CREAT | O_RDWR | O_WRONLY：创建与只写（见前文说明）
// 1026 O_APPEND | O_RDWR：追加可读写（追加时只需要在open时设置offset即可，之后的write不需要再设置offset，可以参考样例4）
// 1025 O_APPEND | O_WRONLY：追加与只写
// 515 O_TRUNC | O_WRONLY | O_RDWR：覆盖与只写（见前文说明）


#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

typedef struct node
{
  enum { FNODE, DNODE } type;
  struct node   * dirents[4096];
  // if DTYPE child dir
  void *content;
  int nrde;//num of dirents
  char *name;
  int size;
} node;

typedef struct FD 
{
  bool used;
  int offset;
  int flags;
  node *f;
} FD;
extern struct node *root;
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
void init_new_node(node *new_node);
int rmkfile(const char *pathname);
void free_node(node *root);
node *findFatherNode(const char *pathname);
char *FatherNodePathName(char *pathname);