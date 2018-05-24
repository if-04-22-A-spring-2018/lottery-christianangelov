#include <stdio.h>
#include "lottery.h"

static char* File;
static char digit;
static int* drawn;
static bool b =false;

bool init_lottery(char* filename, char j){

    FILE* filex= fopen(filename, "r");
    digit = j;
    b = false;
    File = filename;

    if(filex ==NULL){
      return false;
    }
    fclose(filex);

    return true;
}
bool get_tip(int tip, int* array){

    FILE* file = fopen(File, "r");
    char input[MAX_LINE_LEN] = {0};

    int r = 0;
    if(tip < 0 || file == 0){
        fclose(file);
        return false;
    }
    char* outp = fgets(input, MAX_LINE_LEN, file);
    while(outp != NULL && r < tip){
        outp = fgets(input, MAX_LINE_LEN, file);
        r++;
        if(outp != input){
            fclose(file);
            return false;
        }
    }

    if(ftell(file) == EOF){
        fclose(file);
        return false;
    }
    int pos = 0;

    while(input[pos] !=digit&& pos < UUID_LEN){
        pos++;
    }

    int insertionpos = 0;
    int f = 0;

    while(insertionpos < 6){
        pos++;
        if(input[pos] <= '9' && input[pos]>= '0'){
            f = f*10+ (input[pos] - '0');
        }
        else{
            array[insertionpos] = f;
            f = 0;
            insertionpos++;
        }
    }
    fclose(file);
    return true;
}
bool set_drawing(int* array){

    b = true;
    drawn = array;

    return false;
}
int get_tip_result(int tip){
    if(!b )return -1;
    int bb[6];
    if(!get_tip(tip, bb))return -2;
    int count = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if(bb[i] == drawn[j])count++;
        }
    }
    return count;
}
int get_right_tips_count(int tip){
    if(!b|| tip < 0 || tip > TIP_SIZE)return -1;
    int b = 0;
    int count = 0;
    int x = 0;

    while(x != -2&& x != -1){
        x = get_tip_result(b);
        if(x == tip)count++;
        b++;
    }
    return count;
}
