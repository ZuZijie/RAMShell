#include "ramfs.h"
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "stdio.h"
node *root = NULL;

#define NRFD 4096
FD fdesc[NRFD];

node *find(const char *pathname, node *current_dir) {
    char *path_copy=malloc((strlen(pathname)+1)*sizeof(char));
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
            if (strcmp(current_dir->dirents[i]->name, token) == 0) {
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
    node *pt_node=find(pathname,root);
    if(pt_node==NULL)
    {
        return -1;
    }
    else
    {
        if(pt_node->type==DNODE)return -1;
        else
        {
            int lastposi=0;
            for(int i=strlen(pathname);i>=0;i--)
            {
                if(pathname[i]=='/'&&pathname[i-1]!='/')
                {
                    lastposi=i;
                    break;
                }//寻找对应的父目录
            }
            char *father_dir;
            strncpy(father_dir,lastposi,pathname);
            node *pt_father_node=find(father_dir,root);
            for(int i=0;i<pt_father_node->nrde;i++)
            {
                if(strcmp(pt_father_node->dirents[i]->name,pt_node->name)==0)
                {
                    strcpy(pt_father_node->dirents[i],NULL);
                    pt_father_node->nrde--; 
                    return 0;
                }
            }
        } 
    }
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
    //root->content=NULL;
    root->size=0;
    root->name="root";
    //root->dirents=NULL;
    root->dirents=malloc(sizeof(node *));
    root->nrde=0;
}

void close_ramfs() {

}
int main()
{
    char pathname[100]="/home/zoinve/test.c";
    init_ramfs();
    root->nrde=3;
    node *home;
    root->dirents[0]=malloc(sizeof(node *));
    root->dirents[0]->name="home";
    root->dirents[0]->nrde=1;
    node *zoinve;
    node *n3;
    root->dirents[0]->dirents[0]=malloc(sizeof(node *));
    strcpy(root->dirents[0]->dirents[0]->name,"test.c");
    n3->type=DNODE;
    zoinve->dirents[0]=n3;
    printf("%p",find("/home/zoinve/test.c",root));
    return 0;
}