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
    for(int i = 0; i < checkLines()/45; i++){
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
        for(int i = 0; i < checkLines()/45; i++){
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
        user[idxLogin].jenisPengeluaran[0] += cost;
    }else if(option == 2){
        user[idxLogin].jenisPengeluaran[1] += cost;
    }else if(option == 3){
        user[idxLogin].jenisPengeluaran[2] += cost;
    }else if(option == 4){
        user[idxLogin].jenisPengeluaran[3] += cost;
    }else if(option == 5){
        user[idxLogin].jenisPengeluaran[4] += cost;
    }else if(option == 6){
        user[idxLogin].jenisPengeluaran[5] += cost;
    }else if(option == 7){
        user[idxLogin].jenisPengeluaran[6] += cost;
    }else if(option == 8){
        user[idxLogin].jenisPengeluaran[7] += cost;
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
    char inputKeterangan[1000];
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

//Fungsi Rekapan Bulanan
void monthRecap(struct dataUser user[], int idxLogin){
    fflush(stdin);
    system("clear");
    //Setup Variabel (Digunakan untuk men-sorting pengeluaran, sehingga pengeluaran yang terbanyak ditampilkan terlebih dahulu)
    int penandaCtg[] = {0, 1, 2, 3, 4, 5, 6, 7};
    bubbleSort(user[idxLogin].jenisPengeluaran, penandaCtg);
    //Catatan : Hanya Menampilkan Jika Pengeluaran > 0
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

    //Menu Pilihan
    int action;
    printf("|| ================================================== ||\n");
    printf("||    No  |                   Action                  ||\n");
    printf("|| ================================================== ||\n");
    printf("||   [1]  | Lihat Riwayat Pengeluaran                 ||\n");
    printf("||   [2]  | Kembali ke Menu                           ||\n");
    printf("||   [3]  | Keluar Program                            ||\n");
    printf("|| ================================================== ||\n");
    reVldInt(&action, "|| Input Anda [] : ");
    system("clear");
    switch(action){
        case 1 :
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
                        printf("|| %d %s             || Rp.%d                ||\n", i+1, bulanString(), user[idxLogin].tglPengeluaran[i]);
                    }else{
                        printf("|| %d %s            || Rp.%d                ||\n", i+1, bulanString(), user[idxLogin].tglPengeluaran[i]);
                    }
                }
            }
            printf("|| ================================================== ||\n");
            printf("||          Total         || Rp.%d                ||\n", user[idxLogin]. totalPengeluaran);
            printf("|| ================================================== ||\n");

            //Menu Pilihan
            system("read -n 1 -s -p ''");
            fflush(stdin);
            printf("|| ================================================== ||\n");
            printf("||    No  |                   Action                  ||\n");
            printf("|| ================================================== ||\n");
            printf("||   [1]  | Kembali ke Menu                           ||\n");
            printf("||   [2]  | Keluar Program                            ||\n");
            printf("|| ================================================== ||\n");
            reVldInt(&action, "|| Input Anda [] : ");
            switch (action){
                case 1 :
                    break;
                case 2 :
                    exit(0);
                    break;
            }
            break;
        case 2 :
            break;
        case 3 :
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
            pemasukan(user, idxLogin, totalUser);
            break;
        case 2 :
            pengeluaran(user, idxLogin, totalUser);
            break;
        case 3 :
            monthRecap(user, idxLogin);
            break;
        case 4 :
            exit(0);
        default :
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
