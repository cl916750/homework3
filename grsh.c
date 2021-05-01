#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


char *cmd = NULL;
size_t cap = 0; 

int i;
char *token;
char *arr[256];

void cd();
void path();
void end();
void tokenize(char *cmd);

int main(void){
   while(1){
      printf("grsh> ");
      getline(&cmd, &cap, stdin);
     
      tokenize(cmd);
      
      if(strcmp(arr[0], "exit") == 0){
         end();
      }
      else{
         printf("test");
         end();
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

void cd(){

}

void path(){

}

void end(){
   exit(0);
}
