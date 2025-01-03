#include "ramfs.h"
#include "shell.h"
#ifndef ONLINE_JUDGE
  #define print(...) printf("\033[31m");printf(__VA_ARGS__);printf("\033[0m");
#else
  #define print(...) 
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int sls(const char *pathname) {
  node *pt_node=(node *)malloc(sizeof(node));
  if(pathname == NULL) pt_node=root;
  else {
      pt_node = find(pathname,root);
      if(pt_node == NULL) {
          printf("ls: cannot access '%s': No such file or directory\n",pathname);
          return 0;
      }
     else if(pt_node->type==DNODE)
     {
       printf("ls: cannot access '%s: Not a directory\n",pathname);
       return 0;
     }
  }
    for(int i=0;i<4096;i++) {
      if(pt_node->dirents[i]!=NULL) {
        printf("%s ",pt_node->dirents[i]->name);
      }
    }
  printf("\n");
  return 0;
}

int scat(const char *pathname) {
    if(find(pathname,root)==NULL) {
      printf("cat: %s: No such file or directory\n",pathname);
      return 0;
    }
  node *current_node=(node *)malloc(sizeof(node));
  current_node=findFatherNode(pathname);
  char *current_node_name=pathname;
  while(findFatherNode(current_node)!=root) {
    if(current_node->type==DNODE) {
      printf("%s: Not a directory\n",current_node->name);
      return 0;
    }
    current_node_name=FatherNodePathName(current_node_name);
    current_node=find(current_node_name,root);
  }
  node *pt_node=(node *)malloc(sizeof(node));
  pt_node=find(pathname,root);
  if(find(pathname,root)->type==DNODE) {
    printf("cat: %s: Is a directory\n",pathname);
    return 0;
  }
  else {
    char *output=(char *)malloc(sizeof(char)*4096);
    memset(output,0,4096);
    output=(char*)pt_node->content;
    for(int i=0;i<pt_node->size;i++)printf("%c",output[i]);
    printf("\n");
  }
  return 0;
}

int smkdir(const char *pathname) {
    node *pt_node=(node *)malloc(sizeof(node));
    pt_node=findFatherNode(pathname);
  if(pt_node==NULL) {
    printf("mkdir: cannot create directory '%s': No such file or directory\n",pathname);
    return 0;
  }
  node *current_node=(node *)malloc(sizeof(node));
  current_node=findFatherNode(pathname);
  char *current_node_name=pathname;
  while(findFatherNode(current_node)!=root) {
    if(current_node->type==DNODE) {
      printf("%s: Not a directory\n",current_node->name);
      return 0;
    }
    current_node_name=FatherNodePathName(current_node_name);
    current_node=find(current_node_name,root);
  }
  rmkfile(pathname);
  return 0;
}

int stouch(const char *pathname) {
  print("touch %s\n", pathname);

}

int secho(const char *content) {
  print("echo %s\n", content);

}

int swhich(const char *cmd) {
  print("which %s\n", cmd);

}

void init_shell() {

}

void close_shell() {

}

