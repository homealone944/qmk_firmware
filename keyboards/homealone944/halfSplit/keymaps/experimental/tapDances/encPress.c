/*
*   ChangeLayer Tap Dance
*/

static td_tap_t encTap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void printInfo(void){
    SEND_STRING( SS_TAP(X_LWIN) SS_DELAY(500) "Noepad" SS_DELAY(500) SS_TAP(X_ENT) SS_DELAY(500) );
    send_string( getInfo() );
}

void encPress_end(qk_tap_dance_state_t *state, void *user_data) {
    encTap_state.state = cur_dance(state);
    switch (encTap_state.state) {
        case TD_SINGLE_TAP:
            switch(curLayer){
                default: register_code( KC_MUTE ); break;
                case 1: register_code( KC_MUTE ); break;
                case 2: register_code( KC_MUTE ); break;
            } break;
        case TD_SINGLE_HOLD: register_code( KC_RALT ); break;
        case TD_DOUBLE_TAP: register_code( KC_F2 ); break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: tap_code( KC_MUTE ); register_code( KC_MUTE ); break;
        case TD_TRIPLE_TAP: layer_move( 0 ); break;
        case TD_TRIPLE_HOLD: printInfo(); break;
        default: break;
    }
}

void encPress_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (encTap_state.state) {
        case TD_SINGLE_TAP:
            switch(curLayer){
                default: unregister_code( KC_MUTE ); break;
                case 1: unregister_code( KC_MUTE ); break;
                case 2: unregister_code( KC_MUTE ); break;
            }break;
        case TD_SINGLE_HOLD: unregister_code( KC_RALT ); break;
        case TD_DOUBLE_TAP: unregister_code( KC_F2 ); break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: break;
        case TD_TRIPLE_TAP: break;
        case TD_TRIPLE_HOLD: break;
        default: break;
    }
    encTap_state.state = TD_NONE;
}
