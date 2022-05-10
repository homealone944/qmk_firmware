/* 
* Encoder
* https://docs.qmk.fm/#/feature_encoders
*/

//Default values for encoder
#define DEFAULT_CLOCKWISE       KC_DOWN
#define DEFAULT_ANTI_CLOCKWISE  KC_UP

typedef struct encoderCode{
    int16_t clockW;
    int16_t antiC;
} encoderCode;

struct encoderCode EncoderList[32];

void setEncoder(void){
    EncoderList[0] = (encoderCode) {.clockW = KC_PGDN, .antiC = KC_PGUP};
    EncoderList[1] = (encoderCode) {.clockW = KC_VOLU, .antiC = KC_VOLD};
    EncoderList[2] = (encoderCode) {.clockW = KC_C, .antiC = KC_A};
}
