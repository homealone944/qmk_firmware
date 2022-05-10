/* 
* RGB Section
* https://docs.qmk.fm/#/feature_rgblight
* {start, numLEDs, Color}
*/

const rgblight_segment_t PROGMEM flash[] = RGBLIGHT_LAYER_SEGMENTS (
    {0, 1, HSV_RED},
    {1, 1, HSV_GREEN},
    {2, 1, HSV_BLUE}
    
);
const rgblight_segment_t PROGMEM baseLayer[] = RGBLIGHT_LAYER_SEGMENTS (
    {0, 1, HSV_OFF},
    {1, 1, HSV_OFF},
    {2, 1, HSV_OFF}
    
);
const rgblight_segment_t PROGMEM l001[] = RGBLIGHT_LAYER_SEGMENTS (
    {0, 1, HSV_OFF},
    {1, 1, HSV_OFF},
    {2, 1, HSV_WHITE}
);
const rgblight_segment_t PROGMEM l010[] = RGBLIGHT_LAYER_SEGMENTS (
    {0, 1, HSV_OFF},
    {1, 1, HSV_WHITE},
    {2, 1, HSV_OFF}
);
const rgblight_segment_t PROGMEM l011[] = RGBLIGHT_LAYER_SEGMENTS (
    {0, 1, HSV_OFF},
    {1, 1, HSV_WHITE},
    {2, 1, HSV_WHITE}
);
const rgblight_segment_t PROGMEM l100[] = RGBLIGHT_LAYER_SEGMENTS (
    {0, 1, HSV_WHITE},
    {1, 1, HSV_OFF},
    {2, 1, HSV_OFF}
);
const rgblight_segment_t PROGMEM l101[] = RGBLIGHT_LAYER_SEGMENTS (
    {0, 1, HSV_WHITE},
    {1, 1, HSV_OFF},
    {2, 1, HSV_WHITE}
);
const rgblight_segment_t PROGMEM l110[] = RGBLIGHT_LAYER_SEGMENTS (
    {0, 1, HSV_WHITE},
    {1, 1, HSV_WHITE},
    {2, 1, HSV_OFF}
);
const rgblight_segment_t PROGMEM l111[] = RGBLIGHT_LAYER_SEGMENTS (
    {0, 1, HSV_WHITE},
    {1, 1, HSV_WHITE},
    {2, 1, HSV_WHITE}
);

// Define the array of RGBlayers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    flash,              //0
    baseLayer,          //1
    l001,               //2
    l010,               //...
    l011,
    l100,
    l101,
    l110,
    l111
);

// Sets RGBlayers to keymap layers 
void setRGB(layer_state_t state){
    //rgblight_set_layer_state(RGBLAYER, layer_state_cmp(state, LAYER));
    rgblight_set_layer_state(1, layer_state_cmp(state, 0));
    rgblight_set_layer_state(2, layer_state_cmp(state, 1));
    rgblight_set_layer_state(3, layer_state_cmp(state, 2));
    rgblight_set_layer_state(4, layer_state_cmp(state, 3));
    rgblight_set_layer_state(5, layer_state_cmp(state, 4));
}
