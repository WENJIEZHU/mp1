/** @file she&Log.c */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "log.h"

log_t Log;

extern char **environ;
int i = 0;
int main(int argc, char ** argv) {						
	log_t *m = &Log;	
	log_init(m);
	//-h
	if (argc == 2 && strcmp(argv[1],"-h") == 0 ){	
		printf("Shell by wzhu26\n");
	}
	//=
	if (argc == 2 && strcmp(argv[1],"=") == 0){	
		while(environ[i]) {
  			printf("%s\n", environ[i++]);
		}
    	}

	//-f <file>
	if (argc == 3 && strcmp(argv[1], "-f") ==0){
		FILE *file = fopen(argv[2],"r");
		char* buff = NULL;
		//char* t;
		size_t sizes = 0;
	while (getline(&buff, &sizes, file)> -1){
		if (strncmp(buff, "cd ",3) == 0){
			//printf("here is cd: %s\n", buff);
			//puts(strtok(buff,"cd "));
			//chdir(strtok(t, ".. "));
			
			char* z  = (char *) malloc(sizeof(buff));
			strcpy(z, buff);
			char *di = strtok(z, " ");
			di = strtok(NULL, " ");
			di[strlen(di)-1] = '\0';
			//puts(di);
			if (chdir(di)<0){
				printf("%s: No such file or directory\n", di);			
			}
		}	
		system(buff);
	}
		fclose(file);
		buff = NULL;
		free(buff);
		//free(file);
	}
	
	
	while(1) {
		signal(SIGINT, SIG_IGN);
		//Print a command prompt
		pid_t pid = getpid();        
        	char cwd[100];
        	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("(pid=%d)%s$", pid, cwd);
	
		//read the command from stdin
		char* buffer = NULL;
		size_t size = 0;
		ssize_t chars = getline(&buffer, &size, stdin);
		if(chars >0 && buffer[chars-1] =='\n') 
			buffer[chars-1] = '\0';
		//puts(buffer);
	
		//print the PID of process excuting the command
		printf(" Command executed by pid=%d\n", pid);
	
		/////BUILT-IN FUNCTIONS: 
		//cd
		if (strncmp(buffer, "cd ",3) == 0){
			char* h  = (char *) malloc(sizeof(buffer));
			strcpy(h, buffer);
			log_push(m, buffer);
			//puts("here is buffer: ");
			//puts(buffer);
			char *dir = strtok(h, " ");
			dir = strtok(NULL, " ");
			if (chdir(dir) < 0){
				printf("%s: No such file or directory\n", dir);			
			}
			free(h);
		}		
		//exit	
		if ((strncmp(buffer,"exit",4)== 0)){
			//log_push(m, buffer);
			log_destroy(m);
			//buffer = NULL;
			free(buffer);
			exit(0);
		}
		
		//!
        	if(strncmp(buffer, "!", 1) == 0){
			//!#
			if (strncmp(buffer, "!#", 2) == 0){
				//puts("here is head:");
				//puts(m -> head -> value);
				node* temp = m ->head;
				//puts("n");
				//if (temp == NULL){
				//	temp -> next = NULL;}
				while(temp != NULL && (temp != m -> tail)) {
					//puts(temp ->value);
					temp = temp->next;
				}
				while(temp != NULL) {
					printf("%s\n",temp->value);
					temp = temp->prev;
				}
			//free(buffer);
			}
			//!query
			else{
				char* r;
				if ((log_search(m, strtok(buffer, "!"))) != NULL){
					char * key = log_search(m, strtok(buffer, "!"));	
					printf("%s matches %s\n", strtok(buffer, "!"), key);
					r = buffer;
					buffer = strdup(key);
					free(r);	//free(key);
				}
				else{
					printf("No Match\n");
				}
			}
		}

		//////Non-built-in functions
		if ((strncmp(buffer,"cd ",3)!= 0) && (strncmp(buffer,"exit",4)!= 0) && (strncmp(buffer,"!",1)!= 0) ){
			//char* k = buffer;
			//puts("here is buffer: ");
			//puts(buffer);
			log_push(m, buffer);
			char* list[300];
			
			list[0] = strtok(buffer, " ");
			struct timeval start;
			gettimeofday(&start, 0);
  			pid_t child_pid;
  			int child_status;
  			child_pid = fork();
  			
			if(child_pid == 0) {
				char * b = list[0];
				int i =1;

				while (b != NULL){
					b = strtok(NULL," ");
					//puts(list[i+1]);
					list[i] = b;					
					i++;
				}

				list[i] = (char*)'\0';	
	
    				execvp(list[0], list);
				if (execvp(list[0], list) < 0)
					printf("%s: not found\n", list[0]);
    				_exit(0);
  			}
			else {
				//if(buffer[strlen(buffer)-1] == '&'){
									
				//}
				wait(&child_status);
				struct timeval end;
				gettimeofday(&end, 0);
				long elapsed = (end.tv_sec-start.tv_sec)*1000000 + end.tv_usec - start.tv_usec;
				printf("Execution took %ld microseconds.\n", elapsed) ;
			}
		}	
		//buffer = NULL;
		free(buffer);
		
	 }
	 return 0;
}
