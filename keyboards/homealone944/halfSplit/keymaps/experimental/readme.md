# The experimental keymap for halfSplit

## How to add a new layer
1. Add your layer name to `layer_names`
3. Add your layout to `keymaps`
    >**NOTE:** Use the [Template](#Template)
4. Add Encoder keycodes in **encoder.c**
5. Edit `setRGB()` in **lighting.c** to match lightingLayer to your layer


## Compile firmware with QMK MSYS
`qmk compile -kb homealone944/halfSplit -km experimental`

## Template
```
[LAYERNAME]=LAYOUT(
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    TD(ChangeL),
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO,
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_NO
)
```
