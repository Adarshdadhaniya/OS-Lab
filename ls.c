/* Program to simulate the ls command of the Linux operating system.
   It lists all the files present in the given directory. */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

void main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;

    if (argc < 2)
    {
        printf("\nYou are not passing the directory\n");
        exit(1);
    } 

    if ((dp = opendir(argv[1])) == NULL)
    {
        printf("\nCannot open, it doesn't exist: %s\n", argv[1]);
        exit(1);
    }

    while ((dirp = readdir(dp)) != NULL)
        printf("%s\n", dirp->d_name);

    closedir(dp);
}
