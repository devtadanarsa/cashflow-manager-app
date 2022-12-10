#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>

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

ssize_t getpasswd (char **pw, size_t sz, int mask, FILE *fp)
{
    if (!pw || !sz || !fp) return -1;
    #ifdef MAXPW
        if (sz > MAXPW) sz = MAXPW;
    #endif

    if (*pw == NULL){
        void *tmp = realloc (*pw, sz * sizeof **pw);
        if (!tmp)
            return -1;
        memset (tmp, 0, sz);
        *pw =  (char*) tmp;
    }

    size_t idx = 0;
    int c = 0;

    struct termios old_kbd_mode;
    struct termios new_kbd_mode;

    if (tcgetattr (0, &old_kbd_mode)) {
        fprintf (stderr, "%s() error: tcgetattr failed.\n", __func__);
        return -1;
    } 
    memcpy (&new_kbd_mode, &old_kbd_mode, sizeof(struct termios));

    new_kbd_mode.c_lflag &= ~(ICANON | ECHO);
    new_kbd_mode.c_cc[VTIME] = 0;
    new_kbd_mode.c_cc[VMIN] = 1;
    if (tcsetattr (0, TCSANOW, &new_kbd_mode)) {
        fprintf (stderr, "%s() error: tcsetattr failed.\n", __func__);
        return -1;
    }

    while (((c = fgetc (fp)) != '\n' && c != EOF && idx < sz - 1) ||
            (idx == sz - 1 && c == 127))
    {
        if (c != 127) {
            if (31 < mask && mask < 127) 
                fputc (mask, stdout);
            (*pw)[idx++] = c;
        }
        else if (idx > 0) { 
            if (31 < mask && mask < 127) {
                fputc (0x8, stdout);
                fputc (' ', stdout);
                fputc (0x8, stdout);
            }
            (*pw)[--idx] = 0;
        }
    }
    (*pw)[idx] = 0; 

    if (tcsetattr (0, TCSANOW, &old_kbd_mode)) {
        fprintf (stderr, "%s() error: tcsetattr failed.\n", __func__);
        return -1;
    }

    if (idx == sz - 1 && c != '\n') 
        fprintf (stderr, " (%s() warning: truncated at %zu chars.)\n",
                __func__, sz - 1);

    return idx; 
}
