#include "ramfs.h"
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
node *root = NULL;

#define NRFD 4096
FD fdesc[NRFD];


find(const char *pathname, node *current_dir) {
    // 如果 pathname 为空或者当前目录为空，则直接返回 NULL
    if (pathname == NULL || current_dir == NULL) {
        return NULL;
    }

    // 复制 pathname 以避免修改原始字符串
    char path_copy[strlen(pathname) + 1];
    strcpy(path_copy, pathname);

    const char *delim = "/";  // 分隔符为 '/'
    char *token = strtok(path_copy, delim);  // 获取路径的第一个部分

    while (token != NULL) {
        int found = 0;

        // 遍历当前目录的目录项
        for (int i = 0; i < current_dir->nrde; i++) {
            // 如果找到了匹配的目录或文件
            if (strcmp(current_dir->dirents[i], token) == 0) {
                found = 1;

                // 如果这是路径中的最后一个部分（即文件或目录），就打印并返回当前目录节点
                if (strtok(NULL, delim) == NULL) {
                    printf("Found node at address: %p\n", (void *)current_dir);
                    return current_dir;  // 返回当前目录节点，表示找到了路径
                }

                // 否则，更新 current_dir 为子目录，并继续查找
                current_dir = current_dir->nrde[i];
                break;
            }
        }

        if (!found) {
            return NULL;
        }

        token = strtok(NULL, delim);
    }

    return NULL;  
}

int ropen(const char *pathname, int flags) {

}

int rclose(int fd) {

}

ssize_t rwrite(int fd, const void *buf, size_t count) {

}

ssize_t rread(int fd, void *buf, size_t count) {

}

off_t rseek(int fd, off_t offset, int whence) {

}

int rmkdir(const char *pathname) {//make new directory

}

int rrmdir(const char *pathname) {//remove directory

}

int runlink(const char *pathname) {

}

void init_ramfs() {
    root=malloc(sizeof(node));
    root->content=NULL;
    root->size=0;
    root->name=root;
    root->dirents=NULL;
    root->nrde=0;
}

void close_ramfs() {

}