/*
*   Valorant_PointBuyPlant Tap Dance
*/

static td_tap_t valTap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

//Point Buy Plant 
void val_end(qk_tap_dance_state_t *state, void *user_data) {
    valTap_state.state = cur_dance(state);
    switch (valTap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_Z); break;     //Point
        case TD_SINGLE_HOLD: register_code(KC_4); break;    //Plant
        case TD_DOUBLE_TAP: register_code(KC_B); break;     //Buy
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_Z); register_code(KC_Z); break;
        default: break;
    }
}

void val_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (valTap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_Z); break;
        case TD_SINGLE_HOLD: unregister_code(KC_4); break;
        case TD_DOUBLE_TAP: unregister_code(KC_B); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_Z); break;
        default: break;
    }
    valTap_state.state = TD_NONE;
}