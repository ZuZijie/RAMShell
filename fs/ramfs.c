#include "ramfs.h"
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
node *root = NULL;

#define NRFD 4096
FD fdesc[NRFD];

node *find(const char *pathname, node *current_dir) {
    char path_copy[strlen(pathname) + 1];
    strcpy(path_copy, pathname);

    const char *delim = "/";  
    char *token = strtok(path_copy, delim); 

    while (token != NULL) {
        if (strlen(token) == 0) {
            token = strtok(NULL, delim);  
            continue;  
        }

        int found = 0;

        for (int i = 0; i < current_dir->nrde; i++) {
            if (strcmp(current_dir->dirents[i], token) == 0) {
                found = 1;
                if (strtok(NULL, delim) == NULL) {
                    return current_dir;  
                }
                current_dir = current_dir->dirents[i];
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
    strcpy(root->name,"root");
    root->dirents=NULL;
    root->nrde=0;
}

void close_ramfs() {

}