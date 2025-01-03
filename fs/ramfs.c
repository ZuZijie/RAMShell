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
char *FatherNodePathName(char *pathname) {
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
    return  fatherNodePathName;
}

node *find(const char *pathname, node *current_dir) {
    if (current_dir == NULL) {
        return NULL; // 检查当前目录是否有效
    }

    // 分配内存并复制路径
    char *path_copy = (char *)malloc((strlen(pathname) + 1) * sizeof(char));
    if (path_copy == NULL) {
        return NULL; // 如果内存分配失败，则返回 NULL
    }
    strcpy(path_copy, pathname);

    const char *delim = "/";
    char *token = strtok(path_copy, delim); // 获取第一个 token

    // 循环处理路径中的每个部分
    while (token != NULL) {
        // 跳过空 token（连续斜杠）
        while (token != NULL && strlen(token) == 0) {
            token = strtok(NULL, delim);
        }

        // 如果跳过空 token 后，token 仍然是 NULL，则路径处理完毕
        if (token == NULL) {
            break;
        }

        int found = 0;

        // 在当前目录中查找与 token 匹配的节点
        for (int i = 0; i < current_dir->nrde; i++) {
            if (strcmp(current_dir->dirents[i]->name, token) == 0) {
                found = 1;

                // 获取下一个 token
                token = strtok(NULL, delim);

                // 跳过连续的空 token
                while (token != NULL && strlen(token) == 0) {
                    token = strtok(NULL, delim);
                }

                // 如果没有更多 token，则返回找到的节点
                if (token == NULL) {
                    free(path_copy); // 在返回之前释放 path_copy
                    return current_dir->dirents[i];
                }

                // 更新当前目录为找到的节点
                current_dir = current_dir->dirents[i];
                break;
            }
        }

        // 如果在当前目录中未找到匹配的节点
        if (!found) {
            free(path_copy); // 在返回之前释放 path_copy
            return NULL;
        }
    }

    free(path_copy); // 释放内存
    return current_dir; // 返回当前目录（如果路径为空，则返回当前目录）
}

int ropen(const char *pathname, int flags) {
    if(pathname[0] != '/') return -1;
    node *pt_node=find(pathname,root);
    bool isNull=0;
    if(pt_node==NULL)
    {
        isNull=1;
        if(flags>=64&&flags<=67)
        {
            if(rmkfile(pathname)==-1)return -1;
        }
        else return -1;
    }
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
                if(pt_node==NULL)pt_node=findFatherNode(pathname);
                fdesc[i].used=1;
                fdesc[i].f=find(pathname,root);
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
        else{
            fdesc[fd].used=1;
        }
     }
    else return -1;
     return 0;
}

ssize_t rwrite(int fd, const void *buf, size_t count) {
    if(fdesc[fd].used==0){
        return  -1;
    }
    else if(fdesc[fd].f->type==DNODE)return  -1;
    else if(fdesc[fd].flags==0) return  -1;
    else {
        buf=(char *)buf;
        // if(count>strlen(buf))count=strlen(buf);
        if(fdesc[fd].f->size<fdesc[fd].offset+count) {
            fdesc[fd].f->size=fdesc[fd].offset+count;
        }
        strncpy(fdesc[fd].f->content+fdesc[fd].offset,buf,count);
        fdesc[fd].offset+=count;
        return count;
    }
}

ssize_t rread(int fd, void *buf, size_t count) {
    if(fdesc[fd].used==0){
        return  -1;
    }
    else if(fdesc[fd].f->type==DNODE)return  -1;
    else if(fdesc[fd].flags==1) return  -1;
    else {
        int currentposi=fdesc[fd].offset;
        if(count>(fdesc[fd].f->size-fdesc[fd].offset)) {
            count=fdesc[fd].f->size-fdesc[fd].offset;
        }
        for (size_t i = 0; i < count; ++i) {
            strncpy(buf + i, fdesc[fd].f->content + fdesc[fd].offset + i, 1);
        }
        fdesc[fd].offset+=count;
        return count;
    }
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
    if(pathname[0]!='/')return -1;
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
        for(int i=0;i<strlen(newDirName);i++) {
            if (!( (newDirName[i] >= 'A' && newDirName[i] <= 'Z') ||
       (newDirName[i] >= 'a' && newDirName[i] <= 'z') ||
       (newDirName[i] >= '0' && newDirName[i] <= '9') ||
       newDirName[i] == '.')) {
                return -1;
       }
        }
        if(strlen(pathname)>32)return -1;
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
    if(pathname[0]!='/')return -1;
    node *pt_node=find(pathname,root);
    if(pt_node==NULL)return -1;
    if(pt_node->type==FNODE)return -1;
    if(pt_node==root)return -1;
    if(pt_node->nrde!=0)return -1;
    node * pt_fatherNode=findFatherNode(pathname);
    for(int i=0;i<sizeof(pt_fatherNode->dirents)/sizeof(node *);i++) {
        if(pt_fatherNode->dirents[i]!=NULL) {
            if(pt_fatherNode->dirents[i]==pt_node) {
                pt_fatherNode->dirents[i]=NULL;
                break;
            }
        }
    }
    return 0;
}
int rmkfile(const char *pathname) {//make new file
    if(pathname[0]!='/')return -1;
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
        for(int i=lastposi;i<strlen(pathname);i++) {

            if (!( (pathname[i] >= 'A' && pathname[i] <= 'Z') ||(pathname[i] >= 'a' && pathname[i] <= 'z') ||
       (pathname[i] >= '0' && pathname[i] <= '9') ||
       pathname[i] == '.')) {
                return -1;
       }
            newDirName[i-lastposi]=pathname[i];
        }
        for(int i=0;i<strlen(newDirName);i++) {

        }
        if(strlen(pathname)>32)return -1;
        node *newDir=(node *)malloc(sizeof(node));
        // init_new_node(newDir);
        newDir->name=(char *)malloc(strlen(newDirName)+1);
        strcpy(newDir->name,newDirName);
        newDir->nrde=0;
        // newDir->dirents=malloc(4096*sizeof(node*));
        pt_fatherNode->dirents[pt_fatherNode->nrde]=newDir;
        newDir->type=FNODE;
        newDir->size=0;
        newDir->content=malloc(1000*sizeof(void ));
        memset(newDir->content,0,1000*sizeof(void ));
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
                if(strcmp(pt_fatherNode->dirents[i]->name,pt_node->name)==0)
                {
                    // strcpy(pt_fatherNode->dirents[i],"/0");
                    pt_fatherNode->dirents[i]=NULL;
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
    free_node(root);
}
void free_node(node *root) {
    if (root == NULL) {
        return;
    }
        for (int i = 0; i < root->nrde; i++) {
            if (root->dirents[i] != NULL) {
                free_node(root->dirents[i]); // 递归释放子节点
                root->dirents[i] = NULL;
            }
        }
    free(root);
}