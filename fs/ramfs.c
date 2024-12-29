#include "ramfs.h"
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "stdio.h"
node *root = NULL;

#define NRFD 4096
FD fdesc[NRFD];
node *findFatherNode(const char *pathname)
{
    int lastposi=0;
    for(int i=strlen(pathname)-1;i>=0;i--)
    {
        if(pathname[i]=='/' && i>0 && pathname[i-1]!='/')
        {
            lastposi=i;
            break;
        }
    }
    char *fatherNodePathName;
    fatherNodePathName=(char *)malloc(strlen(pathname)+1);
    memset(fatherNodePathName,0,sizeof(fatherNodePathName));//分配空间
    for(int i=0;i<lastposi+1;i++) {
        fatherNodePathName[i]=pathname[i];
    }
    //strncpy(fatherNodePathName,pathname,lastposi+1);
    if(lastposi==0) {
        return root;
    }

    else {
        for(int i=lastposi+1;i<strlen(fatherNodePathName);i++) {
            fatherNodePathName[i]='\0';
        }
        return find(fatherNodePathName,root);
    }
}

node *find(const char *pathname, node *current_dir) {
    if (current_dir == NULL) {
        return NULL; // 检查当前目录是否有效
    }

    char *path_copy = (char *)malloc((strlen(pathname) + 1) * sizeof(char));
    if (path_copy == NULL) {
        return NULL; // 如果内存分配失败，则返回NULL
    }

    strcpy(path_copy, pathname); // 复制路径

    const char *delim = "/";
    char *token = strtok(path_copy, delim); // 获取第一个token

    while (1) {
        // 如果token为空（表示多个斜杠的情况），跳过
        if (strlen(token) == 0) {
            token = strtok(NULL, delim);
            continue;
        }

        int found = 0;

        for (int i = 0; i < current_dir->nrde; i++) {
            if (strcmp(current_dir->dirents[i]->name, token) == 0) {
                found = 1;
                char *next_token = strtok(NULL, delim); // 获取下一个token

                if (next_token == NULL) {
                    free(path_copy); // 在返回之前释放path_copy
                    return current_dir->dirents[i]; // 找到对应的文件/目录
                }

                current_dir = current_dir->dirents[i]; // 更新当前目录
                break;
            }
        }

        if (!found) {
            free(path_copy); // 在返回之前释放path_copy
            return NULL; // 找不到匹配项，返回NULL
        }

        token = strtok(NULL, delim); // 获取下一个token
    }

    free(path_copy); // 释放内存
    return NULL; // 没有找到匹配项
}



int ropen(const char *pathname, int flags) {
    node *pt_node=find(pathname,root);
    bool isNull=0;
    if(pt_node==NULL)
    {
        isNull=1;
        if(flags>=64&&flags<=67)
        {
            rmkfile(pathname);
        }
        else return -1;
    }
    else
    {
        for(int i=0;i<NRFD;i++)
        {
            if(fdesc[i].used==0)
            {
                if(flags==66 || flags==1026 || flags==2)
                {
                    fdesc[i].flags=2;
                }
                else if(flags==64 || flags==0)
                {
                    fdesc[i].flags=0;
                }
                else if(flags==1 || flags==65 || flags==1025 || flags==515)
                {
                    fdesc[i].flags=1;
                }
                if(flags==1025 ||flags==1026)
                {
                    fdesc[i].offset=pt_node->size;
                }
                if(flags==515&&isNull==0)
                {
                    runlink(pathname);
                    rmkdir(pathname);
                }
                fdesc[i].f=pt_node;
                return i;
            }
            if(i==NRFD-1&&fdesc[i].used==1)return -1;
        }
    }
    return  0;
}

int rclose(int fd) {
     if(fdesc[fd].used==1)
     {
        if(fdesc[fd].f->type==DNODE)
        {
            return -1;
        }
        else if(fdesc[fd].used==0)
        {
            return -1;
        }
        else{
            fdesc[fd].used=1;
        }
     }
     return 0;
}

ssize_t rwrite(int fd, const void *buf, size_t count) {

}

ssize_t rread(int fd, void *buf, size_t count) {
        
}

off_t rseek(int fd, off_t offset, int whence) {
    if(whence==SEEK_SET)
    {
        fdesc[fd].offset=offset;
    }
    else if(whence==SEEK_CUR)
    {
        fdesc[fd].offset+=offset;
    }
    else if(whence==SEEK_END)
    {
        fdesc[fd].offset=fdesc[fd].f->size+offset;
    }
}

int rmkdir(const char *pathname) {//make new directory
    if(find(pathname,root)!=NULL)
    {
        return -1;
    }
    else
    {
        node *pt_fatherNode=findFatherNode(pathname);
        if(pt_fatherNode==NULL)return -1;
        if(pt_fatherNode->type==FNODE)
        {
            return -1;
        }
        int lastposi=strlen(pathname)-1;
        for(int i=strlen(pathname)-1;i>=1;i--)
        {
            if(pathname[i]!='/'&&pathname[i-1]=='/')
            {
                lastposi=i;
                break;
            }
        }
        char newDirName[100];
        memset(newDirName,0,sizeof(newDirName));
        for(int i=lastposi;i<strlen(pathname);i++)
        newDirName[i-lastposi]=pathname[i];

        node *newDir=(node *)malloc(sizeof(node));
        // init_new_node(newDir);
        newDir->name=(char *)malloc(strlen(newDirName)+1);
        strcpy(newDir->name,newDirName);
        newDir->nrde=0;
        // newDir->dirents=malloc(4096*sizeof(node*));
        pt_fatherNode->dirents[pt_fatherNode->nrde]=newDir;
        pt_fatherNode->nrde++;
        return 0;
    }
}

int rrmdir(const char *pathname) {//remove directory

}
int rmkfile(const char *pathname) {//make new file
    if(find(pathname,root)!=NULL)
    {
        return -1;
    }
    else
    {
        node *pt_fatherNode=findFatherNode(pathname);
        if(pt_fatherNode==NULL)return -1;
        if(pt_fatherNode->type==FNODE)
        {
            return -1;
        }
        int lastposi=strlen(pathname)-1;
        for(int i=strlen(pathname)-1;i>=1;i--)
        {
            if(pathname[i]!='/'&&pathname[i-1]=='/')
            {
                lastposi=i;
                break;
            }
        }
        char newDirName[100];
        memset(newDirName,0,sizeof(newDirName));
        for(int i=lastposi;i<strlen(pathname);i++)
            newDirName[i-lastposi]=pathname[i];

        node *newDir=(node *)malloc(sizeof(node));
        // init_new_node(newDir);
        newDir->name=(char *)malloc(strlen(newDirName)+1);
        strcpy(newDir->name,newDirName);
        newDir->nrde=0;
        // newDir->dirents=malloc(4096*sizeof(node*));
        pt_fatherNode->dirents[pt_fatherNode->nrde]=newDir;
        newDir->type=FNODE;
        pt_fatherNode->nrde++;
        return 0;
    }
}

int runlink(const char *pathname) {
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
            node *pt_fatherNode=findFatherNode(pathname);
            for(int i=0;i<pt_fatherNode->nrde;i++)
            {
                if(strcmp(pt_fatherNode->dirents[i],pt_node->name)==0)
                {
                    strcpy(pt_fatherNode->dirents[i],"/0");
                    pt_fatherNode->nrde--; 
                    return 0;
                }
            }
        } 
    }
}

void init_ramfs() {
    root=malloc(sizeof(node));
    root->content=NULL;
    root->size=0;
    root->name="root";
    // root->dirents=malloc(4096*sizeof(node*));
    root->nrde=0;
    for(int i=0;i<NRFD;i++)
    {
        fdesc[i].used=0;
    }
}

void close_ramfs() {

}
