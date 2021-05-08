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
Jawab 1a

#
### Jawab 1b
Jawab 1b

#
### Jawab 1c
Jawab 1c

#
### Jawab 1d
Jawab 1d

#
### Jawab 1e
Jawab 1e

#
### Jawab 1f
Jawab 1f

#
### Jawab 1g
Jawab 1g

#
### Jawab 1h
Jawab 1h

#
### Kendala
Isi kendala

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
| A	| B |	Angka-Angka Faktorial |
|---|---|-----------------------|
| 4	| 4	| 4 3 2 1               |
| 4	| 5	| 4 3 2 1               |
| 4	| 3	| 4 3 2                 |
| 4	| 0	| 0                     |
| 0	| 4	| 0                     |
| 4	| 6	| 4 3 2 1               |

Contoh :
| Matriks A |	Matriks B	|        Matriks Hasil       |
|-----------|-----------|----------------------------|
|   0	  4   |   0  	4   | 0	              4\*3\*2\*1 |
|   4	  5   |   6	  2	  | 4\*3\*2\*1	    5\*4       |
|   5	  6   |   6  	0	  | 5\*4\*3\*2\*1   0          |

c. Karena takut lag dalam pengerjaannya membantu Loba, Crypto juga membuat program (soal2c.c) untuk mengecek 5 proses teratas apa saja yang memakan resource komputernya dengan command `ps aux | sort -nrk 3,3 | head -5` (**Catatan!:** Harus menggunakan IPC Pipes)

Note:
- Semua matriks berasal dari input ke program.
- Dilarang menggunakan system()

#
### Jawab 2a
Jawab 2a
pada soal 2a kita diminta untuk membuat matriks yang ber ordo 4x3 dan 3x6 yang berisikan angka 1-20 lalu kita mengkalikan kedua matriks tersebut menjadi matriks hasil :

```
matriks 4x3

int sum = 0;
	int first[4][3] = {
		{2, 1, 1},
		{1, 2, 0},
		{2, 0, 1},
		{0, 2, 0}
	};
```

```
matriks 3x6

int second[3][6] = {
		{1, 2, 0, 1, 2, 1},
		{1, 2, 2, 0, 2, 0},
		{0, 1, 0, 1, 0, 1}
	};
    
```
lalu kita membuat pengelompokkan dan mengurutkan pada baris dan kolom dan membuatnya menjadi bentuk matriks untuk memudahkan perkalian matriks :

```
printf("Matrix 4x3: \n");
	for(int i=0; i<4; i++){
		for(int j=0; j<3; j++){
			printf("%d\t", first[i][j]);
		}
		printf("\n");
        
        
	printf("Matrix 3x6: \n");
	for(int i=0; i<3; i++){
		for(int j=0; j<6; j++){
			printf("%d\t", second[i][j]);
		}
        
```
kita mengkalikan kedua matriks yang terbentuk menjadi satu matriks hasil :
```
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
pada matriks hasil kita menggunakan prinsip perkalian matriks untuk menentukan ordo dari matriks hasil yaitu ketika A X B dan B X C maka ordo tersebut akan menjadi A X C , pada soal ini kita mengalikan matriks yang ber ordo 4 X 3 dan 3 X 6 sehingga bentuk dari matriks hasil adalah 4 X 6 sehingga kita membuat fungsi untuk matriks hasil dengan 
```int multiply[4][6];``` dengan isi :
```
printf("Matrix Hasil: \n");
	for(int i=0; i<4; i++){
		for(int j=0; j<6; j++){
			value[6*i+j] = multiply[i][j];
			printf("%d\t",multiply[i][j]);
		}
		printf("\n");
	}
```
kita juga menambahkan untuk menggunakan shared memory karena matriks hasil akan digunakan pada soal berikutnya :
```
key_t key = 1234;
	int *value;
	int shmid = shmget(key, sizeof(int) * 24, IPC_CREAT | 0644);
	value = shmat(shmid, NULL, 0);
```



#
### Jawab 2b
Jawab 2b
pada soal ini kita diminta mengoperasikan kembali matriks a yang kita dapat pada soal 2a dengan soal b yang terdapat pada soal,untuk pengoperasiannya terdapat beberapa ketentuan dimana matrik A menjadi angka untuk faktorian lalu matriks b menjadi batas maksimal faktorialnya dengan ini kita mendapat rules 

jika a>=b  maka a!/(a-b)!
jika b > a maka a!
jika 0 maka output akan tetap 0

```
void *fact(void* arg){
	data* d = (data*) arg;
	if(d->angka1 == 0 || d->angka2 == 0) d->hasil = 0;
	else if(d->angka1 < d->angka2) d->hasil = faktorial(d->angka1);
	else d->hasil = faktorial(d->angka1) / faktorial(d->angka1 - d->angka2);
}
```

pertama kita membuat matriks b dan memanggil matriks hasil pada soal 2a menggunakan shared memory :
```
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
    
```
lalu kita memanggil matriks hasil pada soal 2a untuk dimasukan kedalam matrik a pada soal ini,kita menggunakan mutual exclusion sehingga code nya menjadi :
```
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
kita juga memanggil matriks b pada fungsi berikut :
```
printf("Matrix B: \n");
	for(int i=0; i<24; i++){
		if(i%6 == 0 && i != 0) printf("\n");
		printf("%d\t", matrixB[i]);
		pthread_join(tid[i],NULL);
	}
	printf("\n\n");
    
```
lalu kita mengkalikan kedua matriks yang sudah terpanggil menggunakan fungsi berikut :
```

printf("Matrix Hasil: \n");
	for(int i=0; i<24; i++){
		if(i%6 == 0 && i != 0) printf("\n");
		printf("%lld\t", d[i].hasil);
	}
    
```

 #
### Jawab 2c
Jawab 2c
pada soal ini kita diminta untuk mencari 5 proses teratas yang memakan resources komputer menggunakan command ```ps aux| sort -nrk 3,3|head -5``` pertama kita membuat command yang menampilkan seluruh proses pada user lalu kita menggunakan pipe-fork untuk menjalankan program tersebut
```
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
	
	child_id = fork();
	if(child_id < 0) exit(0);
	if(child_id == 0){
		dup2(fp1[1], STDOUT_FILENO);
		close(fp1[0]);
		char *argv[] = {"ps", "aux", NULL};
		execv("/bin/ps", argv);
	}
```

lalu setelah kita menampilkan seluruh proses user kita mengurutkan menggunakan sort :
```
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
```

lalu setelah mengurutkan kita menyeleksi menjadi 5 saja proses yang paling banyak memakan resource pada komputer
```
while(wait(&status) > 0);
	dup2(fp2[0], STDIN_FILENO);
	close(fp2[1]);
	char *argv[] = {"head", "-5", NULL};
	execv("/usr/bin/head", argv);
	return 0;
```
pada soal ini kita menggunakan fungsi ```fork``` yang berguna untuk spawning process,lalu kita menggunakan ```wait``` untuk menunggu process menyelesaikan tugasnya terlebih dahulu lalu ```exec``` digunakan untuk menjalankan program baru dan menggantikan program yang sedang berjalan.

#
### Kendala
Isi kendala

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
Jawab 3a

#
### Jawab 3b
Jawab 3b

#
### Jawab 3c
Jawab 3c

#
### Jawab 3d
Jawab 3d

#
### Jawab 3e
Jawab 3e

#
### Kendala
Isi kendala
