#include <time.h>
#include <stdio.h>

int tglHariIni(){
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_mday;
}

int blnHariIni(){
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_mon+1;
}

int thnHariIni(){
    time_t t;
    t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year+1900;
}
