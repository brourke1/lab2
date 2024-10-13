#ifndef main_h
#define main_h

void cd(char *path);
void help();
char *pwd();
int file_isreg(const char *path);
char *path_resolution(char *env_var);
void execute(char *path);
int search(char *PATH, char *var);

#endif /* main_h */