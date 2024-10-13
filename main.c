#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>


#include "helpers.h"
#include "main.h"


int main(int argc, char *argv[]){
    
    printf("Brian's own shell (Bosh) v1.0\n");
    //char *command = argv[1];
    //char *builtin_commands[2] = {"help", "exit"};

    char *input;
    char **parsed_input;

    int size = 100;
    while(1){
        printf("-> ");

        //get input
        fgets(input, size, stdin);

        input[strcspn(input, "\n")] = '\0';

        //int ISREG = file_isreg(input);
        parsed_input = parse(input, " ");
        

        if(strcmp(parsed_input[0], "help") == 0)  {help();}

        else if(strcmp(parsed_input[0], "exit") == 0)  {return 1;}

        else if(strcmp(parsed_input[0], "pwd") == 0)  {pwd();}

        else if(strcmp(parsed_input[0], "cd") == 0)  {cd(parsed_input[1]);}

        else  {execute(parsed_input[0]);}
        
    
       
       

    }
    

    free(parsed_input);
    //compare command to builtin commands
    //error if specified command not in list


    //printf("command: %s\n", command);
    //printf("my-shell>\n");
    return 0;
}

void help(){
    printf("Brian's own shell (Bosh) version 1.0.0 pre-release\n"
    "The following are valid commands for interacting with Bosh\n\
    help - Displays this menu detailing different available commands\n\
    exit - Quits the current shell\n\
    pwd  - Prints current working directory\n\
    cd   - Changes current working directory to specified path\n\
    \n");
}
char *pwd(){
    long size;
    char *buf;
    char *ptr;


    size = pathconf(".", _PC_PATH_MAX);


    if ((buf = (char *)malloc((size_t)size)) != NULL){
        ptr = getcwd(buf, (size_t)size);
    }

    printf("%s\n", ptr);
    return ptr;
}

void cd(char *path){
    chdir(path);
}

//checks if given string is a valid file
int file_isreg(const char *path) {
    struct stat st;

    if (stat(path, &st) < 0)
        return -1;

    return S_ISREG(st.st_mode);
}

char *path_resolution(char *env_var){
    char *PATH = getenv("PATH");
    char *token = strtok(PATH, ":");

    while(token != NULL){
        
        if(search(token, env_var)){
            char *result = malloc(strlen(token) + strlen(env_var) + 2);
            result = strcpy(result, token);
            result = strcat(result, "/");
            result = strcat(result, env_var);
            return result;
        }
        token = strtok(NULL, ":");
    }

    return NULL;
}

int search(char *PATH, char *var){

    DIR *folder;
    struct dirent *entry;
    int files = 0;

    folder = opendir(PATH);
    if(folder == NULL)
    {
        perror("Unable to read directory");
        return(1);
    }

    while( (entry=readdir(folder)) )
    {
        if(strcmp(entry->d_name, var) == 0){
            return 1;
        }
    }
    return 0;

    closedir(folder);
}

void execute(char *path){
    pid_t pid = fork();
            if(pid < 0){
                printf("error");
            }
            else if(pid == 0){
                if(access(path, F_OK) == 0){
                    execl(path, (const char*)NULL, (char*)NULL);
                }
                else{
                    path = path_resolution(path);
                    if(path != NULL){
                        execl(path, (const char*)NULL, (char*)NULL);
                    }
                    else{
                        printf("File does not exist\n");
                    }
                }
                
            }
            else{
                wait(NULL);
            }
    
}

/*
void read_dirent(){
    DIR *d;
    struct dirent *dir;
    char path[1000]="/home/joy/Downloads";
    d = opendir(path);
    char full_path[1000];
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            //Condition to check regular file.
            if(dir->d_type==DT_REG){
                full_path[0]='\0';
                strcat(full_path,path);
                strcat(full_path,"/");
                strcat(full_path,dir->d_name);
                printf("%s\n",full_path);
            }
        }
        closedir(d);
    }
    
    return(0);
}*/