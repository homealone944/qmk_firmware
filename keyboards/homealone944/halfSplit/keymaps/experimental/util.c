/*
* Utility File
*/
#include <string.h>

#define VERSION  "v0.1.0"


uint8_t curLayer = 0;   //0,1,2,...
uint8_t layerFlag = 0;  //0 is off, 1 is to use encoder as layer changer

// Converts int to a string
char *toString(int x){
    static char newString[5];
    itoa(x, newString, 10);
    return newString;
};

// Holds up to 32 Layer names (up to 16 chars)
char layerNames_str[32][16+1];

void setLayerNames(void){
    strcpy(layerNames_str[0], "gaming");
    strcpy(layerNames_str[1], "valorant");
    strcpy(layerNames_str[2], "numPad");
    strcpy(layerNames_str[3], "Fn");
    strcpy(layerNames_str[4], "default");
    // Add more layerNames here
}

// Returns string with information on keyboard
char *getInfo(void){
    static char info[128] = "HalfSplit by Homealone944 __";
    strcat(info, VERSION);
    strcat(info, "__ CurLayer:");
    strcat(info, layerNames_str[curLayer]);
    return info;
}
