/*
* Utility File
*/
#include <string.h>

// Converts int to a string
char *toString(int x){
    static char newString[5];
    itoa(x, newString, 10);
    return newString;
};

//Holds up to 32 Layer names (up to 16 chars)
char layerNames_str[32][16+1];
void setLayerNames(void){
    strcpy(layerNames_str[0], "default");
    strcpy(layerNames_str[1], "overwatch");
    strcpy(layerNames_str[2], "valorant");
    strcpy(layerNames_str[3], "numPad");
    strcpy(layerNames_str[4], "Fn");
}
