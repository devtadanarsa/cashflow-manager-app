float persentase(int a, int b){
    float persentase = (float)a/(float)b * 100;
    return persentase;
}

void bubbleSort(int arr[], int arrPenanda[]){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            if(arr[j] < arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                int tempPen = arrPenanda[j];
                arrPenanda[j] = arrPenanda[j+1];
                arrPenanda[j+1] = tempPen;
            }
        }
    }
}
