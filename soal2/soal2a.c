#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main(){
	key_t key = 1234;
	int *value;
	int shmid = shmget(key, sizeof(int) * 24, IPC_CREAT | 0644);
	value = shmat(shmid, NULL, 0);
 
	int sum = 0;
	int first[4][3] = {
		{2, 1, 1},
		{1, 2, 0},
		{2, 0, 1},
		{0, 2, 0}
	};
	int second[3][6] = {
		{1, 2, 0, 1, 2, 1},
		{1, 2, 2, 0, 2, 0},
		{0, 1, 0, 1, 0, 1}
	};
	int multiply[4][6];
	
	printf("Matrix 4x3: \n");
	for(int i=0; i<4; i++){
		for(int j=0; j<3; j++){
			printf("%d\t", first[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	printf("Matrix 3x6: \n");
	for(int i=0; i<3; i++){
		for(int j=0; j<6; j++){
			printf("%d\t", second[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	for(int i=0; i<4; i++){
		for(int j=0; j<6; j++){
			for(int k=0; k<3; k++) {
				sum = sum + first[i][k] * second[k][j];
			}
			multiply[i][j] = sum;
			sum = 0;
		}
	}
	
	printf("Matrix Hasil: \n");
	for(int i=0; i<4; i++){
		for(int j=0; j<6; j++){
			value[6*i+j] = multiply[i][j];
			printf("%d\t",multiply[i][j]);
		}
		printf("\n");
	}
	shmdt(value);
	return 0;
}
