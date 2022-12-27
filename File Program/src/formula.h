#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

//Fungsi Untuk Menghitung Persentase
//Input Berupa Integer Sedangkan Output Berupa Float!
float persentase(int a, int b){
    float persentase = (float)a/(float)b * 100;
    return persentase;
}

//Fungsi Untuk Melakukan Sorting
//Menggunakan Metode "Bubble Sort"
void bubbleSort(int arr[], int arrPenanda[]){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(arr[j] < arr[j+1]){
                //Sorting Array Asli
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                //Sorting Array Tiruan
                int tempPen = arrPenanda[j];
                arrPenanda[j] = arrPenanda[j+1];
                arrPenanda[j+1] = tempPen;
            }
        }
    }
}

//Fungsi Untuk Menghitung Banyaknya Baris
//Pada File account.txt
int checkLines(char *fileDirectory){
    FILE *fptr;
    char ch;
    int lines = 1;
    fptr = fopen(fileDirectory, "r");
    if(fptr == NULL){
        printf("Unable to open file");
    }
    do{
        ch = fgetc(fptr);
        if(ch == '\n'){
            lines++;
        }
    }while(ch != EOF);

    fclose(fptr);
    return lines;
}
