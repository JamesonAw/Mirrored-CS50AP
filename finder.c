/**********************************
 * finder.c
 *
 * CS50 AP
 * Finder
 *
 * Searches for a target string in
 * all files in a directory
 * Jameson
 *
 **********************************/

#define _BSD_SOURCE
#define _GNU_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

// struct to hold the file name and type
typedef struct
{
    string name;
    string type;
}
path;

// struct to hold the directory info
typedef struct
{
    string name;
    int npaths;
    path* paths;
}
directory;

// string to hold the word to seek
string key;

// the function to search for files in a directory and populate the struct
directory populate(directory dir);

// the function to recursively iterate through directories and handle files
int seek(directory dir);

// main - sets arguments and calls the seek function
int main(int argc, char* argv[])
{

    // TODO: ensure proper number of command line arguments
    if(argc != 2 && argc != 3)
    {
        printf("Enter valid arguments! (./finder foo or ./finder foo bar)\n");
        return 1;
    }
    //store key value
    key = argv[1];
    // create initial directory
    directory dir;

    // TODO: set "dir"s name based on command line arguments entered
    if(argc == 3){
        dir.name = argv[2];
    }
    else
    {
        dir.name  = "./";
    }
    // call the seek function
    seek(dir);
    return 0;
}

// for a given directory, searches for files and fills array in the struct
directory populate(directory dir)
{
    // initialize all pointers and values in the given struct
    dir.npaths = 0;
    dir.paths = NULL;
    DIR* dirp;
    struct dirent* entry;

    // opendir is a system call that opens a "directory stream" containing
    // information about all files in the given directory (represented here
    // by dir.name)
    dirp = opendir(dir.name);
    if (dirp == NULL)
    {
        printf("Opening directory failed. Check your input filepath!\n");
        return dir;
    }

    // while directory stream still contains files, seek through them
    while((entry = readdir(dirp)) != NULL)
    {
        // if entry is a directory and not '.' or '..',
        // increase file count and populate the struct
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            // allocate zeroed-out memory for the construction of the file name
            string name = calloc(1, strlen(dir.name) + strlen(entry->d_name) + 2);
            strcat(name, dir.name);
            strcat(name, entry->d_name);
            strcat(name, "/");

            // reallocate memory to expand the array
            dir.paths = realloc(dir.paths, (dir.npaths + 1) * sizeof(path));

            // add a new element to the array containing names and types
            path newPath = {.name = name, .type = "directory"};
            dir.paths[dir.npaths] = newPath;

            // increase file count for the directory
            dir.npaths++;
        }

        // else if entry is a file, increase file count and populate the struct
        else if (entry->d_type == DT_REG)
        {
            // allocate zeroed-out memory for the construction of the file name
            string name = calloc(1, strlen(dir.name) + strlen(entry->d_name) + 1);
            strcat(name, dir.name);
            strcat(name, entry->d_name);

            // reallocate memory to expand the array
            dir.paths = realloc(dir.paths, (dir.npaths + 1) * sizeof(path));

            // add a new element to the array containing names and types
            path newPath = {.name = name, .type = "file"};
            dir.paths[dir.npaths] = newPath;

            // increase file count for the directory
            dir.npaths++;
        }
    }

    // close directory stream using system call closedir and return struct
    closedir(dirp);
    return dir;

}

// recursive function to iterate through directories and search files
int seek(directory dir)
{
    //popuate directory
    dir = populate(dir);
    //look at each path
    for(int i = 0; i < dir.npaths; i++)
    {
        //if the current path is a file, and not found.txt or ./finder
        if(strcmp(dir.paths[i].type,"file") == 0 && strcmp(dir.paths[i].name,"./found.txt") != 0 && strcmp(dir.paths[i].name,"./finder") != 0)
        {
            //create a file reader
            FILE *fr = fopen(dir.paths[i].name,"r");
            //make sure reader is not null
            if(fr == NULL)
            {
                printf("invalid path: %s\n",dir.paths[i].name);
                return 1;
            }
            //create an array to store words in the file
            char word[50];
            //create a boolean to keep track if it is the first time a word is found in the file
            bool found = false;
            //run the while loop until we are at the end of the file
            while(fgets(word,sizeof(word),fr) != NULL)
            {

                //for debugging
                /*if(strcmp(dir.paths[i].name,"./dogs.txt") == 0)
                {
                    printf("the word in the file is: %s\n",word);
                }*/
                //create a string to store the substring
                char *sub;
                //try find and assign a substring in the current words of the file
                sub = strstr(word,key);
                //if a substring is not found, assign sub to all the current words
                if(sub == NULL)
                {
                    sub = word;
                }
                /*
                if sub is longer than key, add a null terminator sub so that it is the same size of
                key. Substring returns a pointer to the start of the string, for example
                if you had a sentence, like: "dogs are great!" , and you are looking for great
                strstr would give you a pointer to the start of great, but would contain
                also the !. Adding a null terminator to the character in the equivalent spot
                in the key makes the later usage of strcmp properly work.
                */
                if(strlen(sub) > strlen(key))
                {
                    sub[strlen(key)] = '\0';
                }
                //compare the substring to the key
                if(strcmp(sub,key) == 0)
                {
                    //printf("found in %s\n", dir.paths[i].name); //optional print
                    //begin appending to found.txt
                    FILE *fw = fopen("found.txt","a");
                    if (fw == NULL)
                    {
                        printf("problems writing to found.txt\n");
                        return 1;
                    }
                    //if the first time, also print information about the file
                    if(!found)
                    {
                        fputs("for keyword ",fw);
                        fputs(key,fw);
                        fputs(" in ",fw);
                        fputs(dir.paths[i].name,fw);
                        fputs(":\n",fw);
                        found = true;
                    }
                    //print the word
                    fputs(key,fw);
                    fputs("\n",fw);
                    fclose(fw);
                }
            }
            fclose(fr);
        }
        //if a directory, make a new directory and do a recursive call to seek
        else if(strcmp(dir.paths[i].type,"directory") == 0)
        {
            directory nDir;
            nDir.name = dir.paths[i].name;
            seek(nDir);
        }
    }
    return 0;
}