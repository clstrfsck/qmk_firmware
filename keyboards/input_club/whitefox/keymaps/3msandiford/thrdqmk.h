#pragma once

#include "quantum.h"

// Called from QMK thread to start game
void qmk_start_game(void);

// Called from QMK thread to process keyboard input
bool qmk_process_input(uint16_t keycode, keyrecord_t *record);

// Called from QMK thread to process game output
void qmk_process_output(void);
