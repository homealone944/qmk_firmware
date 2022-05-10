/*
*   altTab Tap Dance
*/

static td_tap_t altTab_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void tab_end(qk_tap_dance_state_t *state, void *user_data) {
    altTab_state.state = cur_dance(state);
    switch (altTab_state.state) {
        case TD_SINGLE_TAP: register_code(KC_TAB); break;       // Press tab
        case TD_SINGLE_HOLD: register_code(KC_TAB); break;      // Hold Tab
        case TD_DOUBLE_TAP: register_code(KC_LALT); register_code(KC_TAB); break;   //Single alt-tab
        case TD_DOUBLE_HOLD: register_code(KC_LALT); tap_code(KC_TAB); break;       //Alt-tab + hold alt
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_TAB); register_code(KC_TAB); break;
        default: break;
    }
}

void tab_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (altTab_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_TAB); break;
        case TD_SINGLE_HOLD: unregister_code(KC_TAB); break;
        case TD_DOUBLE_TAP: unregister_code(KC_LALT); unregister_code(KC_TAB); break;
        case TD_DOUBLE_HOLD: unregister_code(KC_LALT); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_TAB); break;
        default: break;
    }
    altTab_state.state = TD_NONE;
}
