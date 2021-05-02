#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void grsh_loop();
char *grsh_readln();
char **grsh_tokenize(char *line);
int grsh_run(char **args);
int grsh_exec(char **args);
int grsh_cd(char **args);
int grsh_exit(char **args);
char *builtin_str[] = {"cd","exit"};
int (*builtin_func[]) (char **) = {&grsh_cd,&grsh_exit};

char error_message[30] = "An error has occured\n";

int main(int argc, char **argv){

	grsh_loop();
	return 1;
}

void grsh_loop(){

	char *cmd;
	char **args;

	do{
	  printf("grsh> ");
	  cmd = grsh_readln();
	  args = grsh_tokenize(cmd);

	  free(args);
	} while(1);
}

char *grsh_readln(){

	char *line = NULL;
	size_t buff = 0;

	if(getline(&line, &buff, stdin) == -1){
	  if(feof(stdin)){
	    exit(1);
	  }
	  else{
	    write(STDERR_FILENO, error_message, strlen(error_message));
	    exit(0);
	  }
	}

	return line;
}

char **grsh_tokenize(char *line){

	int buff = 64;
	int pos = 0;
	char **tokens = malloc(buff * sizeof(char*));
	char *token;

	if(!tokens){
	  write(STDERR_FILENO, error_message, strlen(error_message));
	  exit(0);
	}

	token = strtok(line, " \t\r\n\a");
	while(token != NULL) {
	  tokens[pos] = token;
	  pos++;

	  if(pos >= buff){
	    buff += 64;
	    tokens = realloc(tokens, buff * sizeof(char*));
	    if(!tokens){
	      write(STDERR_FILENO, error_message, strlen(error_message));
	      exit(0);
	    }
	  }

	  token = strtok(NULL, " \t\r\n\a");
	}
	tokens[pos] = NULL;
	return tokens;
}

int grsh_run(char **args){

	pid_t pid;

	pid = fork();
	if(pid == 0){
	  if(execvp(args[0], args) == -1){
	    write(STDERR_FILENO, error_message, strlen(error_message));
	  }
	  exit(0);
	}
	else if(pid < 0){
	  write(STDERR_FILENO, error_message, strlen(error_message));
	}

	return 1;
}

int grsh_exec(char **args){

	int i;

	if(args[0] == NULL) {
	  return 1;
	}

	for(i = 0; i < (sizeof(builtin_str) / sizeof(char *)); i++){
	  if(strcmp(args[0], builtin_str[i]) == 0){
	    return(*builtin_func[i])(args);
	  }
	}
	return grsh_run(args);
}

int grsh_cd(char **args){

	if(args[1] == NULL){
	  write(STDERR_FILENO, error_message, strlen(error_message));
	}
	else{
	  if(chdir(args[1]) != 0){
	    write(STDERR_FILENO, error_message, strlen(error_message));
	  }
	}
	return 1;
}


int grsh_exit(char **args){

	return 0;
}
