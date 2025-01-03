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


}

int scat(const char *pathname) {
  print("cat %s\n", pathname);

}

int smkdir(const char *pathname) {
  print("mkdir %s\n", pathname);

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