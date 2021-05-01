#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void tokenize(char *cmd);
void execute();
void end();

char error_message[30] = "An error has occurred\n";
char *cmd = NULL;
size_t cap = 0;

int i;
char *token;
char *arr[256];

int main(void){
   while(1){
      printf("grsh> ");
      getline(&cmd, &cap, stdin);
     
      tokenize(cmd);
      
      if(strcmp(arr[0], "exit") == 0){
         end();
      }
      execute();
   }   
}

void tokenize(char *cmd){
   i = 0;
   token = strtok(cmd, "\n");
   while(token != NULL){
      arr[i] = token;
      i++;
      token = strtok(NULL, "\n");
   }
   arr[i] = NULL;
}

void execute(){
   int pID = fork();
   if(pID != 0){
      int s;
      waitpid(-1,&s,0);}
   else if(execvp(arr[0], arr) == -1){
         write(STDERR_FILENO, error_message, strlen(error_message));
   }
   
}

void end(){
   exit(0);
}
