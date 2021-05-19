# soal-shift-sisop-modul-3-C05-2021

Repository Praktikum Sisop Modul 3
- 05111940000073_Aji Wahyu Admaja Utama
- 05111940000084_Aldo Yaputra Hartono
- 05111940000204_Muhammad Subhan

## Penyelesaian Soal No.1
Keverk adalah orang yang cukup ambisius dan terkenal di angkatannya. Sebelum dia menjadi ketua departemen di HMTC, dia pernah mengerjakan suatu proyek dimana keverk tersebut meminta untuk membuat server database buku. Proyek ini diminta agar dapat digunakan oleh pemilik aplikasi dan diharapkan bantuannya dari pengguna aplikasi ini. 

Di dalam proyek itu, Keverk diminta: 

a. Pada saat client tersambung dengan server, terdapat dua pilihan pertama, yaitu register dan login. Jika memilih register, client akan diminta input id dan passwordnya untuk dikirimkan ke server. User juga dapat melakukan login. Login berhasil jika id dan password yang dikirim dari aplikasi client sesuai dengan list akun yang ada didalam aplikasi server. Sistem ini juga dapat menerima multi-connections. Koneksi terhitung ketika aplikasi client tersambung dengan server. Jika terdapat 2 koneksi atau lebih maka harus menunggu sampai client pertama keluar untuk bisa melakukan login dan mengakses aplikasinya. Keverk menginginkan lokasi penyimpanan id dan password pada file bernama **akun.txt** dengan format :

**akun.txt**
```txt
id:password
id2:password2
```

b. Sistem memiliki sebuah database yang bernama **files.tsv**. Isi dari **files.tsv** ini adalah **path file saat berada di server, publisher, dan tahun publikasi**. Setiap penambahan dan penghapusan file pada folder file yang bernama **FILES** pada server akan memengaruhi isi dari **files.tsv**. Folder **FILES** otomatis dibuat saat server dijalankan. 

c. Tidak hanya itu, Keverk juga diminta membuat fitur agar client dapat menambah file baru ke dalam server. Direktori **FILES** memiliki struktur direktori di bawah ini : 

Direktori **FILES**
```txt
File1.ekstensi
File2.ekstensi
```

Pertama client mengirimkan input ke server dengan struktur sebagai berikut :
Contoh Command Client :
```txt
add
```

Output Client Console :
```txt
Publisher:
Tahun Publikasi:
Filepath:
```

Kemudian, dari aplikasi client akan dimasukan data buku tersebut (perlu diingat bahwa Filepath ini merupakan **path file yang akan dikirim ke server**). Lalu client nanti akan melakukan pengiriman file ke aplikasi server dengan menggunakan socket. Ketika file diterima di server, maka row dari files.tsv akan bertambah sesuai dengan data terbaru yang ditambahkan.

d. Dan client dapat mendownload file yang telah ada dalam folder FILES di server, sehingga sistem harus dapat mengirim file ke client. Server **harus** melihat dari files.tsv untuk melakukan pengecekan apakah file tersebut valid. Jika tidak valid, maka mengirimkan pesan error balik ke client. Jika berhasil, file akan dikirim dan akan diterima ke client di **folder client** tersebut. 

Contoh Command client :
```txt
download TEMPfile.pdf
```

e. Setelah itu, client juga dapat menghapus file yang tersimpan di server. Akan tetapi, Keverk takut file yang dibuang adalah file yang penting, maka file hanya akan diganti namanya menjadi `old-NamaFile.ekstensi`. Ketika file telah diubah namanya, maka row dari file tersebut di file.tsv akan terhapus.

Contoh Command Client :
```txt
delete TEMPfile.pdf
```

f. Client dapat melihat semua isi **files.tsv** dengan memanggil suatu perintah yang bernama see. Output dari perintah tersebut keluar dengan format. 

Contoh Command Client :
```txt
see
```

Contoh Format Output pada Client :
```txt
Nama:
Publisher:
Tahun publishing:
Ekstensi File : 
Filepath : 

Nama:
Publisher:
Tahun publishing:
Ekstensi File : 
Filepath : 

```

g. Aplikasi client juga dapat melakukan pencarian dengan memberikan suatu string. Hasilnya adalah semua nama file yang mengandung string tersebut. Format output seperti nomor 6.

Contoh Client Command :
```txt
find TEMP
```

h. Dikarenakan Keverk waspada dengan pertambahan dan penghapusan file di server, maka Keverk membuat suatu log untuk server yang bernama **running.log**. Contoh isi dari log ini adalah

**running.log**
```txt
Tambah : File1.ektensi (id:pass)
Hapus : File2.ektensi (id:pass)
```

Akan tetapi, kevek saat itu masih belum paham dengan sistem server dan client. Bantulah Keverk untuk menyelesaikan proyek ini!

Note: 
- Dilarang menggunakan system() dan execv(). Silahkan dikerjakan sepenuhnya dengan thread dan socket programming. 
- Untuk download dan upload silahkan menggunakan file teks dengan ekstensi dan isi bebas (yang ada isinya bukan touch saja dan tidak kosong) dan requirement untuk benar adalah percobaan dengan minimum 5 data.

Struktur Direktori:
```txt
.
├── Client
│   ├── client.c
│   ├── File2.extensi
│   └── File1.extensi
└── Server
    ├── akun.txt
    ├── files.tsv
    ├── server.c
    ├── running.log
    └── FILES
            ├── File2.extensi
            └── File1.ekstensi
```

#
### Jawab 1a
Pada soal ini, client diberikan pilihan register atau login. Kami menambahkan pilihan exit untuk keluar dari aplikasi.
```c
//Pada Client

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

	...
}
else if(strcmp(cmd, "exit") == 0){
	send(sock, cmd, sizeof(cmd), 0);
	break;
}
else printf("Input salah\n");
```

Dikarenakan sistem harus multi-connections, maka akan digunakan thread setiap ada client yang connect. Jika terdapat 2 koneksi atau lebih maka harus menunggu sampai client pertama keluar untuk bisa melakukan login dan mengakses aplikasinya. Hal ini dilakukan dengan suatu variabel bantuan `conn_cek` yang awalnya diset FALSE dimana jika ada client yang connect maka conn_cek diset TRUE sehingga client lainnya hanya bisa connect tapi belum bisa mengakses pilihan menu.
```c
//Pada Server

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
	
	...
}
```

```c
//Pada Client

while(1){
	printf("Harap Menunggu\n\n");
	char stat[1024] = {0};
	read(sock, stat, sizeof(stat));
	while(strcmp(stat, "ready") != 0){
		memset(stat, 0, sizeof(stat));
		read(sock, stat, sizeof(stat));
	}
	memset(stat, 0, sizeof(stat));
	
	...
}
```
![11](https://user-images.githubusercontent.com/31863229/118823301-16878800-b8e3-11eb-8363-2c6093acf0a6.PNG)
![12](https://user-images.githubusercontent.com/31863229/118823412-2a32ee80-b8e3-11eb-951f-419ab46338ec.PNG)

Semua akun dari pengguna yang register akan disimpan pada **akun.txt** dan digunakan pula pada pengecekan akun saat login.
```c
//Pada Server

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
	
	...
}
```
![13](https://user-images.githubusercontent.com/31863229/118823417-2b641b80-b8e3-11eb-9e2b-e6e0b6261057.PNG)
![14](https://user-images.githubusercontent.com/31863229/118823421-2bfcb200-b8e3-11eb-80f8-1a3c697319a0.PNG)

#
### Jawab 1b
Terdapat **files.tsv** dan folder **FILES** pada folder Server. Pembuatan folder **FILES** dilakukan pada saat server berjalan.
```c
mkdir("FILES", 0755);
```

Kemudian untuk **files.tsv** akan diakses pada saat penambahan dan penghapusan data dan akan ditunjukkan pada soal selanjutnya.

#
### Jawab 1c
Terdapat perintah `add` untuk menambahkan files ke server. Client mengirimkan nama publisher, tahun publikasi, dan filepath lokasi file yang akan dikirimkan.
```c
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
```

Kemudian server menerima file tersebut dan dimasukkan ke folder **FILES**. Lakukan penambahan data file ke **files.tsv** juga.
```c
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
```
![15](https://user-images.githubusercontent.com/31863229/118823433-2e5f0c00-b8e3-11eb-9c02-e26666300fbb.PNG)

#
### Jawab 1d
Terdapat perintah `download` sehingga client dapat mendownload file yang ada di server. Client mengirimkan nama file yang akan di download.
```c
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
```

Server mengecek file tersebut pada **files.tsv**. Jika tidak valid maka mengirimkan pesan error. Jika valid maka file akan dikirim dan diterima client pada folder Client.
```c
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
```
![16](https://user-images.githubusercontent.com/31863229/118823440-2f903900-b8e3-11eb-9f43-e3e8473f9084.PNG)

#
### Jawab 1e
Terdapat perintah `delete` untuk menghapus file yang ada di server. Client mengirimkan nama file yang akan di delete.
```c
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
```

Server mengecek file tersebut pada **files.tsv**. Jika tidak valid maka mengirimkan pesan error. Jika valid maka file akan direname menjadi `old-NamaFile.ekstensi` dan data file pada **files.tsv** dihapus.
```c
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
```
![17](https://user-images.githubusercontent.com/31863229/118823447-30c16600-b8e3-11eb-8f2f-98e61d20f315.PNG)

#
### Jawab 1f
Terdapat perintah `see` untuk melihat semua isi **files.tsv**. Client hanya cukup mengirimkan `see`.
```c
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
```

Server mengirimkan isi dari **files.tsv** ke client dan ditampilkan sesuai format pada soal.
```c
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
```
![18](https://user-images.githubusercontent.com/31863229/118823456-3159fc80-b8e3-11eb-98ea-a7eded2f97f4.PNG)

#
### Jawab 1g
Terdapat perintah `find` untuk melakukan pencarian nama file. Client mengirimkan suatu string yang merupakan substring dari nama file yang dicari.
```c
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
```

Server mencari nama file yang mengandung string dari client lalu mengirimkan isi data file ke client dan ditampilkan sesuai format pada soal.
```c
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
```
![19](https://user-images.githubusercontent.com/31863229/118823461-328b2980-b8e3-11eb-9d60-d62dcf214a42.PNG)

#
### Jawab 1h
Terdapat **running.log** untuk menyimpan log saat terjadi pertambahan dan penghapusan file di server. Hal ini dilakukan pada saat client menjalankan perintah `add` dan `delete`. Format pengisian log sesuai yang diminta soal dan sudah diimplementasikan pada soal sebelumnya.

![110](https://user-images.githubusercontent.com/31863229/118823470-33bc5680-b8e3-11eb-84f0-cb49798b4fe1.PNG)

#
### Kendala
1. Soalnya panjang banget dan kompleks sekali.
2. Kebingungan untuk multi-connection karena pada modul hanya 1 connection.
3. Penggunaan socket sebagai penghubung antara client dan server sangat banyak karena fitur aplikasi cukup banyak serta untuk error handling.

#
## Penyelesaian Soal No.2
Crypto (kamu) adalah teman Loba. Suatu pagi, Crypto melihat Loba yang sedang kewalahan mengerjakan tugas dari bosnya. Karena Crypto adalah orang yang sangat menyukai tantangan, dia ingin membantu Loba mengerjakan tugasnya. Detil dari tugas tersebut adalah:

a. Membuat program perkalian matrix (4x3 dengan 3x6) dan menampilkan hasilnya. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).

b. Membuat program dengan menggunakan matriks output dari program sebelumnya (program soal2a.c) (**Catatan!:** gunakan shared memory). Kemudian matriks tersebut akan dilakukan perhitungan dengan matrix baru sebagai berikut contoh perhitungan untuk matriks yang ada. Perhitungannya adalah setiap cel yang berasal dari matriks A menjadi angka untuk faktorial, lalu cel dari matriks B menjadi batas maksimal faktorialnya (dari paling besar ke paling kecil) (**Catatan!:** gunakan thread untuk perhitungan di setiap cel). 

**Ketentuan**
```txt
If a >= b  -> a!/(a-b)!
If b > a -> a!
If 0 -> 0
```

Contoh :
| A | B | Angka-Angka Faktorial |
|---|---|-----------------------|
| 4 | 4	| 4 3 2 1               |
| 4 | 5	| 4 3 2 1               |
| 4 | 3	| 4 3 2                 |
| 4 | 0	| 0                     |
| 0 | 4	| 0                     |
| 4 | 6	| 4 3 2 1               |

Contoh :
| Matriks A | Matriks B	|        Matriks Hasil       |
|-----------|-----------|----------------------------|
|   0   4   |   0   4   | 0               4\*3\*2\*1 |
|   4   5   |   6   2   | 4\*3\*2\*1      5\*4       |
|   5   6   |   6   0   | 5\*4\*3\*2\*1   0          |

c. Karena takut lag dalam pengerjaannya membantu Loba, Crypto juga membuat program (soal2c.c) untuk mengecek 5 proses teratas apa saja yang memakan resource komputernya dengan command `ps aux | sort -nrk 3,3 | head -5` (**Catatan!:** Harus menggunakan IPC Pipes)

Note:
- Semua matriks berasal dari input ke program.
- Dilarang menggunakan system()

#
### Jawab 2a
Pada soal 2a kita diminta untuk membuat matriks yang ber ordo 4x3 dan 3x6 dan menyimpan dalam shared memory. Sebelum menjalankan proses perkalian matriks, lakukan setting pada shared memory sebagai berikut.
```c
key_t key = 1234;
int *value;
int shmid = shmget(key, sizeof(int) * 24, IPC_CREAT | 0644);
value = shmat(shmid, NULL, 0);
```

Buat matriks pertama berukuran 4x3 dan matriks kedua berukuran 3x6.
```c
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
```

Print isi matriks untuk memudahkan melihat proses perkalian matriks.
```c
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
}
printf("\n");
```

Kita mengkalikan kedua matriks dan menampung hasilnya di matriks multiply. Pada matriks multiply kita menggunakan prinsip perkalian matriks untuk menentukan ordo dari matriks multiply yaitu ketika AXB dan BXC maka ordo tersebut akan menjadi AXC. Pada soal ini kita mengalikan matriks yang ber ordo 4X3 dan 3X6 sehingga bentuk dari matriks hasil adalah 4X6.
```c
for(int i=0; i<4; i++){
	for(int j=0; j<6; j++){
		for(int k=0; k<3; k++) {
			sum = sum + first[i][k] * second[k][j];
		}
		multiply[i][j] = sum;
		sum = 0;
	}
}
```

Pindahkan isi dari matriks multiply ke array value sehingga dapat diakses oleh file lainnya melalui shared memory.
```c
printf("Matrix Hasil: \n");
for(int i=0; i<4; i++){
	for(int j=0; j<6; j++){
		value[6*i+j] = multiply[i][j];
		printf("%d\t",multiply[i][j]);
	}
	printf("\n");
}
shmdt(value);
```

#
### Jawab 2b
Pada soal ini kita diminta mengoperasikan kembali matriks A yang kita dapat pada soal 2a dengan matriks B yang terdapat pada soal 2b. Untuk pengoperasiannya terdapat beberapa ketentuan dimana matriks A menjadi angka untuk faktorial lalu matriks B menjadi batas maksimal faktorialnya. Dengan ini kita dapat membuat fungsi untuk threadnya.
```txt
jika a >= b maka a!/(a-b)!
jika b >  a maka a!
jika 0      maka output akan tetap 0
```

```c
void *fact(void* arg){
	data* d = (data*) arg;
	if(d->angka1 == 0 || d->angka2 == 0) d->hasil = 0;
	else if(d->angka1 < d->angka2) d->hasil = faktorial(d->angka1);
	else d->hasil = faktorial(d->angka1) / faktorial(d->angka1 - d->angka2);
}
```

Pertama kita membuat matriks B dan memanggil array value pada soal 2a menggunakan shared memory.
```c
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
```

Tampilkan isi array value pada soal 2a untuk dimasukan ke dalam matriks A. Pada soal ini kita menggunakan thread untuk perhitungan tiap sel nya.
```c
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
```

Tampilkan isi matriks B dan lakukan join thread.
```c
printf("Matrix B: \n");
for(int i=0; i<24; i++){
	if(i%6 == 0 && i != 0) printf("\n");
	printf("%d\t", matrixB[i]);
	pthread_join(tid[i],NULL);
}
printf("\n\n");
```

Tampilkan matriks hasil.
```c
printf("Matrix Hasil: \n");
for(int i=0; i<24; i++){
	if(i%6 == 0 && i != 0) printf("\n");
	printf("%lld\t", d[i].hasil);
}
```

#
### Jawab 2c
Pada soal ini kita diminta untuk mencari 5 proses teratas yang memakan resources komputer menggunakan command `ps aux | sort -nrk 3,3 | head -5`. Pertama kita membuat command yang menampilkan seluruh proses pada user lalu kita menggunakan pipe-fork untuk menjalankan program tersebut.
```c
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

child_id = fork();
if(child_id < 0) exit(0);
if(child_id == 0){
	dup2(fp1[1], STDOUT_FILENO);
	close(fp1[0]);
	char *argv[] = {"ps", "aux", NULL};
	execv("/bin/ps", argv);
}
```

Lalu setelah kita menampilkan seluruh proses user, lakukan pengurutkan menggunakan sort.
```c
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
```

Lalu setelah mengurutkan, kita menyeleksi menjadi 5 proses teratas yang paling banyak memakan resource pada komputer.
```c
while(wait(&status) > 0);
dup2(fp2[0], STDIN_FILENO);
close(fp2[1]);
char *argv[] = {"head", "-5", NULL};
execv("/usr/bin/head", argv);
return 0;
```

Pada soal ini kita menggunakan fungsi `fork` yang berguna untuk spawning process, lalu kita menggunakan `wait` untuk menunggu process sebelumnya menyelesaikan tugasnya terlebih dahulu, lalu `execv` digunakan untuk menjalankan suatu perintah dan menghentikan child yang sedang berjalan.

#
### Kendala
1. Sedikit bingung untuk shared memory pada array 2D lalu diakalin dengan array 1D.
2. Deskripsi pada soal 2b sedikit membingungkan, lalu kita mengasumsikan hasil dari soal 2a sebagai matriks A.
3. Salah saat melakukan pipes pada soal 2c hingga program tidak berhenti dan sekarang sudah diperbaiki.

#
## Penyelesaian Soal No.3
Seorang mahasiswa bernama Alex sedang mengalami masa gabut. Di saat masa gabutnya, ia memikirkan untuk merapikan sejumlah file yang ada di laptopnya. Karena jumlah filenya terlalu banyak, Alex meminta saran ke Ayub. Ayub menyarankan untuk membuat sebuah program C agar file-file dapat dikategorikan. Program ini akan memindahkan file sesuai ekstensinya ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.

Contoh apabila program dijalankan:
```txt
# Program soal3 terletak di /home/izone/soal3
$ ./soal3 -f path/to/file1.jpg path/to/file2.c path/to/file3.zip
#Hasilnya adalah sebagai berikut
/home/izone
      |-jpg
            |--file1.jpg
      |-c
            |--file2.c
      |-zip
            |--file3.zip
```

a. Program menerima opsi -f seperti contoh di atas, jadi pengguna bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang diinginkan oleh pengguna. Output yang dikeluarkan adalah seperti ini :
```txt
File 1 : Berhasil Dikategorikan (jika berhasil)
File 2 : Sad, gagal :( (jika gagal)
File 3 : Berhasil Dikategorikan
```

b. Program juga dapat menerima opsi -d untuk melakukan pengkategorian pada suatu directory. Namun pada opsi -d ini, user hanya bisa memasukkan input 1 directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin. Contohnya adalah seperti ini :
```txt
$ ./soal3 -d /path/to/directory/
```

Perintah di atas akan mengkategorikan file di /path/to/directory, lalu hasilnya akan disimpan di working directory dimana program C tersebut berjalan (hasil kategori filenya bukan di /path/to/directory). Output yang dikeluarkan adalah seperti ini :
```txt
Jika berhasil, print “Direktori sukses disimpan!”
Jika gagal, print “Yah, gagal disimpan :(“
```

c. Selain menerima opsi-opsi di atas, program ini menerima opsi \*, contohnya ada di bawah ini:
```txt
$ ./soal3 \*
```

Opsi ini akan mengkategorikan seluruh file yang ada di working directory ketika menjalankan program C tersebut.

d. Semua file harus berada di dalam folder, jika terdapat file yang tidak memiliki ekstensi, file disimpan dalam folder `Unknown`. Jika file hidden, masuk folder `Hidden`.

e. Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat.

Namun karena Ayub adalah orang yang hanya bisa memberi ide saja, tidak mau bantuin buat bikin programnya, Ayub meminta bantuanmu untuk membuatkan programnya. Bantulah agar program dapat berjalan!

Catatan: 
- Kategori folder tidak dibuat secara manual, harus melalui program C
- Program ini tidak case sensitive. Contoh: JPG dan jpg adalah sama
- Jika ekstensi lebih dari satu (contoh `.tar.gz`) maka akan masuk ke folder dengan titik terdepan (contoh `tar.gz`)
- Dilarang juga menggunakan fork-exec dan system()
- Bagian b dan c berlaku **rekursif**

#
### Jawab 3a
Pada soal ini kita diminta untuk mengkategorikan file dalam suatu folder sesuai dengan ekstensinya. Untuk soal nomor 3a ini program dapat menerima opsi `-f` yang artinya pengguna dapat menambahkan argumen file yang bisa dikategorikan sesuai dengan keinginan. Hal pertama yang dilakukan yakni mengecek kesesuaian argc dan argv yang ada.
```c
if(argc > 2 && strcmp(argv[1], "-f") == 0){
	...
}
```

Selanjutnya menginisialisasi thread dan variabel count yang digunakan untuk menghitung banyaknya file yang berhasil dikategorikan. Lalu kita membuat thread yang mengkategorikan file berdasarkan ekstensinya.
```c
pthread_t tid[argc-2];
int count = 0;
for(int i=2; i<argc; i++){
	if(access(argv[i], F_OK) == 0){
		pthread_create(&tid[count], NULL, categorize, (void *)argv[i]);
		count++;
		printf("File %d : Berhasil Dikategorikan\n", i-1);
	}
	else printf("File %d : Sad, gagal :(\n", i-1);
	...
}
```

Untuk fungsi `categorize` yaitu membuat pengkategorian file, dimulai dari pencarian ekstensi file, pembuatan folder, pencarian nama file, dan rename filepath.
```c
void* categorize(void *arg){
	char *src = (char *)arg;
	char srcP[150];
	memcpy(srcP, (char*)arg, 400);
	char *srcExt = checkExt(src);
	char ext[400];
	strcpy(ext, srcExt);
	
	DIR *dir = opendir(srcExt);
	if(dir) closedir(dir);
	else if(ENOENT == errno) mkdir(srcExt, 0755);
	
	char *srcName = checkName(srcP);
	char *curr = getenv("PWD");
	
	char destP[400];
	sprintf(destP, "%s/%s/%s", curr, ext, srcName);
	
	rename(srcP, destP);
}
```

Fungsi `checkName` untuk mengecek dan mendapatkan nama dari suatu file yang diinputkan.
```c
char *checkName(char *dir){
char *name = strrchr(dir, '/');
if(name == dir) return "";
return name + 1;
}
```

Dan yang terakhir di nomor 3a ini yaitu membuat thread join dari semua thread yang telah dibuat sebelumnya.
```c
	...
	for(int i=0; i<count; i++) pthread_join(tid[i], NULL);
	return 0;
```

#
### Jawab 3b
Untuk nomor 3b ini input yang diberikan berupa opsi `-d` yang artinya pengguna hanya bisa memasukkan input 1 directory saja. Hal pertama yang dilakukan pastinya mengecek kesesuaian argc dan argv yang ada. Lalu membuka direktori/folder yang diinputkan, jika folder tersebut ditemukan maka akan dicari berapa jumlah file yang ada didalamnya sehingga kita bisa menyesuaiakannya dengan thread yang akan dibuat. Selanjutnya membuat pengkategorian file dengan menggunakan thread dan menampilkan keterangan outputnya. 
```c
else if(argc == 3 && strcmp(argv[1], "-d") == 0){
	DIR *fd = opendir(argv[2]);
	if(fd){
		struct dirent *dp;
		int threadSize = 0;
		while((dp = readdir(fd)) != NULL){
			if(dp->d_type == DT_REG){
				threadSize++;
			}
		}
		categorizeFolder(argv[2], threadSize);
		closedir(fd);
		printf("Direktori sukses disimpan!\n");
	}
	else if(ENOENT == errno) printf("Yah, gagal disimpan :(\n");
}
```

Untuk fungsi `categorizeFolder` yaitu untuk membuat pengkategorian file berdasarkan ekstensinya yang dimulai dengan membuka direktori yang diinputkan lalu mengecek setiap file dalam direktori tersebut untuk nanti selanjutnya akan dibuat kategorisasinya. Jika didalam direktori tersebut ditemukan juga folder yang lain maka juga akan dibuat pengkategorian file didalam folder tersebut dengan langkah yang sama dengan sebelumnya dengan menggunakan prinsip rekursif.  
```c
void categorizeFolder(char *folderPath, int threadSize){
	DIR *fd = opendir(folderPath);
	struct dirent *dp;
	pthread_t tid[threadSize];
	int count = 0;
	char fileName[400][400];
	
	while((dp = readdir(fd)) != NULL){
		if(dp->d_type == DT_REG){
			sprintf(fileName[count], "%s/%s", folderPath, dp->d_name);
			pthread_create(&tid[count], NULL, categorize, (void *)fileName[count]);
			count++;
		}
		else if((dp->d_type == DT_DIR) && strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            char folderPath2[400];
            sprintf(folderPath2, "%s/%s", folderPath, dp->d_name);
            DIR *fd2 = opendir(folderPath2);
            struct dirent *dp2;
			int threadSize2 = 0;
			while((dp2 = readdir(fd2)) != NULL){
				if(dp2->d_type == DT_REG){
					threadSize2++;
				}
			}
			categorizeFolder(folderPath2, threadSize2);
			closedir(fd2);
        }
	}
	
	for(int i=0; i<threadSize; i++) pthread_join(tid[i], NULL);
    closedir(fd);
}
```

#
### Jawab 3c
Tidak berbeda jauh dengan 3b, dalam soal nomor 3c ini kita juga diminta untuk mengkategorikan file dalam suatu folder, perbedaannya terdapat dalam opsi input yang diberikan yakni `*` yang artinya akan mengkategorikan seluruh file yang ada di working directory ketika menjalankan program C tersebut. Untuk fungsi `categorizeFolder` sama seperti yang sudah dijelaskan sebelumnya.
```c
else if(argc == 2 && strcmp(argv[1], "*") == 0){
	char *curr = getenv("PWD");
	DIR *dir = opendir(curr);
	struct dirent *dp;
	int threadSize = 0;
	while((dp = readdir(dir)) != NULL){
		if(dp->d_type == DT_REG){
			threadSize++;
		}
	}
	categorizeFolder(curr, threadSize);
	closedir(dir);
}
```

#
### Jawab 3d
Untuk soal 3d ini semua file harus ada dalam satu folder sesuai ekstensinya dimana jika terdapat file yang tidak memiliki ekstensi akan disimpan dalam folder `Unknown` dan jika file hidden akan masuk folder `Hidden`. Hal ini telah diatur dalam suatu fungsi yakni `checkExt` yang berfungsi untuk mengecek ekstensi dari sebuah file dimana fungsi ini terdapat dalam fungsi `categorize` yang telah dijelaskan sebelumnya.
```c
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
```

Lalu juga ada fungsi `lowercase()` untuk mengubah nama ekstensinya menjadi huruf kecil.
```c
char *lowercase(char *str){
	unsigned char *temp = (unsigned char *)str;
	while(*temp){
		*temp = tolower(*temp);
		temp++;
	}
	return str;
}
```

#
### Jawab 3e
Soal 3e kita diminta untuk membuat setiap thread untuk setiap file yang akan dikategorikan agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat. Oleh karena itu, kami membuat thread sesuai dengan jumlah file yang akan dikategorikan lalu menjoinkan tiap thread yang dijalankan. Hal tersebut telah dibuat dalam program dan fungsi yang telah dijelaskan sebelumnya.

#
### Kendala
1. Sempat kebingungan dalam membuat dan menjalankan program dengan menggunakan prinsip rekursif.
2. Thread tidak berjalan sesuai keinginan dan dapat diselesaikan dengan menjoinkannya.
3. Sempat kesulitan dalam penentuan ekstensi file dikarenakan yang diminta soal sedikit berbeda dengan format ekstensi file pada umumnya.
