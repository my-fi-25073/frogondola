// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


#include "os_detection.h"
enum my_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
    LAYER_EXTRA,
    LAYER_EXTRA2,
};

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define EXTRA1 MO(LAYER_EXTRA)
#define EXTRA2 MO(LAYER_EXTRA2)

#define _LO(x) LT(LAYER_LOWER, x)
#define _RA(x) LT(LAYER_RAISE, x)
#define _PT(x) LT(LAYER_POINTER, x)

#define _C(x) CTL_T(x)
#define _A(x) ALT_T(x)
#define _G(x) GUI_T(x)
#define _LS(x) LSFT_T(x)
#define _RS(x) RSFT_T(x)

#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#define LO_SPC  _LO(KC_SPC)
#define LO_COMM _LO(KC_COMM)
#define LO_DOT _LO(KC_DOT)

#define RA_COMM _RA(KC_COMM)
#define RA_DOT _RA(KC_DOT)

#define TO_PT TO(LAYER_POINTER)
#define TO_BA TO(LAYER_BASE)




#define SH____1 LSFT(KC_1)
#define SH____2 LSFT(KC_2)
#define SH____3 LSFT(KC_3)
#define SH____4 LSFT(KC_4)
#define SH____5 LSFT(KC_5)
#define SH____6 LSFT(KC_6)
#define SH____7 LSFT(KC_7)
#define SH____8 LSFT(KC_8)
#define SH____9 LSFT(KC_9)
#define SH____0 LSFT(KC_0)

#define SH__GRV LSFT(KC_GRV)
#define SH_MINS LSFT(KC_MINS)
#define SH__EQL LSFT(KC_EQL)
#define SH_LBRC LSFT(KC_LBRC)
#define SH_RBRC LSFT(KC_RBRC)
#define SH_BSLS LSFT(KC_BSLS)
#define SH_QUOT LSFT(KC_QUOT)




enum keycodes {
    GO_LEFT = SAFE_RANGE, // ctrl + left, left desktop, win ctrl <
    GO_RGHT, // ctrl + right, right desktop, win ctrl >
    GO_UP, // ctrl + up, mission control, win tab

    WO_LEFT, // next word
    WO_RGHT, // prev word
    OS_LANG, // change language, ctrl + space at mac, right alt at window
    OS_PSCR,

    MC_LCMD, // work lcmd on mac, lctl on win
    MC_LCTL, // work lctl on mac, lgui on win

    VS_BRCK, // visual studio put break point
    VC_FLDA, // visual studio code fold all
    VC_UFDA, // visual studio code unfold all
    VC_FLDR, // visual studio code fold recursive
    VC_UFDR, // visual studio code unfold recursive

    DRG_SCR, // hold scroll mode
    TOG_SCR, // toggle scroll mode

};


bool set_scrolling = false;

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 12.0
#define SCROLL_DIVISOR_V 12.0

#define MOUSE_DIVISOR_X 0.89
#define MOUSE_DIVISOR_Y 0.89

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0.f;
float scroll_accumulated_v = 0.f;
float mouse_accumulated_x = 0.f;
float mouse_accumulated_y = 0.f;


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        MC_LCMD, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    LO_COMM, RA_DOT,  PT_SLSH, KC_RSFT,
                                   EXTRA2,                    MS_BTN1, MS_BTN3, MS_BTN2,                   EXTRA2,
        EXTRA2,  EXTRA2,  EXTRA1,           KC_LALT, KC_SPC,  LOWER,   DRG_SCR, RAISE,   LOWER,   MC_LCTL,          EXTRA1,  EXTRA2,  EXTRA2
    ),
    [1] = LAYOUT( 
        KC_ESC,  XXXXXXX, KC_7,    KC_8,    KC_9,    KC_0,                               KC_GRV,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        MC_LCMD, XXXXXXX, KC_4,    KC_5,    KC_6,    XXXXXXX,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT, KC_QUOT,
        KC_LSFT, XXXXXXX, KC_1,    KC_2,    KC_3,    XXXXXXX,                            KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, KC_RSFT,
                                   _______,                   _______, _______, _______,                   _______,
        _______, _______, _______,          KC_LALT, KC_SPC,  _______, _______, _______, _______, MC_LCTL,          _______, _______, _______
    ),
    [2] = LAYOUT(
        KC_TAB,  XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,                             XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, OS_PSCR, KC_DEL,
        MC_LCMD, XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11,                             XXXXXXX, KC_RCTL, KC_RSFT, OS_LANG, KC_RGUI, XXXXXXX,
        KC_LSFT, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F12,                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
                                   _______,                   _______, _______, _______,                   _______,
        _______, _______, _______,          KC_LALT, KC_SPC,  _______, _______, _______, _______, MC_LCTL,          _______, _______, _______
    ),
    [3] = LAYOUT(
        KC_ESC,  XXXXXXX, GO_UP,   XXXXXXX, VC_FLDR, VC_UFDR,                            QK_RBT,  QK_BOOT, EE_CLR,  XXXXXXX, XXXXXXX, KC_DEL,
        MC_LCMD, GO_LEFT, XXXXXXX, GO_RGHT, VC_FLDA, VC_UFDA,                            WO_LEFT, XXXXXXX, XXXXXXX, WO_RGHT, XXXXXXX, XXXXXXX,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, VS_BRCK,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
                                   _______,                   _______, _______, _______,                   _______,
        _______, _______, _______,          KC_LALT, KC_SPC,  _______, _______, _______, _______, MC_LCTL,          _______, _______, _______
    ),
    [4] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        MC_LCMD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
                                   _______,                   _______, _______, _______,                   _______,
        _______, _______, _______,          KC_LALT, KC_SPC,  _______, _______, _______, _______, MC_LCTL,          _______, _______, _______
    ),
    [5] = LAYOUT(
        XXXXXXX, XXXXXXX, SH____7, SH____8, SH____9, SH____0,                            SH__GRV, SH_MINS, SH__EQL, SH_LBRC, SH_RBRC, SH_BSLS,
        MC_LCMD, XXXXXXX, SH____4, SH____5, SH____6, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, SH_QUOT, SH_QUOT,
        KC_LSFT, XXXXXXX, SH____1, SH____2, SH____3, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
                                   _______,                   _______, _______, _______,                   _______,
        _______, _______, _______,          KC_LALT, KC_SPC,  _______, _______, _______, _______, MC_LCTL,          _______, _______, _______
    )
};


report_mouse_t pointing_device_task_user(report_mouse_t mouse_report)
{
    if (set_scrolling)
    {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)mouse_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int16_t)scroll_accumulated_h;
        mouse_report.v = (int16_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int16_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int16_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    else
    {
        // Calculate and accumulate mouse movement values based on mouse report
        mouse_accumulated_x += (float)mouse_report.x / MOUSE_DIVISOR_X;
        mouse_accumulated_y += (float)mouse_report.y / MOUSE_DIVISOR_Y;

        // Assign integer parts of accumulated mouse movement values to the mouse report
        mouse_report.x = (int16_t)mouse_accumulated_x;
        mouse_report.y = (int16_t)mouse_accumulated_y;

        // Update accumulated mouse movement values by subtracting the integer parts
        mouse_accumulated_x -= (int16_t)mouse_accumulated_x;
        mouse_accumulated_y -= (int16_t)mouse_accumulated_y;

        // Clear the scroll values of the mouse report
        mouse_report.h = 0;
        mouse_report.v = 0;
    }

    return mouse_report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    os_variant_t host = detected_host_os();
    switch (keycode)
    {
    case OS_LANG:
        if (record->event.pressed)
        {
            if (host == OS_WINDOWS)
            {
                tap_code(KC_RALT);
            }
            else
            {
                register_code(KC_LCTL);
                tap_code(KC_SPACE);
                unregister_code(KC_LCTL);
            }
        }
        return false;
    case OS_PSCR:
        if (host == OS_WINDOWS)
        {
            if (record->event.pressed)
            {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                tap_code(KC_S);
                unregister_code(KC_LGUI);
                unregister_code(KC_LSFT);
            }
        }
        else
        {
            if (record->event.pressed)
            {
                register_code(KC_LGUI);
                register_code(KC_LSFT);
                tap_code(KC_4);
                unregister_code(KC_LGUI);
                unregister_code(KC_LSFT);
            }
        }
        return false;

    case WO_LEFT:
        if (record->event.pressed)
        {
            if (host == OS_WINDOWS)
            {
                register_code(KC_LCTL);
                register_code(KC_LEFT);
                // unregister_code(KC_LCTL);
            }
            else
            {
                register_code(KC_LALT);
                register_code(KC_LEFT);
                // unregister_code(KC_LALT);
            }
        }
        else
        {
            if (host == OS_WINDOWS)
            {
                // register_code(KC_LCTL);
                unregister_code(KC_LEFT);
                unregister_code(KC_LCTL);
            }
            else
            {
                // register_code(KC_LALT);
                unregister_code(KC_LEFT);
                unregister_code(KC_LALT);
            }
        }
        return false;

    case WO_RGHT:
        if (record->event.pressed)
        {
            if (host == OS_WINDOWS)
            {
                register_code(KC_LCTL);
                register_code(KC_RIGHT);
                // unregister_code(KC_LCTL);
            }
            else
            {
                register_code(KC_LALT);
                register_code(KC_RIGHT);
                // unregister_code(KC_LALT);
            }
        }
        else
        {
            if (host == OS_WINDOWS)
            {
                // register_code(KC_LCTL);
                unregister_code(KC_RIGHT);
                unregister_code(KC_LCTL);
            }
            else
            {
                // register_code(KC_LALT);
                unregister_code(KC_RIGHT);
                unregister_code(KC_LALT);
            }
        }

        return false;

    case MC_LCMD:
        if (host == OS_WINDOWS)
        {
            if (record->event.pressed)
                register_code(KC_LCTL);
            else
                unregister_code(KC_LCTL);
        }
        else
        {
            if (record->event.pressed)
                register_code(KC_LGUI);
            else
                unregister_code(KC_LGUI);
        }

        return false;

    case MC_LCTL:
        if (host == OS_WINDOWS)
        {
            if (record->event.pressed)
                register_code(KC_LGUI);
            else
                unregister_code(KC_LGUI);
        }
        else
        {
            if (record->event.pressed)
                register_code(KC_LCTL);
            else
                unregister_code(KC_LCTL);
        }

        return false;

    case GO_LEFT:
        if (host == OS_WINDOWS)
        {
            if (record->event.pressed)
            {
                register_code(KC_LGUI);
                register_code(KC_LCTL);
                tap_code(KC_LEFT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
            }
        }
        else
        {
            if (record->event.pressed)
            {
                register_code(KC_LCTL);
                tap_code(KC_LEFT);
                unregister_code(KC_LCTL);
            }
        }

        return false;

    case GO_RGHT:
        if (host == OS_WINDOWS)
        {
            if (record->event.pressed)
            {
                register_code(KC_LGUI);
                register_code(KC_LCTL);
                tap_code(KC_RIGHT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
            }
        }
        else
        {
            if (record->event.pressed)
            {
                register_code(KC_LCTL);
                tap_code(KC_RIGHT);
                unregister_code(KC_LCTL);
            }
        }

        return false;

    case GO_UP:
        if (host == OS_WINDOWS)
        {
            if (record->event.pressed)
            {
                register_code(KC_LGUI);
                tap_code(KC_TAB);
                unregister_code(KC_LGUI);
            }
        }
        else
        {
            if (record->event.pressed)
            {
                register_code(KC_LCTL);
                tap_code(KC_UP);
                unregister_code(KC_LCTL);
            }
        }
        return false;


    case VS_BRCK:
        if (record->event.pressed)
        {
            if (host == OS_WINDOWS)
            {
                register_code(KC_LCTL);
                register_code(KC_LALT);
                tap_code(KC_PAUS);
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
            }
            else
            {
                tap_code(KC_PAUS);
            }
        }
        return false;

    case VC_FLDA:
        if (record->event.pressed)
        {
            if (host == OS_WINDOWS)
            {
                register_code(KC_LCTL);
                tap_code(KC_K);
                tap_code(KC_0);
                unregister_code(KC_LCTL);
            }
            else
            {
                register_code(KC_LGUI);
                tap_code(KC_K);
                tap_code(KC_0);
                unregister_code(KC_LGUI);
            }
        }
        return false;

    case VC_UFDA:
        if (record->event.pressed)
        {
            if (host == OS_WINDOWS)
            {
                register_code(KC_LCTL);
                tap_code(KC_K);
                tap_code(KC_J);
                unregister_code(KC_LCTL);
            }
            else
            {
                register_code(KC_LGUI);
                tap_code(KC_K);
                tap_code(KC_J);
                unregister_code(KC_LGUI);
            }
        }
        return false;

    case VC_FLDR:
        if (record->event.pressed)
        {
            if (host == OS_WINDOWS)
            {
                register_code(KC_LCTL);
                tap_code(KC_K);
                tap_code(KC_LBRC);
                unregister_code(KC_LCTL);
            }
            else
            {
                register_code(KC_LGUI);
                tap_code(KC_K);
                tap_code(KC_LBRC);
                unregister_code(KC_LGUI);
            }
        }
        return false;

    case VC_UFDR:
        if (record->event.pressed)
        {
            if (host == OS_WINDOWS)
            {
                register_code(KC_LCTL);
                tap_code(KC_K);
                tap_code(KC_RBRC);
                unregister_code(KC_LCTL);
            }
            else
            {
                register_code(KC_LGUI);
                tap_code(KC_K);
                tap_code(KC_RBRC);
                unregister_code(KC_LGUI);
            }
        }

        return false;

    case DRG_SCR:
        set_scrolling = record->event.pressed;
        return false;

    case TOG_SCR:
        if (record->event.pressed)
            set_scrolling = !set_scrolling;
        return false;


    }

    return true;
}