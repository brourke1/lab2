#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "helpers.h"
#include "main.h"


int main(int argc, char *argv[]){
    
    printf("Brian's own shell (Bosh) v1.0\n");
    //char *command = argv[1];
    //char *builtin_commands[2] = {"help", "exit"};

    char *input;
    char **parsed_input;

    int size = 100;
    int i = 0;
    while(1){
        i = 0;
        printf("->");

        fgets(input, size, stdin);

        input[strcspn(input, "\n")] = '\0';
        parsed_input = parse(input, " ");

        if(strcmp(parsed_input[0], "help") == 0){
            help();
        }

        else if(strcmp(parsed_input[0], "exit") == 0){
            return 1;
        }

        else if(strcmp(parsed_input[0], "pwd") == 0){
            pwd();
        }

        else if(strcmp(parsed_input[0], "cd") == 0){
            cd(parsed_input[1]);
        }

        else{
            
            execl(parsed_input[0], parsed_input[1]);
        }



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
void pwd(){
    long size;
    char *buf;
    char *ptr;


    size = pathconf(".", _PC_PATH_MAX);


    if ((buf = (char *)malloc((size_t)size)) != NULL){
        ptr = getcwd(buf, (size_t)size);
    }

    printf("%s\n", ptr);
}

void cd(char *path){
    chdir(path);
}