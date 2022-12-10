#include <stdio.h>
#include <stdlib.h>

//fungsi validasi int
int validInt(int *var){
	char buff[1024];
	char check;
	if (fgets(buff, sizeof(buff), stdin) !=NULL) {
		if (sscanf(buff, "%d %c", var, &check) ==1){
			return 1;
		}
	}
	return 0;
}

//prosedur output ketika user salah memasukkan input
void reVldInt(int *var, char *prompt){
	while(1){
		printf(prompt);
		if(validInt(var))
			break;
		printf("Input hanya berupa angka!! \n");
		printf("\n");
	}
}