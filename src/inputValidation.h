#include <stdio.h>
#include <stdlib.h>

int validInt(int *var){
	char buff[1024];
	char cek;
	fflush(stdin);
	if(fgets(buff, sizeof(buff), stdin) != NULL){
		if(sscanf(buff, "%d %c", var, &cek) == 1) {
			return 1;
		}
	}
	return 0;
}

void reVldInt(int *var, char *prompt){
	while(1){
		printf(prompt);
		if(validInt(var)){
			break;
			printf("Input hanya berupa angka!! \n");
			printf("\n");
        }    
	}
}

int validFloat(float *var){
	char buff[1024];
	char cek;
	fflush(stdin);
	if(fgets(buff, sizeof(buff), stdin) != NULL){
		if(sscanf(buff, "%f %c", var, &cek) == 1) {
			return 1;
		}
	}
	return 0;
}

void reVldFloat(float *var, char *prompt){
	while(1){
		printf(prompt);
		if(validFloat(var)){
			break;
			printf("Input hanya berupa angka!! \n");
			printf("\n");
        }    
	}
}
