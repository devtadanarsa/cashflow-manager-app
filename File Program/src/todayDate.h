#include <time.h>
#include <stdio.h>

//Fungsi Untuk Mendapatkan Tanggal (return : integer)
int tglHariIni(){
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_mday;
}

//Fungsi Untuk Mendapatkan Bulan (return : integer)
//Fungsi ini akan dipakai di fungsi bulanString() untuk mengubah nilai return menjadi string!!
int blnHariIni(){
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_mon+1;
}

//Fungsi Untuk Mendapatkan Tahun (return : integer)
int thnHariIni(){
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year+1900;
}

//Fungsi Untuk Mengubah Bulan Menjadi String
//Jika fungsi ini dipanggil, maka akan menampilkan bulan pada hari ini berupa string.
char *bulanString(){
    int bulan = blnHariIni();
    switch(bulan){
        case 1 :
            return "Januari";
        case 2 :
            return "Februari";
        case 3 :
            return "Maret";
        case 4 :
            return "April";
        case 5 :
            return "Mei";
        case 6 :
            return "Juni";
        case 7 :
            return "Juli";
        case 8 :
            return "Agustus";
        case 9 :
            return "September";
        case 10 :
            return "Oktober";
        case 11 :
            return "November";
        case 12 :
            return "Desember";
    }
}
