#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "formula.h"

struct dataUser
{
    char namaLengkap[50];
    char username[40];
    char password[40];
    int saldo;
    int jenisPengeluaran[8];
    int totalPengeluaran;
};

void registerAcc()
{
    system("clear");
    fflush(stdin);
    FILE *fptr;
    fptr = fopen("database/account.txt", "a");
    char namaLengkap[50];
    char username[40];
    char password[40];

    printf("|| Nama Lengkap : ");
    scanf("%[^\n]", namaLengkap);
    getchar();
    fputs(namaLengkap, fptr);
    fputs("\n", fptr);
    fflush(stdin);
    printf("|| Username : ");
    scanf("%s", username);
    getchar();
    fputs(username, fptr);
    fputs("\n", fptr);
    fflush(stdin);
    printf("|| Password : ");
    scanf("%s", password);
    getchar();
    fputs(password, fptr);
    fputs("\n", fptr);

    for (int i = 0; i < 10; i++)
    {
        fputs("0", fptr);
        fputs("\n", fptr);
    }
    fclose(fptr);
    char enter;
    printf("|| ================================================== ||\n");
    printf("||                Akun anda sudah siap!               ||\n");
    printf("||        Tekan Enter untuk keluar dari program       ||\n");
    printf("|| ================================================== ||\n");
    scanf("%c", &enter);
    exit(0);
}

void readFile(struct dataUser user[10])
{
    FILE *fptr;
    fptr = fopen("database/account.txt", "r");
    for (int i = 0; i < 2; i++)
    {
        fscanf(fptr, "%[^\n]%*c", user[i].namaLengkap);
        fscanf(fptr, "%[^\n]%*c", user[i].username);
        fscanf(fptr, "%[^\n]%*c", user[i].password);
        char digitUang[10];
        fscanf(fptr, "%[^\n]%*c", digitUang);
        user[i].saldo = atoi(digitUang);
        for (int j = 0; j < 8; j++)
        {
            fscanf(fptr, "%[^\n]%*c", digitUang);
            user[i].jenisPengeluaran[j] = atoi(digitUang);
        }
        fscanf(fptr, "%[^\n]%*c", digitUang);
        user[i].totalPengeluaran = atoi(digitUang);
    }
    fclose(fptr);
}

int idxSearch(struct dataUser user[10], char *username, char *password){
    for(int i = 0; i < 3; i++){
        if(strcmp(user[i].username, username) == 0 && strcmp(user[i].password, password) == 0){
            return i;
        }
    }
    return -1;
}

void writeFile(struct dataUser user[10]){
    FILE *fptr;
    fptr = fopen("database/account.txt", "w");
    char angka[10];
    for (int i = 0; i < 2; i++){
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
    }
    fclose(fptr);
}

void tmbBiaya(struct dataUser user[10], int idxLogin, int option){
    fflush(stdin);
    int cost;
    printf("|| ================================================== ||\n");
    printf("||                Biaya Yang Anda Keluarkan           ||\n");
    printf("|| ================================================== ||\n");
    printf("|| Input Anda : Rp.");
    scanf("%d", &cost);
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
    user[idxLogin].totalPengeluaran = 0;
    for(int i = 0; i < 8; i++){
        user[idxLogin].totalPengeluaran += user[idxLogin].jenisPengeluaran[i];
    }
    user[idxLogin].saldo -= user[idxLogin].totalPengeluaran;
    writeFile(user);
}

void pengeluaran(struct dataUser user[10], int idxLogin){
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
    printf("|| Input Anda : ");
    scanf("%d", &option);
    switch(option){
        case 1 :
            tmbBiaya(user, idxLogin, 1);
            break;
        case 2 :
            tmbBiaya(user, idxLogin, 2);
            break;
        case 3 :
            tmbBiaya(user, idxLogin, 3);
            break;
        case 4 :
            tmbBiaya(user, idxLogin, 4);
            break;
        case 5 : 
            tmbBiaya(user, idxLogin, 5);
            break;
        case 6 :
            tmbBiaya(user, idxLogin, 6);
            break;
        case 7 :
            tmbBiaya(user, idxLogin, 7);
            break;
        case 8 :
            tmbBiaya(user, idxLogin, 8);
            break;

    }
}

void monthRecap(struct dataUser user[10], int idxLogin){
    fflush(stdin);
    system("clear");
    printf("|| ================================================== ||\n");
    printf("||                   Rekap Pengeluaran                ||\n");
    printf("||                       Bulan Ini                    ||\n");
    printf("|| ================================================== ||\n");
    printf("||                                                    ||\n");
    printf("|| Total Pengeluaran : Rp.%d\n", user[idxLogin].totalPengeluaran);
    printf("|| Sisa Saldo : Rp.%d\n", user[idxLogin].saldo);
    printf("||                                                    ||\n");
    printf("|| ================================================== ||\n");
    printf("||                 Persentase Pengeluaran             ||\n");
    printf("||                                                    ||\n");
    int penandaCtg[] = {0, 1, 2, 3, 4, 5, 6, 7};
    bubbleSort(user[idxLogin].jenisPengeluaran, penandaCtg);
    for(int i = 0; i < 8; i++){
        if(user[idxLogin].jenisPengeluaran[i] > 0){
            if(penandaCtg[i] == 0){
                printf("|| %.1f%c Makanan dan Minuman\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%');
            }else if(penandaCtg[i] == 1){
                printf("|| %.1f%c Transportasi\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%');
            }else if(penandaCtg[i] == 2){
                printf("|| %.1f%c Hiburan atau Rekreasi\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%');
            }else if(penandaCtg[i] == 3){
                printf("|| %.1f%c Biaya Kesehatan\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%');
            }else if(penandaCtg[i] == 4){
                printf("|| %.1f%c Biaya Rumah Tangga\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%');
            }else if(penandaCtg[i] == 5){
                printf("|| %.1f%c Biaya Pendidikan\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%');
            }else if(penandaCtg[i] == 6){
                printf("|| %.1f%c Pakaian\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%');
            }else if(penandaCtg[i] == 7){
                printf("|| %.1f%c Lainnya\n", persentase(user[idxLogin].jenisPengeluaran[i], user[idxLogin].totalPengeluaran), '%');
            }
        }else{
            continue;
        }
    }
    printf("|| ================================================== ||\n");
    printf("||             Tekan Enter Untuk Melanjutkan          ||\n");
    printf("|| ================================================== ||\n");
    char enter;
    scanf("%c", &enter);
    int action;
    printf("|| ================================================== ||\n");
    printf("||    No  |                   Action                  ||\n");
    printf("|| ================================================== ||\n");
    printf("||   [1]  | Lihat Rincian                             ||\n");
    printf("||   [2]  | Keluar Program                            ||\n");
    printf("|| ================================================== ||\n");
    printf("|| Input Anda [] : ");
    scanf("%d", &action);
    switch(action){
        case 1 :
            printf("|| ================================================== ||\n");
            printf("||                   Rincian Pengeluaran              ||\n");
            printf("|| ================================================== ||\n");
            for(int i = 0; i < 8; i++){
                if(penandaCtg[i] == 0){
                    printf("|| Makanan dan Minuman : Rp.%d\n", user[idxLogin].jenisPengeluaran[i]);
                }else if(penandaCtg[i] == 1){
                    printf("|| Transportasi : Rp.%d\n", user[idxLogin].jenisPengeluaran[i]);
                }else if(penandaCtg[i] == 2){
                    printf("|| Hiburan & Rekreasi : Rp.%d\n", user[idxLogin].jenisPengeluaran[i]);
                }else if(penandaCtg[i] == 3){
                    printf("|| Biaya Kesehatan : Rp.%d\n", user[idxLogin].jenisPengeluaran[i]);
                }else if(penandaCtg[i] == 4){
                    printf("|| Biaya Rumah Tangga : Rp.%d\n", user[idxLogin].jenisPengeluaran[i]);
                }else if(penandaCtg[i] == 5){
                    printf("|| Biaya Pendidikan : Rp.%d\n", user[idxLogin].jenisPengeluaran[i]);
                }else if(penandaCtg[i] == 6){
                    printf("|| Pakaian : Rp.%d\n", user[idxLogin].jenisPengeluaran[i]);
                }else if(penandaCtg[i] == 7){
                    printf("|| Lainnya : Rp.%d\n", user[idxLogin].jenisPengeluaran[i]);
                }
            }
            fflush(stdin);
            printf("|| ================================================== ||\n");
            printf("||    No  |                   Action                  ||\n");
            printf("|| ================================================== ||\n");
            printf("||   [1]  | Kembali ke Menu                           ||\n");
            printf("||   [2]  | Keluar Program                            ||\n");
            printf("|| ================================================== ||\n");
            scanf("%d", &action);
            switch (action){
                case 1 :
                    break;
                case 2 :
                    exit(0);
                    break;
            }
            break;
        case 2 :
            exit(0);
            break;
    }
}

void todayManage(struct dataUser user[10], int idxLogin){
    system("clear");
    fflush(stdin);
    int action;
    printf("|| ================================================== ||\n");
    printf("||              Atur Keuangan Anda Hari Ini           ||\n");
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
        case 2 :
            pengeluaran(user, idxLogin);
            break;
        case 3 :
            monthRecap(user, idxLogin);
            break;
        case 4 :
            exit(0);
    }
}

void loginCheck(struct dataUser user[10], int idxLogin){
    fflush(stdin);
    char username[50];
    char password[50];
    char enter;
    fflush(stdin);
    printf("\n|| ================================================== ||\n");
    printf("||                   Masuk ke akun anda!              ||\n");
    printf("|| ================================================== ||\n");
    printf("|| Username : ");
    scanf("%[^\n]%*c", username);
    fflush(stdin);
    printf("|| Password : ");
    scanf("%[^\n]%*c", password);
    idxLogin = idxSearch(user, username, password);
    if(idxLogin != -1){
        system("clear");
        printf("|| ================================================== ||\n");
        printf("||                      Login Sukses                  ||\n");
        printf("|| ================================================== ||\n");
        printf("|| Kamu masuk sebagai %s\n", user[idxLogin].namaLengkap);
        printf("|| ================================================== ||\n");
        printf("||             Tekan Enter Untuk Melanjutkan          ||\n");
        printf("|| ================================================== ||\n");
        scanf("%c", &enter);
        while(true){
            todayManage(user, idxLogin);
        }
    }else{
        system("clear");
        printf("|| ================================================== ||\n");
        printf("||                      Login Gagal                   ||\n");
        printf("||                                                    ||\n");
        printf("||               Tekan Enter Untuk Mengulang          ||\n");
        printf("|| ================================================== ||\n");
        scanf("%c", &enter);
        loginCheck(user, idxLogin);
    }
}

void menu(struct dataUser user[10], int idxLogin){
    fflush(stdin);
    int action;
    printf("|| ================================================== ||\n");
    printf("||                   Cash Flow Tracker                ||\n");
    printf("|| ================================================== ||\n");
    printf("||    No  |                   Action                  ||\n");
    printf("|| ================================================== ||\n");
    printf("||   [1]  | Masuk                                     ||\n");
    printf("||   [2]  | Daftar                                    ||\n");
    printf("|| ================================================== ||\n");
    printf("|| Input Anda [] : ");
    scanf("%d", &action);
    switch(action){
        case 1 :
            loginCheck(user, idxLogin);
            break;
        case 2 :
            registerAcc();
            break;
    }
}
