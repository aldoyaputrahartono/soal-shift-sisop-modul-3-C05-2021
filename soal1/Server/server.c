#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <ctype.h>
#define PORT 8080

typedef struct akun {
	char id[1024];
	char ps[1024];
} akun;

typedef struct file_tsv {
	char path[1024];
	char pub[1024];
	char thn[1024];
} file_tsv;

typedef struct client_serv {
	int cid;
	int login;
} client_serv;

akun list_akun[100];
file_tsv list_file[100];
bool akun_cek, file_cek, conn_cek;
int conn, akun_n, file_n;

char *lowercase(char *str){
	unsigned char *temp = (unsigned char *)str;
	while(*temp){
		*temp = tolower(*temp);
		temp++;
	}
	return str;
}

char *checkName(char *dir){
	char *name = strrchr(dir, '/');
	if(name == dir) return "";
	return name + 1;
}

char *checkExt(char *dir){
	char *unk = {"Unknown"};
	char *hid = {"Hidden"};
	char *tmp = strrchr(dir, '/');
	if(tmp[1] == '.') return hid;
	
	int i = 0;
	while(i < strlen(tmp) && tmp[i] != '.') i++;
	if(i == strlen(tmp)) return unk;
	
	char ext[400];
	int j = i;
	while(i < strlen(tmp)) ext[i-j] = tmp[i], i++;
	return lowercase(ext + 1);
}

void *ready(void *arg){
	client_serv cl = *(client_serv *) arg;
	int cid = cl.cid;
	int log = cl.login;
	
	while(conn_cek);
	conn_cek = 1;
	
	while(log){
		send(cid, "ready", 5, 0);
		
		char data[1024], id[1024], ps[1024], kode;
		memset(data, 0, sizeof(data));
		read(cid, data, sizeof(data));
		
		if(strcmp(data, "exit") == 0){
			printf("Exit berhasil\n");
			conn_cek = 0;
			break;
		}
		
		kode = data[0];
		int idx = 0;
		for(int i=2; i<strlen(data); i++){
			if(data[i] == '\t') break;
			id[idx] = data[i];
			idx++;
		}
		
		int idx2 = 0;
		for(int i=idx+3; i<strlen(data); i++){
			ps[idx2] = data[i];
			idx2++;
		}
		
		if(kode == 'r'){
			akun_cek = 1;
			akun akun_reg;
			strcpy(akun_reg.id, id);
			strcpy(akun_reg.ps, ps);
			list_akun[akun_n] = akun_reg;
			akun_n++;
			
			while(file_cek);
			file_cek = 1;
			FILE *filep = fopen("akun.txt", "a");
			fprintf(filep, "%s:%s\n", id, ps);
			fclose(filep);
			
			file_cek = 0;
			akun_cek = 0;
			
			printf("Register berhasil\n");
		}
		else if(kode == 'l'){
			bool done = 0;
			while(akun_cek);
			for(int i=0; i<akun_n; i++){
				if((strcmp(id, list_akun[i].id) == 0) && (strcmp(ps, list_akun[i].ps) == 0)){
					done = 1;
					break;
				}
			}
			
			send(cid, &done, sizeof(done), 0);
			if(done){
				printf("Login berhasil\n");
				while(1){
					char cmd[1024] = {0};
					read(cid, cmd, sizeof(cmd));
					
					if(strcmp(cmd, "add") == 0){
						char res[1024] = {0};
						read(cid, res, sizeof(res));
						
						char pub[1024]={0}, thn[1024]={0}, path[1024]={0};
						
						int idx = 0;
						for(int i=0; i<strlen(res); i++){
							if(res[i] == '\t') break;
							pub[idx] = res[i];
							idx++;
						}
						int idx2 = 0;
						for(int i=idx+1; i<strlen(res); i++){
							if(res[i] == '\t') break;
							thn[idx2] = res[i];
							idx2++;
						}
						int idx3 = 0;
						for(int i=idx+1+idx2+1; i<strlen(res); i++){
							path[idx3] = res[i];
							idx3++;
						}
						
						//copy file di path ke FILES
						char path_tmp[1024];
						strcpy(path_tmp, path);
						char *srcName = checkName(path_tmp);
						char *curr = getenv("PWD");
						char destP[400];
						sprintf(destP, "%s/FILES/%s", curr, srcName);
						
						printf("%s\n%s\n", path, destP);
						
						FILE *fsrc = fopen(path, "r");
						if(fsrc == NULL){
							printf("File tidak ada\n");
							send(cid, "Gagal", 5, 0);
						}
						else{
							FILE *fdst = fopen(destP, "w");
							char tmp = fgetc(fsrc);
							while(tmp != EOF){
								fputc(tmp, fdst);
								tmp = fgetc(fsrc);
							}
							fclose(fsrc);
							fclose(fdst);
							
							//insert to tsv
							file_tsv file_insert;
							strcpy(file_insert.path, destP);
							strcpy(file_insert.pub, pub);
							strcpy(file_insert.thn, thn);
							memset(list_file[file_n].path, 0, sizeof(list_file[file_n].path));
							memset(list_file[file_n].pub, 0, sizeof(list_file[file_n].pub));
							memset(list_file[file_n].thn, 0, sizeof(list_file[file_n].thn));
							list_file[file_n] = file_insert;
							file_n++;
							
							FILE *ftsv = fopen("files.tsv", "a");
							fprintf(ftsv, "%s\t%s\t%s\n", destP, pub, thn);
							fclose(ftsv);
							
							char path_tmp[1024];
							strcpy(path_tmp, destP);
							char *srcName = checkName(path_tmp);
							FILE *flog = fopen("running.log", "a");
							fprintf(flog, "Tambah : %s (%s:%s)\n", srcName, id, ps);
							fclose(flog);
							
							printf("Add berhasil\n");
							send(cid, "Sukses", 6, 0);
						}
						
					}
					else if(strcmp(cmd, "download") == 0){
						char fileName[1024] = {0};
						read(cid, fileName, sizeof(fileName));
						
						//cek fileName di tsv
						char path[1024];
						bool ada = 0;
						for(int i=0; i<file_n; i++){
							char path_tmp[1024];
							strcpy(path, list_file[i].path);
							strcpy(path_tmp, list_file[i].path);
							char *srcName = checkName(path_tmp);
							if(strcmp(fileName, srcName) == 0){
								ada = 1;
								break;
							}
						}
						
						//copy ke client
						if(ada){
							char destP[400];
							sprintf(destP, "/home/aldo/Sisop/Modul3/Soal1/Client/%s", fileName);
							FILE *fsrc = fopen(path, "r");
							FILE *fdst = fopen(destP, "w");
							char tmp = fgetc(fsrc);
							while(tmp != EOF){
								fputc(tmp, fdst);
								tmp = fgetc(fsrc);
							}
							fclose(fsrc);
							fclose(fdst);
							
							printf("Download berhasil\n");
							send(cid, "Sukses", 6, 0);
						}
						else{
							printf("File tidak ada\n");
							send(cid, "Gagal", 5, 0);
						}
					}
					else if(strcmp(cmd, "delete") == 0){
						char fileName[1024] = {0};
						read(cid, fileName, sizeof(fileName));
						
						//cek fileName di tsv
						char path[1024];
						bool ada = 0;
						for(int i=0; i<file_n; i++){
							char path_tmp[1024];
							strcpy(path, list_file[i].path);
							strcpy(path_tmp, list_file[i].path);
							char *srcName = checkName(path_tmp);
							if(strcmp(fileName, srcName) == 0){
								ada = 1;
								break;
							}
						}
						
						//delete file
						if(ada){
							char *curr = getenv("PWD");
							char destP[400];
							sprintf(destP, "%s/FILES/old-%s", curr, fileName);
							rename(path, destP);
							
							FILE *ftsv = fopen("files.tsv", "w");
							for(int i=0, idx_file=0; i<file_n; i++){
								if(strcmp(path, list_file[i].path) == 0) continue;
								fprintf(ftsv, "%s\t%s\t%s\n", list_file[i].path, list_file[i].pub, list_file[i].thn);
								file_tsv file_baru;
								strcpy(file_baru.path, list_file[i].path);
								strcpy(file_baru.pub, list_file[i].pub);
								strcpy(file_baru.thn, list_file[i].thn);
								memset(list_file[file_n].path, 0, sizeof(list_file[file_n].path));
								memset(list_file[file_n].pub, 0, sizeof(list_file[file_n].pub));
								memset(list_file[file_n].thn, 0, sizeof(list_file[file_n].thn));
								list_file[idx_file] = file_baru;
								idx_file++;
							}
							fclose(ftsv);
							
							FILE *flog = fopen("running.log", "a");
							fprintf(flog, "Hapus : %s (%s:%s)\n", fileName, id, ps);
							fclose(flog);
							
							file_n--;
							printf("Delete berhasil\n");
							send(cid, "Sukses", 6, 0);
						}
						else{
							printf("File tidak ada\n");
							send(cid, "Gagal", 5, 0);
						}
					}
					else if(strcmp(cmd, "see") == 0){
						for(int i=0; i<file_n; i++){
							char path_tmp[1024];
							strcpy(path_tmp, list_file[i].path);
							char *srcName = checkName(path_tmp);
							
							char ext_tmp[1024];
							strcpy(ext_tmp, list_file[i].path);
							char *srcExt = checkExt(ext_tmp);
							char ext_fin[1024];
							strcpy(ext_fin, srcExt);
							
							char name[2048];
							sprintf(name, "Nama:%s\n", srcName);
							char pub[2048];
							sprintf(pub, "Publisher:%s\n", list_file[i].pub);
							char thn[2048];
							sprintf(thn, "Tahun publishing:%s\n", list_file[i].thn);
							char ext[2048];
							sprintf(ext, "Ekstensi File : %s\n", ext_fin);
							char path[2048];
							sprintf(path, "Filepath : %s\n", list_file[i].path);
							char empty[2048] = "\n";
							
							send(cid, name, sizeof(name), 0);
							send(cid, pub, sizeof(pub), 0);
							send(cid, thn, sizeof(thn), 0);
							send(cid, ext, sizeof(ext), 0);
							send(cid, path, sizeof(path), 0);
							send(cid, empty, sizeof(empty), 0);
						}
						
						printf("See berhasil\n");
						send(cid, "Sukses", 6, 0);
					}
					else if(strcmp(cmd, "find") == 0){
						bool found = 0;
						char fileName[1024] = {0};
						read(cid, fileName, sizeof(fileName));
						
						for(int i=0; i<file_n; i++){
							char path_tmp[1024];
							strcpy(path_tmp, list_file[i].path);
							char *srcName = checkName(path_tmp);
							
							if(strstr(srcName, fileName) == NULL) continue;
							
							char ext_tmp[1024];
							strcpy(ext_tmp, list_file[i].path);
							char *srcExt = checkExt(ext_tmp);
							char ext_fin[1024];
							strcpy(ext_fin, srcExt);
							
							char name[2048];
							sprintf(name, "Nama:%s\n", srcName);
							char pub[2048];
							sprintf(pub, "Publisher:%s\n", list_file[i].pub);
							char thn[2048];
							sprintf(thn, "Tahun publishing:%s\n", list_file[i].thn);
							char ext[2048];
							sprintf(ext, "Ekstensi File : %s\n", ext_fin);
							char path[2048];
							sprintf(path, "Filepath : %s\n", list_file[i].path);
							char empty[2048] = "\n";
							
							send(cid, name, sizeof(name), 0);
							send(cid, pub, sizeof(pub), 0);
							send(cid, thn, sizeof(thn), 0);
							send(cid, ext, sizeof(ext), 0);
							send(cid, path, sizeof(path), 0);
							send(cid, empty, sizeof(empty), 0);
							
							found = 1;
						}
						
						if(found){
							printf("Find berhasil\n");
							send(cid, "Sukses", 6, 0);
						}
						else{
							printf("File tidak ada\n");
							send(cid, "Gagal", 5, 0);
						}
					}
					else if(strcmp(cmd, "logout") == 0){
						printf("Logout berhasil\n");
						break;
					}
				}
			}
			else printf("Login gagal\n");
		}
	}
	
	pthread_exit(0);
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
	mkdir("FILES", 0755);
	
	FILE *filep;
	char id[1024], ps[1024], tmp[1024];
	int idx = 0;
	filep = fopen("akun.txt", "a+");
	if(filep == NULL) exit(0);
	while(fscanf(filep, "%s\n", tmp) != EOF){
		memset(id, 0, sizeof(id));
		memset(ps, 0, sizeof(ps));
		
		int idx2 = 0;
		for(int i=0; i<strlen(tmp); i++){
			if(tmp[i] == ':') break;
			id[idx2] = tmp[i];
			idx2++;
		}
		
		int idx3 = 0;
		for(int i=idx2+1; i<strlen(tmp); i++){
			ps[idx3] = tmp[i];
			idx3++;
		}
		
		akun akun_baru;
		strcpy(akun_baru.id, id);
		strcpy(akun_baru.ps, ps);
		list_akun[idx] = akun_baru;
		idx++;
	}
	fclose(filep);
	
	char path[1024], pub[1024], thn[1024];
	int idx_file = 0;
	filep = fopen("files.tsv", "r");
	while(fscanf(filep, "%s", path) != EOF){
		fscanf(filep, "%s", pub);
		fscanf(filep, "%s", thn);
		
		file_tsv file_baru;
		strcpy(file_baru.path, path);
		strcpy(file_baru.pub, pub);
		strcpy(file_baru.thn, thn);
		list_file[idx_file] = file_baru;
		idx_file++;
	}
	fclose(filep);
	
	akun_n = idx;
	file_n = idx_file;
	akun_cek = 0;
	file_cek = 0;
	conn = 0;
	conn_cek = 0;
	
	int client;
	while(client = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)){
		printf("Client accepted\n");
		
		pthread_t th;
		client_serv client_baru;
		client_baru.cid = client;
		client_baru.login = 1;
		
		pthread_create(&th, NULL, ready, (void *) &client_baru);
		//pthread_join(th, NULL);
	}
	if (client < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
	
	close(client);
    return 0;
}
