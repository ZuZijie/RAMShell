#include "ramfs.h"
#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include  "stdio.h"

const char *content = "export PATH=/usr/bin/\n";
const char *ct = "export PATH=/home:$PATH";
int main() {
    init_ramfs();

    printf("%d\n", rmkdir("/home"));
    // assert(rmkdir("//home") == -1);
    // assert(rmkdir("/home/home/1") == -1);
    // assert(rmkdir("/home/ubuntu") == 0);
    // assert(rmkdir("/usr") == 0);
    // assert(rmkdir("/usr/bin") == 0);
    // assert(rwrite(ropen("/home///ubuntu//.bashrc", O_CREAT | O_WRONLY), content, strlen(content)) == strlen(content));

    // int fd = ropen("/home/ubuntu/.bashrc", O_RDONLY);
    char buf[105] = {0};
    return 0;
}