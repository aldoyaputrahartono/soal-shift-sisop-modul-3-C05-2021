#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef struct data{
	int angka1;
	int angka2;
	long long int hasil;
} data;

long long int faktorial(int n){
	long long int res = 1;
	for(; n>0; n--) res*=n;
	return res;
}

void *fact(void* arg){
	data* d = (data*) arg;
	if(d->angka1 == 0 || d->angka2 == 0) d->hasil = 0;
	else if(d->angka1 < d->angka2) d->hasil = faktorial(d->angka1);
	else d->hasil = faktorial(d->angka1) / faktorial(d->angka1 - d->angka2);
}

void main(){
	key_t key = 1234;
	int *value;
	int shmid = shmget(key, sizeof(int) * 24, IPC_CREAT | 0644);
	value = shmat(shmid, NULL, 0);
	
	int matrixB[24] = {
		1, 9, 0, 1, 2, 1,
		1, 2, 2, 0, 2, 0,
		0, 1, 7, 1, 0, 1,
		1, 2, 0, 1, 6, 1
	};

	pthread_t tid[24];
	data d[24];
	printf("Matrix A: \n");
	for(int i=0; i<24; i++){
		d[i].angka1 = value[i];
		d[i].angka2 = matrixB[i];
		if(i%6 == 0 && i != 0) printf("\n");
		printf("%d\t", value[i]);
		pthread_create(&tid[i], NULL, &fact, (void*)&d[i]);
	}
	printf("\n\n");
	
	printf("Matrix B: \n");
	for(int i=0; i<24; i++){
		if(i%6 == 0 && i != 0) printf("\n");
		printf("%d\t", matrixB[i]);
		pthread_join(tid[i],NULL);
	}
	printf("\n\n");
	
	printf("Matrix Hasil: \n");
	for(int i=0; i<24; i++){
		if(i%6 == 0 && i != 0) printf("\n");
		printf("%lld\t", d[i].hasil);
	}
	printf("\n");
	
	shmdt(value);
	shmctl(shmid, IPC_RMID, NULL);
}
