#include <stdbool.h>
#include "formula.h"
#include "inputValidation.h"
#include "todayDate.h"

struct dataUser{
    char namaLengkap[50];
    char username[40];
    char password[40];
    int saldo;
    int jenisPengeluaran[8]; 
    /* Keterangan Index
    [0] = Makanan, [1] = Transportasi, [2] = Hiburan, [3] = Kesehatan, [4] = Rumah Tangga
    [5] = Pendidikan, [6] = Pakaian, [7] = Lainnya 
    */
    int totalPengeluaran;
    int tglPengeluaran[32]; //Untuk Menyimpan Pengeluaran Setiap Tanggal!
};

//Fungsi Untuk Mencari Index dari Akun
int idxSearch(struct dataUser user[], char *username, char *password){
    for(int i = 0; i < checkLines("database/account.txt")/45; i++){
        if(strcmp(user[i].username, username) == 0 && strcmp(user[i].password, password) == 0){
            return i; //akun ditemukan
        }
    }
    return -1; //akun tidak ditemukan
}

//Fungsi Untuk Mendaftar Akun
void registerAcc(struct dataUser user[], int totalUser)
{
    system("clear");
    fflush(stdin);
    //Setup Variabel dan File
    FILE *fptr;
    fptr = fopen("database/account.txt", "a");
    char namaLengkap[50];
    char username[40];
    char pw[38] = {0};
    char *p = pw;
    FILE *fp = stdin;
    ssize_t nchr = 0;
    //Input Nama Lengkap
    while(true){
        system("clear");
        fflush(stdin);
        printf("|| ================================================== ||\n");
        printf("||                    Pendaftaran Akun                ||\n");
        printf("|| ================================================== ||\n");
        printf("|| Nama Lengkap : ");
        scanf("%[^\n]", namaLengkap);
        getchar();
        //Validasi Nama Lengkap
        int nameCheck = 0;
        for(int i = 0; i < strlen(namaLengkap); i++){
            if(isalpha(namaLengkap[i]) == 0 && namaLengkap[i] != ' '){
                nameCheck = -1;
            }
        }
        if(nameCheck == 0){
            break;
        }else{
            system("clear");
            printf("|| ================================================== ||\n");
            printf("||                    Pendaftaran Akun                ||\n");
            printf("|| ================================================== ||\n");
            printf("|| Nama Lengkap : Nama Lengkap Tidak Valid!\n");
            system("read -n 1 -s -p ''");
            continue;
        }
    }

    //Input Username
    while(true){
        system("clear");
        fflush(stdin);
        printf("|| ================================================== ||\n");
        printf("||                    Pendaftaran Akun                ||\n");
        printf("|| ================================================== ||\n");
        printf("|| Nama Lengkap : %s\n", namaLengkap);
        printf("|| Username : ");
        scanf("%[^\n]", username);
        getchar();
        //Validasi Username
        int usernameCheck = 0;
        for(int i = 0; i < checkLines("database/account.txt")/45; i++){
            if(strcmp(user[i].username, username) == 0){
                usernameCheck = -1;
            }
        }
        for(int i = 0; i < strlen(username); i++){
            if(username[i] == ' '){
                usernameCheck = -1;
            }
        }
        if(usernameCheck == 0){
            break;
        }else{
            system("clear");
            printf("|| ================================================== ||\n");
            printf("||                    Pendaftaran Akun                ||\n");
            printf("|| ================================================== ||\n");
            printf("|| Nama Lengkap : %s\n", namaLengkap);
            printf("|| Username : Username Tidak Valid!\n");
            system("read -n 1 -s -p ''");
            continue;
        }
    }

    //Input Password
    fflush(stdin);
    printf("|| Password : ");
    nchr = getpasswd (&p, 38, '*', fp);
    getchar();

    //Menginput data ke dalam file
    fputs(namaLengkap, fptr);
    fputs("\n", fptr);
    fputs(username, fptr);
    fputs("\n", fptr);
    fputs(pw, fptr);
    fputs("\n", fptr);
    for (int i = 0; i < 10; i++){
        fputs("0", fptr);
        fputs("\n", fptr);
    }
    for(int i = 0; i < 32; i++){
        fputs("0", fptr);
        fputs("\n", fptr);
    }
    fclose(fptr);
    printf("|| ================================================== ||\n");
    printf("||                Akun anda sudah siap!               ||\n");
    printf("||        Tekan Enter untuk keluar dari program       ||\n");
    printf("|| ================================================== ||\n");
    system("read -n 1 -s -p ''");
    exit(0);
}

//Fungsi Untuk Membaca Data dari File 
void readFile(struct dataUser user[], int totalUser){
    FILE *fptr;
    fptr = fopen("database/account.txt", "r");
    //WARNING : HATI - HATI KALO MAU DIRUBAH!
    //KODE DIBAWAH SUDAH SESUAI JIKA ACCOUNT.TXT TIDAK TERJADI PERUBAHAN STRUKTUR
    for (int i = 0; i < totalUser; i++){
        char digitUang[10];
        fscanf(fptr, "%[^\n]%*c", user[i].namaLengkap);
        fscanf(fptr, "%[^\n]%*c", user[i].username);
        fscanf(fptr, "%[^\n]%*c", user[i].password);
        fscanf(fptr, "%[^\n]%*c", digitUang);
        user[i].saldo = atoi(digitUang);
        for (int j = 0; j < 8; j++)
        {
            fscanf(fptr, "%[^\n]%*c", digitUang);
            user[i].jenisPengeluaran[j] = atoi(digitUang);
        }
        fscanf(fptr, "%[^\n]%*c", digitUang);
        user[i].totalPengeluaran = atoi(digitUang);
        for(int j = 0; j < 32; j++){
            fscanf(fptr, "%[^\n]%*c", digitUang);
            user[i].tglPengeluaran[j] = atoi(digitUang);
        }
    }
    fclose(fptr);
}

//Fungsi Untuk Menulis Kembali File Setelah Terjadi Perubahan
void writeFile(struct dataUser user[], int totalUser){
    FILE *fptr;
    fptr = fopen("database/account.txt", "w");
    char angka[10];
    //WARNING : HATI - HATI KALO MAU DIRUBAH!!! KARENA AKAN BERDAMPAK KE ACCOUNT.TXT
    //STRUKTUR FILE ACCOUNT.TXT : TIAP DATA DIPISAH OLEH BARIS
    for (int i = 0; i < totalUser; i++){
        fputs(user[i].namaLengkap, fptr);
        fputs("\n", fptr);
        fputs(user[i].username, fptr);
        fputs("\n", fptr);
        fputs(user[i].password, fptr);
        fputs("\n", fptr);
        sprintf(angka, "%d", user[i].saldo);
        fputs(angka, fptr);
        fputs("\n", fptr);
        for(int j = 0; j < 8; j++){
            sprintf(angka, "%d", user[i].jenisPengeluaran[j]);
            fputs(angka, fptr);
            fputs("\n", fptr);
        }
        sprintf(angka, "%d", user[i].totalPengeluaran);
        fputs(angka, fptr);
        fputs("\n", fptr);
        for(int j = 0; j < 32; j++){
            char nomorString[15];
            sprintf(nomorString, "%d", user[i].tglPengeluaran[j]);
            fputs(nomorString, fptr);
            fputs("\n", fptr);
        }
    }
    fclose(fptr);
}

//Fungsi Penambahan Pengeluaran
void tmbBiaya(struct dataUser user[], int idxLogin, int option, int totalUser){
    fflush(stdin);
    int cost;
    printf("|| ================================================== ||\n");
    printf("||                Biaya Yang Anda Keluarkan           ||\n");
    printf("|| ================================================== ||\n");
    //Input Nominal Pengeluaran
    //Nominal Pengeluaran akan Dimasukkan Sesuai Index Jenis Pengeluaran
    reVldInt(&cost, "|| Input Anda : Rp.");
    if(option == 1){
        //Deklarasi variabel
        FILE *fileMakanan = fopen("database/daftarMkn.txt", "a");
        char namaMakanan[100], harga[15], tanggal[3], idxAkun[4];
        sprintf(idxAkun, "%d", idxLogin);
        sprintf(harga, "%d", cost);
        sprintf(tanggal, "%d", tglHariIni());

        //Program Input Output
        user[idxLogin].jenisPengeluaran[0] += cost;
        printf("|| Nama Makanan : ");
        scanf("%[^\n]", namaMakanan);
        getchar();

        //Menulis ke Dalam File
        fputs(idxAkun, fileMakanan);
        fputs("\n", fileMakanan);
        fputs(tanggal, fileMakanan);
        fputs("\n", fileMakanan);
        fputs(namaMakanan, fileMakanan);
        fputs("\n", fileMakanan);
        fputs(harga, fileMakanan);
        fputs("\n", fileMakanan);
        fclose(fileMakanan);
    }else if(option == 2){
        //Deklarasi Variabel
        FILE *fileTransport = fopen("database/daftarTransport.txt", "a");
        char deskripsi[100], harga[15], tanggal[3], idxAkun[4];
        sprintf(idxAkun, "%d", idxLogin);
        sprintf(harga, "%d", cost);
        sprintf(tanggal, "%d", tglHariIni());

        //Program Input Output
        user[idxLogin].jenisPengeluaran[1] += cost;
        printf("|| Nama Kebutuhan : ");
        scanf("%[^\n]", deskripsi);
        getchar();

        //Menulis ke Dalam File
        fputs(idxAkun, fileTransport);
        fputs("\n", fileTransport);
        fputs(tanggal, fileTransport);
        fputs("\n", fileTransport);
        fputs(deskripsi, fileTransport);
        fputs("\n", fileTransport);
        fputs(harga, fileTransport);
        fputs("\n", fileTransport);
        fclose(fileTransport);
    }else if(option == 3){
        //Deklrasi Variabel
        FILE *fileHiburan = fopen("database/daftarHiburan.txt", "a");
        char deskripsi[100], harga[15], tanggal[3], idxAkun[4];
        sprintf(idxAkun, "%d", idxLogin);
        sprintf(harga, "%d", cost);
        sprintf(tanggal, "%d", tglHariIni());

        //Program Input Output
        user[idxLogin].jenisPengeluaran[2] += cost;
        printf("|| Nama Hiburan : ");
        scanf("%[^\n]", deskripsi);
        getchar();

        //Menulis ke Dalam File
        fputs(idxAkun, fileHiburan);
        fputs("\n", fileHiburan);
        fputs(tanggal, fileHiburan);
        fputs("\n", fileHiburan);
        fputs(deskripsi, fileHiburan);
        fputs("\n", fileHiburan);
        fputs(harga, fileHiburan);
        fputs("\n", fileHiburan);
        fclose(fileHiburan);

    }else if(option == 4){
        //Deklarasi Variabel
        FILE *fileKesehatan = fopen("database/daftarKesehatan.txt", "a");
        char deskripsi[100], harga[15], tanggal[3], idxAkun[4];
        sprintf(idxAkun, "%d", idxLogin);
        sprintf(harga, "%d", cost);
        sprintf(tanggal, "%d", tglHariIni());

        //Program Input Output
        user[idxLogin].jenisPengeluaran[3] += cost;
        printf("|| Deskripsi : ");
        scanf("%[^\n]", deskripsi);
        getchar();

        //Menulis ke Dalam File
        fputs(idxAkun, fileKesehatan);
        fputs("\n", fileKesehatan);
        fputs(tanggal, fileKesehatan);
        fputs("\n", fileKesehatan);
        fputs(deskripsi, fileKesehatan);
        fputs("\n", fileKesehatan);
        fputs(harga, fileKesehatan);
        fputs("\n", fileKesehatan);
        fclose(fileKesehatan);
    }else if(option == 5){
        //Deklarasi Variabel
        FILE *fileRT = fopen("database/daftarRumahTangga.txt", "a");
        char deskripsi[100], harga[15], tanggal[3], idxAkun[4];
        sprintf(idxAkun, "%d", idxLogin);
        sprintf(harga, "%d", cost);
        sprintf(tanggal, "%d", tglHariIni());

        //Program Input Output
        user[idxLogin].jenisPengeluaran[4] += cost;
        printf("|| Deskripsi : ");
        scanf("%[^\n]", deskripsi);
        getchar();

        //Menulis ke Dalam File
        fputs(idxAkun, fileRT);
        fputs("\n", fileRT);
        fputs(tanggal, fileRT);
        fputs("\n", fileRT);
        fputs(deskripsi, fileRT);
        fputs("\n", fileRT);
        fputs(harga, fileRT);
        fputs("\n", fileRT);
        fclose(fileRT);
    }else if(option == 6){
        //Deklarasi Variabel
        FILE *filePendidikan = fopen("database/daftarPendidikan.txt", "a");
        char deskripsi[100], harga[15], tanggal[3], idxAkun[4];
        sprintf(idxAkun, "%d", idxLogin);
        sprintf(harga, "%d", cost);
        sprintf(tanggal, "%d", tglHariIni());

        //Program Input Output
        user[idxLogin].jenisPengeluaran[5] += cost;
        printf("|| Deskripsi : ");
        scanf("%[^\n]", deskripsi);
        getchar();

        //Menulis ke Dalam File
        fputs(idxAkun, filePendidikan);
        fputs("\n", filePendidikan);
        fputs(tanggal, filePendidikan);
        fputs("\n", filePendidikan);
        fputs(deskripsi, filePendidikan);
        fputs("\n", filePendidikan);
        fputs(harga, filePendidikan);
        fputs("\n", filePendidikan);
        fclose(filePendidikan);

    }else if(option == 7){
        //Deklarasi Variabel
        FILE *filePakaian = fopen("database/daftarPakaian.txt", "a");
        char deskripsi[100], harga[15], tanggal[3], idxAkun[4];
        sprintf(idxAkun, "%d", idxLogin);
        sprintf(harga, "%d", cost);
        sprintf(tanggal, "%d", tglHariIni());

        //Program Input Output
        user[idxLogin].jenisPengeluaran[6] += cost;
        printf("|| Deskripsi : ");
        scanf("%[^\n]", deskripsi);
        getchar();

        //Menulis ke Dalam File
        fputs(idxAkun, filePakaian);
        fputs("\n", filePakaian);
        fputs(tanggal, filePakaian);
        fputs("\n", filePakaian);
        fputs(deskripsi, filePakaian);
        fputs("\n", filePakaian);
        fputs(harga, filePakaian);
        fputs("\n", filePakaian);
        fclose(filePakaian);

    }else if(option == 8){
        //Deklarasi Variabel
        FILE *fileLainnya = fopen("database/daftarLainnya.txt", "a");
        char deskripsi[100], harga[15], tanggal[3], idxAkun[4];
        sprintf(idxAkun, "%d", idxLogin);
        sprintf(harga, "%d", cost);
        sprintf(tanggal, "%d", tglHariIni());

        //Program Input Output
        user[idxLogin].jenisPengeluaran[7] += cost;
        printf("|| Deskripsi : ");
        scanf("%[^\n]", deskripsi);
        getchar();

        //Menulis ke Dalam File
        fputs(idxAkun, fileLainnya);
        fputs("\n", fileLainnya);
        fputs(tanggal, fileLainnya);
        fputs("\n", fileLainnya);
        fputs(deskripsi, fileLainnya);
        fputs("\n", fileLainnya);
        fputs(harga, fileLainnya);
        fputs("\n", fileLainnya);
        fclose(fileLainnya);
    }
    //Melakukan Pembaruan Terhadap Tgl Pengeluaran, Saldo Tersisa, dan Total Pengeluaran
    user[idxLogin].tglPengeluaran[tglHariIni() - 1] += cost;
    user[idxLogin].saldo -= cost;
    user[idxLogin].totalPengeluaran = 0;
    for(int i = 0; i < 8; i++){
        user[idxLogin].totalPengeluaran += user[idxLogin].jenisPengeluaran[i];
    }
    writeFile(user, totalUser);
    printf("|| ================================================== ||\n");
    printf("||               Pembaruan Telah Dicatat              ||\n");
    printf("||            Tekan Enter untuk Melanjutkan           ||\n");
    printf("|| ================================================== ||\n");
    system("read -n 1 -s -p ''");
}

//Fungsi Untuk Menambah Pemasukan
void pemasukan(struct dataUser user[], int idxLogin, int totalUser){
    system("clear");
    fflush(stdin);
    //Setup Variabel
    int pemasukan;
    printf("|| ================================================== ||\n");
    printf("||                Pemasukan Anda Hari Ini             ||\n");
    printf("||                   %d %s %d                 ||\n", tglHariIni(), bulanString(), thnHariIni());
    printf("|| ================================================== ||\n");
    //Input Pemasukan
    reVldInt(&pemasukan, "|| Pemasukan : Rp.");
    fflush(stdin);
    user[idxLogin].saldo += pemasukan;
    writeFile(user, totalUser);
    printf("|| ================================================== ||\n");
    printf("||               Pembaruan Telah Dicatat              ||\n");
    printf("||            Tekan Enter untuk Melanjutkan           ||\n");
    printf("|| ================================================== ||\n");
    system("read -n 1 -s -p ''");
    
}

//Fungsi Menu Pengeluaran
void pengeluaran(struct dataUser user[], int idxLogin, int totalUser){
    system("clear");
    fflush(stdin);
    int option;
    printf("|| ================================================== ||\n");
    printf("||             Pilih Jenis Pengeluaran Anda           ||\n");
    printf("|| ================================================== ||\n");
    printf("||    No  |                   Option                  ||\n");
    printf("|| ================================================== ||\n");
    printf("||   [1]  | Makanan atau Minuman                      ||\n");
    printf("||   [2]  | Transportasi                              ||\n");
    printf("||   [3]  | Hiburan atau Rekreasi                     ||\n");
    printf("||   [4]  | Biaya Kesehatan                           ||\n");
    printf("||   [5]  | Biaya Rumah Tangga                        ||\n");
    printf("||   [6]  | Biaya Pendidikan                          ||\n");
    printf("||   [7]  | Pakaian                                   ||\n");
    printf("||   [8]  | Lainnya                                   ||\n");
    printf("|| ================================================== ||\n");
    reVldInt(&option, "|| Input Anda [] : ");
    system("clear");
    switch(option){
        case 1 :
            tmbBiaya(user, idxLogin, 1, totalUser);
            break;
        case 2 :
            tmbBiaya(user, idxLogin, 2, totalUser);
            break;
        case 3 :
            tmbBiaya(user, idxLogin, 3, totalUser);
            break;
        case 4 :
            tmbBiaya(user, idxLogin, 4, totalUser);
            break;
        case 5 : 
            tmbBiaya(user, idxLogin, 5, totalUser);
            break;
        case 6 :
            tmbBiaya(user, idxLogin, 6, totalUser);
            break;
        case 7 :
            tmbBiaya(user, idxLogin, 7, totalUser);
            break;
        case 8 :
            tmbBiaya(user, idxLogin, 8, totalUser);
            break;
        default :
            pengeluaran(user, idxLogin, totalUser);
            break;
    }
}


void readHarian(struct dataUser user[], int tanggal, int idxLogin){
    system("clear");
    printf("|| ================================================== ||\n");
    printf("||                   Rekapan Pengeluaran              ||\n");
    printf("||                       %d %s                  ||\n", tanggal, bulanString());
    printf("|| ================================================== ||\n");
    char deskripsi[30], inputAngka[15], idxAkun[3];
    int harga, tglFile, indexLogin;
    FILE * fptr;

    int simpanIdxLogin = idxLogin;
    //Membuka File Biaya Makanan
    //Menghasilkan Output 
    fptr = fopen("database/daftarMkn.txt", "r");
    for(size_t i = 0; i < checkLines("database/daftarMkn.txt")/4; i++){
        fscanf(fptr, "%[^\n]%*c", idxAkun);
        indexLogin = atoi(idxAkun);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        tglFile = atoi(inputAngka);
        fscanf(fptr, "%[^\n]%*c", deskripsi);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        harga = atoi(inputAngka);
        if((tglFile != tanggal) || (indexLogin != idxLogin)){
            continue;
        }else{
            printf("|| %s : Rp.%d\n", deskripsi, harga);
        }
    }
    fclose(fptr);

    //Membuka File Biaya Transport
    //Menghasilkan Output
    fptr = fopen("database/daftarTransport.txt", "r");
    for(size_t i = 0; i < checkLines("database/daftarTransport.txt")/4; i++){
        fscanf(fptr, "%[^\n]%*c", idxAkun);
        indexLogin = atoi(idxAkun);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        tglFile = atoi(inputAngka);
        if(tglFile != tanggal || indexLogin != idxLogin){
            continue;
        }
        fscanf(fptr, "%[^\n]%*c", deskripsi);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        harga = atoi(inputAngka);
        printf("|| %s : Rp.%d\n", deskripsi, harga);
    }
    fclose(fptr);

    //Membuka File Hiburan & Rekreasi
    //Menghasilkan Output
    fptr = fopen("database/daftarHiburan.txt", "r");
    for(size_t i = 0; i < checkLines("database/daftarHiburan.txt")/4; i++){
        fscanf(fptr, "%[^\n]%*c", idxAkun);
        indexLogin = atoi(idxAkun);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        tglFile = atoi(inputAngka);
        if(tglFile != tanggal || indexLogin != idxLogin){
            continue;
        }
        fscanf(fptr, "%[^\n]%*c", deskripsi);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        harga = atoi(inputAngka);
        printf("|| %s : Rp.%d\n", deskripsi, harga);
    }
    fclose(fptr);

    //Membuka File Biaya Kesehatan
    //Menghasilkan Output
    fptr = fopen("database/daftarKesehatan.txt", "r");
    for(size_t i = 0; i < checkLines("database/daftarKesehatan.txt")/4; i++){
        fscanf(fptr, "%[^\n]%*c", idxAkun);
        indexLogin = atoi(idxAkun);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        tglFile = atoi(inputAngka);
        if(tglFile != tanggal || indexLogin != idxLogin){
            continue;
        }
        fscanf(fptr, "%[^\n]%*c", deskripsi);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        harga = atoi(inputAngka);
        printf("|| %s : Rp.%d\n", deskripsi, harga);
    }
    fclose(fptr);

    //Membuka File Rumah Tangga
    //Menghasilkan Output
    fptr = fopen("database/daftarRumahTangga.txt", "r");
    for(size_t i = 0; i < checkLines("database/daftarRumahTangga.txt")/4; i++){
        fscanf(fptr, "%[^\n]%*c", idxAkun);
        indexLogin = atoi(idxAkun);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        tglFile = atoi(inputAngka);
        if(tglFile != tanggal || indexLogin != idxLogin){
            continue;
        }
        fscanf(fptr, "%[^\n]%*c", deskripsi);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        harga = atoi(inputAngka);
        printf("|| %s : Rp.%d\n", deskripsi, harga);
    }
    fclose(fptr);

    //Membuka File Biaya Pendidikan
    //Menghasilkan Output
    fptr = fopen("database/daftarPendidikan.txt", "r");
    for(size_t i = 0; i < checkLines("database/daftarPendidikan.txt")/4; i++){
        fscanf(fptr, "%[^\n]%*c", idxAkun);
        indexLogin = atoi(idxAkun);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        tglFile = atoi(inputAngka);
        if(tglFile != tanggal || indexLogin != idxLogin){
            continue;
        }
        fscanf(fptr, "%[^\n]%*c", deskripsi);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        harga = atoi(inputAngka);
        printf("|| %s : Rp.%d\n", deskripsi, harga);
    }
    fclose(fptr);

    //Membuka File Pakaian
    //Menghasilkan Output
    fptr = fopen("database/daftarPakaian.txt", "r");
    for(size_t i = 0; i < checkLines("database/daftarPakaian.txt")/4; i++){
        fscanf(fptr, "%[^\n]%*c", idxAkun);
        indexLogin = atoi(idxAkun);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        tglFile = atoi(inputAngka);
        if(tglFile != tanggal || indexLogin != idxLogin){
            continue;
        }
        fscanf(fptr, "%[^\n]%*c", deskripsi);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        harga = atoi(inputAngka);
        printf("|| %s : Rp.%d\n", deskripsi, harga);
    }
    fclose(fptr);

    //Membuka File Lainnya
    //Menghasilkan Output
    fptr = fopen("database/daftarLainnya.txt", "r");
    for(size_t i = 0; i < checkLines("database/daftarLainnya.txt")/4; i++){
        fscanf(fptr, "%[^\n]%*c", idxAkun);
        indexLogin = atoi(idxAkun);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        tglFile = atoi(inputAngka);
        if(tglFile != tanggal || indexLogin != idxLogin){
            continue;
        }
        fscanf(fptr, "%[^\n]%*c", deskripsi);
        fscanf(fptr, "%[^\n]%*c", inputAngka);
        harga = atoi(inputAngka);
        printf("|| %s : Rp.%d\n", deskripsi, harga);
    }
    fclose(fptr);
    printf("|| -------------------------------------------------- ||\n");
    printf("|| Total : Rp.%d\n", user[simpanIdxLogin].tglPengeluaran[tanggal-1]);
    printf("|| ================================================== ||\n");

}

void dailyMonthRecap(struct dataUser user[], int idxLogin){
    //Menampilkan Riwayat Pengeluaran User Berdasarkan Tanggal
    //Catatan : Hanya Ditampilkan Jika Pada Tanggal Tersebut, Pengeluaran > 0
    printf("|| ================================================== ||\n");
    printf("||                Riwayat Pengeluaran                 ||\n");
    printf("|| ================================================== ||\n");
    printf("||         Tanggal        ||       Pengeluaran        ||\n");
    printf("|| ================================================== ||\n");
    for(int i = 0; i < 32; i++){
        if(user[idxLogin].tglPengeluaran[i] > 0){
            //If Else disini hanya digunakan untuk merapikan tabel
            if(i < 10){
                printf("|| %d %s             || Rp.%d                 ||\n", i+1, bulanString(), user[idxLogin].tglPengeluaran[i]);
            }else{
                printf("|| %d %s            || Rp.%d                 ||\n", i+1, bulanString(), user[idxLogin].tglPengeluaran[i]);
            }
        }
    }
    printf("|| ================================================== ||\n");
    printf("||          Total         || Rp.%d                 ||\n", user[idxLogin]. totalPengeluaran);
    printf("|| ================================================== ||\n");
    int option;
    reVldInt(&option, "|| Tanggal Yang Mau Ditinjau : ");
    //Memanggil Fungsi Harian
    readHarian(user, option, idxLogin);
}

void categoryRecap(struct dataUser user[], int idxLogin, int pilihan){
    system("clear");
    //Menentukan Database Yang Akan Diakses Sesuai Pilihan User
    char fileDirectory[100];
    switch(pilihan){
        case 1 :
            strcpy(fileDirectory, "database/daftarMkn.txt");
            printf("|| ================================================== ||\n");
            printf("||              Pengeluaran Kategori Makanan          ||\n");
            break;
        case 2 :
            strcpy(fileDirectory, "database/daftarTransportasi.txt");
            printf("|| ================================================== ||\n");
            printf("||           Pengeluaran Kategori Transportasi        ||\n");
            break;
        case 3 :
            strcpy(fileDirectory, "database/daftarHiburan.txt");
            printf("|| ================================================== ||\n");
            printf("||              Pengeluaran Kategori Hiburan          ||\n");
            break;
        case 4 :
            strcpy(fileDirectory, "database/daftarKesehatan.txt");
            printf("|| ================================================== ||\n");
            printf("||            Pengeluaran Kategori Kesehatan          ||\n");
            break;
        case 5 :
            strcpy(fileDirectory, "database/daftarRumahTangga.txt");
            printf("|| ================================================== ||\n");
            printf("||           Pengeluaran Kategori Rumah Tangga        ||\n");
            break;
        case 6 :
            strcpy(fileDirectory, "database/daftarPendidikan.txt");
            printf("|| ================================================== ||\n");
            printf("||            Pengeluaran Kategori Pendidikan         ||\n");
            break;
        case 7 :
            strcpy(fileDirectory, "database/daftarPakaian.txt");   
            printf("|| ================================================== ||\n");
            printf("||            Pengeluaran Kategori Pakaian          ||\n"); 
            break;
        case 8 :
            strcpy(fileDirectory, "database/daftarLainnya.txt");
            printf("|| ================================================== ||\n");
            printf("||             Pengeluaran Kategori Lainnya           ||\n");
            break;
    }
    printf("||                      %s %d                 ||\n", bulanString(), thnHariIni());
    printf("|| ================================================== ||\n");

    //Membaca Isi File Database dan
    //Menampilkan Output
    FILE *fptr = fopen(fileDirectory, "r");
    char inputString[50], deskripsi[50];
    int idxLoginFile, tglFile, harga;

    for(int i = 0; i < checkLines(fileDirectory)/4; i++){
        //Membaca File
        fscanf(fptr, "%[^\n]%*c", inputString);
        idxLoginFile = atoi(inputString);
        fscanf(fptr, "%[^\n]%*c", inputString);
        tglFile = atoi(inputString);
        fscanf(fptr, "%[^\n]%*c", deskripsi);
        fscanf(fptr, "%[^\n]%*c", inputString);
        harga = atoi(inputString);

        //Mengeluarkan Output
        if(idxLoginFile == idxLogin){
            printf("   %d Desember | Pengeluaran : %d\n", tglFile, harga);
            printf("               | Deskripsi : %s\n", deskripsi);
            printf("   --------------------------------------------------\n");
        }
    }
    printf("|| ================================================== ||\n");
    printf("||                 Total : Rp.%d\n", user[idxLogin].jenisPengeluaran[pilihan - 1]);
    printf("|| ================================================== ||\n");
}

//Fungsi Menu Rekapan Kategori
void dailyRecap(struct dataUser user[], int idxLogin){
    int pilihan;
    printf("|| ================================================== ||\n");
    printf("||                    Pilih Kategori                  ||\n");
    printf("||                     Pengeluaran                    ||\n");
    printf("|| ================================================== ||\n");
    printf("|| [1] Makanan dan Minuman                            ||\n");
    printf("|| [2] Transportasi                                   ||\n");
    printf("|| [3] Hiburan dan Rekreasi                           ||\n");
    printf("|| [4] Biaya Kesehatan                                ||\n");
    printf("|| [5] Biaya Rumah Tangga                             ||\n");
    printf("|| [6] Biaya Pendidikan                               ||\n");
    printf("|| [7] Pakaian                                        ||\n");
    printf("|| [8] Lainnya                                        ||\n");
    printf("|| ================================================== ||\n");
    reVldInt(&pilihan, "|| Input Anda : ");
    categoryRecap(user, idxLogin, pilihan);
}

//Fungsi Rekapan Bulanan
void monthRecap(struct dataUser user[], int idxLogin){
    fflush(stdin);
    system("clear");
    //Setup Variabel (Digunakan untuk men-sorting pengeluaran, sehingga pengeluaran yang terbanyak ditampilkan terlebih dahulu)
    //Catatan : Hanya Menampilkan Jika Pengeluaran > 0
    int penandaCtg[] = {0, 1, 2, 3, 4, 5, 6, 7};
    bubbleSort(user[idxLogin].jenisPengeluaran, penandaCtg);
    printf("|| ==================================================================================================== ||\n");
    printf("||                                             Rekap Pengeluaran                                        ||\n");
    printf("||                                               %s %d                                          ||\n", bulanString(), thnHariIni());
    printf("|| ==================================================================================================== ||\n");
    printf("||                                                                                                      ||\n");
    printf("||                                      Total Pengeluaran : Rp.%d                                   ||\n", user[idxLogin].totalPengeluaran);
    printf("||                                                                                                      ||\n");
    printf("|| ==================================================================================================== ||\n");
    printf("||                Persentase Pengeluaran              ||                Rincian Pengeluaran             ||\n");
    printf("|| ==================================================================================================== ||\n");
    for(int i = 0; i < 8; i++){
        if(user[idxLogin].jenisPengeluaran[i] > 0){
            if(penandaCtg[i] == 0){
                printf("|| Makanan & Minuman     %.1f%c                        || Makanan & Minuman  : Rp.%d                 ||\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%', user[idxLogin].jenisPengeluaran[i]);
            }else if(penandaCtg[i] == 1){
                printf("|| Transportasi          %.1f%c                        || Transportasi       : Rp.%d                 ||\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%', user[idxLogin].jenisPengeluaran[i]);
            }else if(penandaCtg[i] == 2){
                printf("|| Hiburan & Rekreasi    %.1f%c                        || Hiburan & Rekreasi : Rp.%d                 ||\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%', user[idxLogin].jenisPengeluaran[i]);
            }else if(penandaCtg[i] == 3){
                printf("|| Biaya Kesehatan       %.1f%c                        || Biaya Kesehatan    : Rp.%d                 ||\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%', user[idxLogin].jenisPengeluaran[i]);
            }else if(penandaCtg[i] == 4){
                printf("|| Biaya Rumah Tangga    %.1f%c                        || Rumah Tangga       : Rp.%d                 ||\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%', user[idxLogin].jenisPengeluaran[i]);
            }else if(penandaCtg[i] == 5){
                printf("|| Biaya Pendidikan      %.1f%c                        || Biaya Pendidikan   : Rp.%d                 ||\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%', user[idxLogin].jenisPengeluaran[i]);
            }else if(penandaCtg[i] == 6){
                printf("|| Pakaian               %.1f%c                        || Pakaian            : Rp.%d                 ||\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%', user[idxLogin].jenisPengeluaran[i]);
            }else if(penandaCtg[i] == 7){
                printf("|| Lainnya               %.1f%c                        || Lainnya            : Rp.%d                 ||\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%', user[idxLogin].jenisPengeluaran[i]);
            }
        }else{
            continue;
        }
    }
    printf("||                                                    ||                                                ||\n");
    printf("|| ==================================================================================================== ||\n");
    printf("||                                                                                                      ||\n");
    printf("||                                          Sisa Saldo : Rp.%d                                     ||\n", user[idxLogin].saldo);
    printf("||                                                                                                      ||\n");
    printf("|| ==================================================================================================== ||\n");
    system("read -n 1 -s -p ''");

    //Menu Pilihan Setelah Menampilkan
    //Rekapan Bulanan
    int action;
    printf("|| ================================================== ||\n");
    printf("||    No  |                   Option                  ||\n");
    printf("|| ================================================== ||\n");
    printf("||   [1]  | Riwayat Pengeluaran per Hari              ||\n");
    printf("||   [2]  | Lihat Pengeluaran Berdasarkan Kategori    ||\n");
    printf("||   [3]  | Kembali ke Menu                           ||\n");
    printf("||   [4]  | Keluar Program                            ||\n");
    printf("|| ================================================== ||\n");
    reVldInt(&action, "|| Input Anda [] : ");
    system("clear");
    switch(action){
        case 1 :
            //Memanggil Fungsi Pengeluaran per Hari
            dailyMonthRecap(user, idxLogin);
            system("read -n 1 -s -p ''");
            fflush(stdin);

            //Menu Pilihan Setelah Menampilkan Fungsi Pengeluaran Per Hari
            printf("|| ================================================== ||\n");
            printf("||    No  |                   Action                  ||\n");
            printf("|| ================================================== ||\n");
            printf("||   [1]  | Kembali ke Rekapan Bulanan                ||\n");
            printf("||   [2]  | Kembali ke Menu                           ||\n");
            printf("||   [3]  | Keluar Program                            ||\n");
            printf("|| ================================================== ||\n");
            reVldInt(&action, "|| Input Anda [] : ");
            switch (action){
                case 1 :
                    monthRecap(user, idxLogin);
                    break;
                case 2 :
                    break;
                case 3 :
                    exit(0);
                    break;
            }
            break;
        case 2 :
            //Memanggil Fungsi Pengeluaran Berdasarkan Kategori
            dailyRecap(user, idxLogin);
            system("read -n 1 -s -p ''");

            //Menu Pilihan Setelah Menampilkan Fungsi Pengeluaran per Kategori
            printf("|| ================================================== ||\n");
            printf("||    No  |                   Action                  ||\n");
            printf("|| ================================================== ||\n");
            printf("||   [1]  | Kembali ke Rekapan Bulanan                ||\n");
            printf("||   [2]  | Kembali ke Menu                           ||\n");
            printf("||   [3]  | Keluar Program                            ||\n");
            printf("|| ================================================== ||\n");
            reVldInt(&action, "|| Input Anda [] : ");
            switch(action){
                case 1 :
                    monthRecap(user, idxLogin);
                    break;
                case 2 :
                    break;
                case 3 :
                    exit(0);
                    break;
            }
            break;
        case 3 :
            break;
        case 4 :
            exit(0);
            break;
    }
}

//Fungsi Perubahan pada Hari Ini
void todayManage(struct dataUser user[], int idxLogin, int totalUser){
    system("clear");
    fflush(stdin);
    int action;
    printf("|| ================================================== ||\n");
    printf("||             Atur Keuangan Anda Hari Ini            ||\n");
    printf("||                   %d %s %d                 ||\n", tglHariIni(), bulanString(), thnHariIni());
    printf("|| ================================================== ||\n");
    printf("||    No  |                   Action                  ||\n");
    printf("|| ================================================== ||\n");
    printf("||   [1]  | Tambah Pemasukan                          ||\n");
    printf("||   [2]  | Tambah Pengeluaran                        ||\n");
    printf("||   [3]  | Rekap Keuangan Bulan Ini                  ||\n");
    printf("||   [4]  | Keluar Program                            ||\n");
    printf("|| ================================================== ||\n");
    printf("|| Input Anda : ");
    scanf("%d", &action);
    switch(action){
        case 1 :
            //Memanggil Fungsi Pemasukan
            pemasukan(user, idxLogin, totalUser);
            break;
        case 2 :
            //Memanggil Fungsi Pengeluaran
            pengeluaran(user, idxLogin, totalUser);
            break;
        case 3 :
            //Memanggil Fungsi Rekapan Bulanan
            monthRecap(user, idxLogin);
            break;
        case 4 :
            //Fungsi Keluar
            exit(0);
        default :
            //Melakukan Rekursi Fungsi Jika Inputan Tidak Valid
            todayManage(user, idxLogin, totalUser);
            break;
    }
}

//Fungsi Login
void loginCheck(struct dataUser user[], int idxLogin, int totalUser){
    system("clear");
    fflush(stdin);
    //Setup Variabel
    char username[50];
    char pw[38] = {0};
    char *p = pw;
    FILE *fp = stdin;
    ssize_t nchr = 0;

    printf("\n|| ================================================== ||\n");
    printf("||                 Masuk ke akun anda!                ||\n");
    printf("|| ================================================== ||\n");

    //Input Username
    printf("|| Username : ");
    scanf("%[^\n]%*c", username);
    fflush(stdin);

    //Input Password
    printf("|| Password : ");
    nchr = getpasswd (&p, 38, '*', fp);

    //Mencari Akun di dalam Database
    idxLogin = idxSearch(user, username, pw);
    if(idxLogin != -1){
        system("clear");
        printf("|| ================================================== ||\n");
        printf("||                     Login Sukses                   ||\n");
        printf("|| ================================================== ||\n");
        printf("||                                                    ||\n");
        printf("|| Kamu masuk sebagai %s\n", user[idxLogin].namaLengkap);
        printf("||                                                    ||\n");
        printf("|| ================================================== ||\n");
        system("read -n 1 -s -p ''");
        while(true){
            fflush(stdin);
            todayManage(user, idxLogin, totalUser);
        }
    }else{
        system("clear");
        printf("|| ================================================== ||\n");
        printf("||                     Login Gagal                    ||\n");
        printf("||                                                    ||\n");
        printf("||              Tekan Enter Untuk Mengulang           ||\n");
        printf("|| ================================================== ||\n");
        system("read -n 1 -s -p ''");
        loginCheck(user, idxLogin, totalUser);
    }
}

//Fungsi Menu Awal
void menu(struct dataUser user[], int idxLogin, int totalUser){
    system("clear");
    fflush(stdin);
    int action;
    printf("|| ================================================== ||\n");
    printf("||                  Cash Flow Tracker                 ||\n");
    printf("|| ================================================== ||\n");
    printf("||    No  |                   Action                  ||\n");
    printf("|| ================================================== ||\n");
    printf("||   [1]  | Masuk                                     ||\n");
    printf("||   [2]  | Daftar                                    ||\n");
    printf("|| ================================================== ||\n");
    reVldInt(&action, "|| Input Anda [] : ");
    switch(action){
        case 1 :
            loginCheck(user, idxLogin, totalUser);
            break;
        case 2 :
            registerAcc(user, totalUser);
            break;
        default :
            menu(user, idxLogin, totalUser);
            break;
    }
}
