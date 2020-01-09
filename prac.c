    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <dirent.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    void remove_dir_content(const char *path)
    {
        struct dirent *de;
        char fname[300];
        DIR *dr = opendir(path);
        if(dr == NULL)
        {
            printf("No file or directory found\n");
            return;
        }
        while((de = readdir(dr)) != NULL)
        {
            int ret = -1;
            struct stat statbuf;
            sprintf(fname,"%s/%s",path,de->d_name);
            if (!strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."))
                        continue;
            if(!stat(fname, &statbuf))
            {
                if(S_ISDIR(statbuf.st_mode))
                {
                    printf("Is dir: %s\n",fname);
                    printf("Err: %d\n",ret = unlinkat(dirfd(dr),fname,AT_REMOVEDIR));
                    if(ret != 0)
                    {
                        remove_dir_content(fname);
                        printf("Err: %d\n",ret = unlinkat(dirfd(dr),fname,AT_REMOVEDIR));
                    }
                }
                else
                {
                    printf("Is file: %s\n",fname);
                    printf("Err: %d\n",unlink(fname));
                }
            }
        }
        closedir(dr);
    }
    void main()
    {
        char str[10],str1[20] = "../",fname[300]; // Use str,str1 as your directory path where it's files & subfolders will be deleted.
        printf("Enter the dirctory name: ");
        scanf("%s",str);
        strcat(str1,str);
        printf("str1: %s\n",str1);
        remove_dir_content(str1); //str1 indicates the directory path
    }