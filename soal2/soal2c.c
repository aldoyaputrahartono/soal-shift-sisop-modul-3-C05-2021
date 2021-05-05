#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>

int main(){
	pid_t child_id;
	int status;
	int fp1[2];
	int fp2[2];
	char output[1000];
	
	if(pipe(fp1)==-1){
		fprintf(stderr, "Pipe Failed" );
		return 1;
	}
	if(pipe(fp2)==-1){
		fprintf(stderr, "Pipe Failed" );
		return 1;
	}
	
	//system("ps aux | sort -nrk 3,3 | head -5");
	
	child_id = fork();
	if(child_id < 0) exit(0);
	if(child_id == 0){
		dup2(fp1[1], STDOUT_FILENO);
		close(fp1[0]);
		char *argv[] = {"ps", "aux", NULL};
		execv("/bin/ps", argv);
	}
	
	while(wait(&status) > 0);
	dup2(fp1[0], STDIN_FILENO);
	close(fp1[1]);
	
	child_id = fork();
	if(child_id < 0) exit(0);
	if(child_id == 0){
		dup2(fp2[1], STDOUT_FILENO);
		close(fp2[0]);
		char *argv[] = {"sort", "-nrk", "3,3", NULL};
		execv("/usr/bin/sort", argv);
	}
	
	while(wait(&status) > 0);
	dup2(fp2[0], STDIN_FILENO);
	close(fp2[1]);
	char *argv[] = {"head", "-5", NULL};
	execv("/usr/bin/head", argv);
	return 0;
}
