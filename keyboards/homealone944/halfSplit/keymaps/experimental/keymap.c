/* Copyright 2021 Homealone944
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#include "util.c"
#include "lighting.c"
#include "listTD.c"
#include "encoderRot.c"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _OW,
    _Val,
    _NumPad,
    _FN,
    _BASE,
    //Add more layers here
};

enum custom_keycodes {
    lFlag = SAFE_RANGE,
    print
    //Add more macros here
};

enum tap_Dances {
    encPress,
    valPBP,
    altTab
    //Add more tapDances here
};

//Custom Variables
//#define DEBUG
#define ENC_LAYER_LOOPS
#define RGB_ON_STARTUP

/*
* Keymaps 
* https://docs.qmk.fm/#/keycodes
* https://docs.qmk.fm/#/feature_layers
*/
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_Game] = LAYOUT(
        TD(altTab),     KC_Q,    KC_W,    KC_E,    KC_R,    TD(encPress),
        KC_Y,           KC_A,    KC_S,    KC_D,    KC_F,    KC_ESC,     KC_H,
        KC_LSFT,        KC_Z,    KC_X,    KC_C,    KC_V,    KC_LCTL,    KC_SPC
    ),
    [_Val] = LAYOUT(
        TD(altTab),     KC_Q,   KC_W,    KC_E,    KC_R,    TD(encPress),
        KC_M,           KC_A,   KC_S,    KC_D,    KC_F,    KC_ESC,     TD(valPBP),
        KC_LSFT,        KC_T,   KC_X,    KC_G,    KC_C,    KC_LCTL,    KC_SPC
    ),
    [_NumPad] = LAYOUT(
        KC_EQL,   KC_7,    KC_8,    KC_9,    KC_MINS,     TD(encPress),
        KC_NO,    KC_4,    KC_5,    KC_6,    KC_PLUS,     KC_NO,     KC_NO,
        KC_0,     KC_1,    KC_2,    KC_3,    KC_DOT,      KC_BSPC,     KC_ENT
    ),
    [_FN] = LAYOUT(
        KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_NO,    TD(encPress),
        KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_NO,    RGB_TOG,     RGB_VAI,
        KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_NO,    RGB_MOD,     RGB_VAD
    ),
    [_BASE] = LAYOUT(
        TD(altTab),     KC_Q,       KC_W,       KC_E,       KC_R,      TD(encPress),
        print,          KC_A,       KC_S,       KC_D,       KC_F,      KC_ESC,      KC_ENT,
        KC_LSFT,        KC_Z,       KC_X,       KC_C,       KC_V,      KC_LCTL,     KC_SPC
    ),
};

/*
* Macros
* https://docs.qmk.fm/#/feature_macros
*/
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case lFlag:
            if (record->event.pressed)
                layerFlag = 1;
            else
                layerFlag = 0;
            break;
        case print:
            if (record->event.pressed){
                send_string( "WOAH!" );
            }
            break;
        //Add more custom Keycodes here
    }
    return true;
};

/* 
* Encoder
* https://docs.qmk.fm/#/feature_encoders
*/
void encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t temp_mod = get_mods();
    uint8_t temp_osm = get_oneshot_mods();
    uint8_t numLayers = sizeof(keymaps)/sizeof(keymaps[0]);

    if( ((temp_mod | temp_osm) & MOD_MASK_ALT) | layerFlag) {
        #ifdef ENC_LAYER_LOOPS
            if (clockwise){
                curLayer ++;
                curLayer = curLayer%numLayers;
            }
            else{
                if(curLayer == 0)
                    curLayer = numLayers-1;
                else
                    curLayer --;
            }
            
        #else
            if (clockwise)
                curLayer ++;
            else
                if(curLayer != 0)   //Since unsigned int, don't decrement from 0 (will loop around)
                    curLayer --;
            //Clamp the current layer
            if(curLayer > numLayers-1)
                curLayer = numLayers-1;
        #endif

        #ifdef DEBUG
            send_string("->");
            send_string( toString(curLayer) );
            send_string(";");
        #endif

        //Go to new layer
        layer_move(curLayer);   
    }
    else {
        encoderCode curEncoder = EncoderList[curLayer];
        if (clockwise){
            tap_code( (curEncoder.clockW == 0)? DEFAULT_CLOCKWISE : curEncoder.clockW);
        } else {
            tap_code( (curEncoder.antiC == 0)? DEFAULT_ANTI_CLOCKWISE : curEncoder.antiC);
        }
    }//End Encoder based off layer
}

/*
* Tap Dance
* https://docs.qmk.fm/#/feature_tap_dance?id=how-to-use
*/
qk_tap_dance_action_t tap_dance_actions[] = {
    [encPress] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, encPress_end, encPress_reset, 250),
    [valPBP] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, val_end, val_reset, 250),
    [altTab] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, tab_end, tab_reset, 250)
    //Add tap dance actions
};


// On Keyboard Init
void keyboard_post_init_user(void) {
    #ifdef RGB_ON_STARTUP   // Enable RGB on startup
        rgblight_enable();
    #endif

    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    
    // Set encoder keycodes for each layer
    setEncoder();
    setLayerNames();
}

// On Layer Change
layer_state_t layer_state_set_kb(layer_state_t state) {
    setRGB(state);
    
    curLayer = get_highest_layer(state);

    #ifdef DEBUG
        send_string("(");
        send_string( toString(curLayer) );
        send_string(")");
    #endif

    return state;
}

/*
    Future
    https://docs.qmk.fm/#/feature_leader_key

    Add print what current keymap
    Encoder tap dance press diff per layer
*/

