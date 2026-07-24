#ifndef KEYMAP_H
#define KEYMAP_H

/**
 * @file KeyMap.h
 * @brief Physical matrix to logical character mapping.
 */

// Define functional keys
#define KEY_BACKSPACE "\b"
#define KEY_ENTER     "\n"
#define KEY_SPACE     " "
#define KEY_MODE      "MODE"
#define KEY_LAYER     "LAYER"  // Toggle Alphabet/Symbol
#define KEY_SHIFT     "SHIFT"  // Toggle Case
#define KEY_UP        "UP"
#define KEY_DOWN      "DOWN"
#define KEY_SCAN      "SCAN"
#define KEY_CLEAR     "CLEAR"
#define KEY_BATTERY   "BATTERY"
#define KEY_ZOOM_IN   "ZOOM+"
#define KEY_ZOOM_OUT  "ZOOM-"

// 6 Rows x 9 Columns Matrix
// This matches your original hardware layout

const char* ALPHABET_MAP[6][9] = {
    { nullptr, nullptr, nullptr, nullptr, "p",   "5",    KEY_BATTERY, KEY_SPACE,   nullptr },
    { "n",     "k",     "m",     "j",     "o",   "4",    KEY_SCAN,    KEY_CLEAR,   KEY_MODE },
    { "b",     "h",     "l",     "u",     "i",   "3",    "9",         KEY_ZOOM_IN, KEY_UP },
    { "v",     "g",     "t",     "y",     "e",   "2",    "8",         KEY_DOWN,    KEY_ZOOM_OUT },
    { "c",     "f",     "s",     "r",     "z",   "1",    "7",         KEY_SHIFT,   KEY_BACKSPACE },
    { "x",     "d",     "w",     "q",     "a",   "0",    "6",         KEY_LAYER,   KEY_ENTER }
};

const char* SYMBOL_MAP[6][9] = {
    { nullptr, nullptr, nullptr, nullptr, "@",   "%",    KEY_BATTERY, KEY_SPACE,   nullptr },
    { "=",     "-",     "/",     KEY_BACKSPACE, "_", "|", KEY_SCAN,    KEY_CLEAR,   KEY_MODE },
    { "^",     "+",     "*",     KEY_ENTER, ")",   "!",    "<",         KEY_ZOOM_IN, KEY_UP },
    { KEY_SPACE, "3",     "6",     "9",     "(",   "?",    ">",         KEY_DOWN,    KEY_ZOOM_OUT },
    { ".",     "2",     "5",     "8",     "'",   ",",    ":",         KEY_SHIFT,   KEY_BACKSPACE },
    { "0",     "1",     "4",     "7",     "\"",  ".",    "&",         KEY_LAYER,   KEY_ENTER }
};

#endif // KEYMAP_H
