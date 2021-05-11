/* 
Ćwiczenie 8.5. Zmień program fsize tak, aby wypisywał również inne informacje 
pochdzące z węzła pliku 
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_PATH 2048

void fsize(char *name);
void dirwalk(char *dir, void (*fcn)(char *name));

int main(int argc, char **argv)
{
    if (argc == 1)
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}

void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1)
    {
        fprintf(stderr, "fsize: nie mogę znaleźć %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
    printf("%8lld %8lld %8o %8hu %s\n", stbuf.st_ino, stbuf.st_size, stbuf.st_mode, stbuf.st_nlink, name);
}

void dirwalk(char *dir, void (*fcn)(char *name))
{
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL)
    {
        fprintf(stderr, "dirwalk: nie mogę otworzyć %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL)
    {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: za długa nazwa %s/%s\n", dir, dp->d_name);
        else
        {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
}