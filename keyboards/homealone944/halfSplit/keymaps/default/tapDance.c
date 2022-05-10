/*
* Tap Dance
* https://docs.qmk.fm/#/feature_tap_dance?id=example-4
*/

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
        else if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}


/*
* Custom Tap Dance Functions
*/

// Create an instance of 'td_tap_t' for the 'enc' tap dance.
static td_tap_t encTap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void ChangeL_end(qk_tap_dance_state_t *state, void *user_data) {
    encTap_state.state = cur_dance(state);
    switch (encTap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_0); break;
        case TD_SINGLE_HOLD: register_code(KC_RALT); break;
        case TD_DOUBLE_TAP: layer_move(0); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_0); register_code(KC_0); break;
        default: break;
    }
}

void ChangeL_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (encTap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_0); break;
        case TD_SINGLE_HOLD: unregister_code(KC_RALT); break;
        case TD_DOUBLE_TAP: layer_move(0); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_0); break;
        default: break;
    }
    encTap_state.state = TD_NONE;
}
