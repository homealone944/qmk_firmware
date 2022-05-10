/* 
* Encoder
* https://docs.qmk.fm/#/feature_encoders
*/

//Default values for encoder
#define DEFAULT_CLOCKWISE       KC_VOLU
#define DEFAULT_ANTI_CLOCKWISE  KC_VOLU

typedef struct encoderCode{
    int16_t clockW;
    int16_t antiC;
} encoderCode;

struct encoderCode EncoderList[32];

void setEncoder(void){
    EncoderList[0] = (encoderCode) {.clockW = KC_VOLU, .antiC = KC_VOLD};
    EncoderList[1] = (encoderCode) {.clockW = KC_VOLU, .antiC = KC_VOLD};
    EncoderList[2] = (encoderCode) {.clockW = KC_C, .antiC = KC_A};
}
