#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const *argv[]) {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
	
	char cmd[1024], cmd2[1024], username[1024], pass[1024], temp[1024];
	
	while(1){
		printf("Menu:\n1. Register\n2. Login\n3. Exit\nPilih: ");
		scanf("%s", cmd);
		if(strcmp(cmd, "register") == 0){
			strcpy(username, "r ");
			printf("ID: ");
			getchar();
			scanf("%s", temp);
			strcat(username, temp);
			printf("Password: ");
			getchar();
			scanf("%s", pass);
			strcat(username, "\t");
			strcat(username, pass);
			send(sock, username, strlen(username), 0);
			printf("Register berhasil\n");
		}
		else if(strcmp(cmd, "login") == 0){
			strcpy(username, "l ");
			printf("ID: ");
			getchar();
			scanf("%s", temp);
			strcat(username, temp);
			printf("Password: ");
			getchar();
			scanf("%s", pass);
			strcat(username, "\t");
			strcat(username, pass);
			send(sock, username, strlen(username), 0);
			
			int feedback;
			read(sock, &feedback, sizeof(feedback));
			if(feedback){
				printf("Login berhasil\n");
				//send(sock, "sukses", 6, 0);
				while(1){
					printf("Perintah:\n1. Add\n2. Download\n3. Delete\n4. See\n5. Find\n6. Logout\nPilih: ");
					scanf("%s", cmd2);
					if(strcmp(cmd2, "add") == 0){
						send(sock, cmd2, sizeof(cmd2), 0);
						char pub[1024], thn[1024], path[1024], res[1024];
						
						printf("Publisher: ");
						getchar();
						scanf("%s", pub);
						strcpy(res, pub);
						printf("Tahun Publikasi: ");
						getchar();
						scanf("%s", thn);
						strcat(res, "\t");
						strcat(res, thn);
						printf("Filepath: ");
						getchar();
						scanf("%s", path);
						strcat(res, "\t");
						strcat(res, path);
						send(sock, res, strlen(res), 0);
						
						char feed[1024] = {0};
						read(sock, feed, sizeof(feed));
						if(strcmp(feed, "Sukses") == 0) printf("Add berhasil\n");
						else printf("Add gagal\n");
					}
					else if(strcmp(cmd2, "download") == 0){
						send(sock, cmd2, sizeof(cmd2), 0);
						char fileName[1024];
						
						scanf("%s", fileName);
						send(sock, fileName, sizeof(fileName), 0);
						
						char feed[1024] = {0};
						read(sock, feed, sizeof(feed));
						if(strcmp(feed, "Sukses") == 0) printf("Download berhasil\n");
						else printf("Download gagal\n");
					}
					else if(strcmp(cmd2, "delete") == 0){
						send(sock, cmd2, sizeof(cmd2), 0);
						char fileName[1024];
						
						scanf("%s", fileName);
						send(sock, fileName, sizeof(fileName), 0);
						
						char feed[1024] = {0};
						read(sock, feed, sizeof(feed));
						if(strcmp(feed, "Sukses") == 0) printf("Delete berhasil\n");
						else printf("Delete gagal\n");
					}
					else if(strcmp(cmd2, "see") == 0){
						send(sock, cmd2, sizeof(cmd2), 0);
						char feed[2048] = {0};
						read(sock, feed, sizeof(feed));
						while((strcmp(feed, "Sukses") != 0) && (strcmp(feed, "Gagal") != 0)){
							printf("%s", feed);
							memset(feed, 0, sizeof(feed));
							read(sock, feed, sizeof(feed));
						}
						if(strcmp(feed, "Sukses") == 0) printf("See berhasil\n");
						else printf("See gagal\n");
					}
					else if(strcmp(cmd2, "find") == 0){
						send(sock, cmd2, sizeof(cmd2), 0);
						char fileName[1024];
						
						scanf("%s", fileName);
						send(sock, fileName, sizeof(fileName), 0);
						
						char feed[1024] = {0};
						read(sock, feed, sizeof(feed));
						while((strcmp(feed, "Sukses") != 0) && (strcmp(feed, "Gagal") != 0)){
							printf("%s", feed);
							memset(feed, 0, sizeof(feed));
							read(sock, feed, sizeof(feed));
						}
						
						if(strcmp(feed, "Sukses") == 0) printf("Find berhasil\n");
						else printf("Find gagal\n");
					}
					else if(strcmp(cmd2, "logout") == 0){
						send(sock, cmd2, sizeof(cmd2), 0);
						break;
					}
					else printf("Input salah\n");
				}
			}
			else printf("Login gagal\n");
		}
		else if(strcmp(cmd, "exit") == 0){
			send(sock, cmd, sizeof(cmd), 0);
			break;
		}
		else printf("Input salah\n");
		
		
		//valread = read(sock, buffer, 1024);
		//printf("%s\n", buffer);
		//memset(buffer, 0, 1024);
	}
	
	close(sock);
    return 0;
}
