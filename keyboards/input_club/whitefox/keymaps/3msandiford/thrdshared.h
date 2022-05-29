#pragma once

// Code and data structures shared by game and QMK threads

#include <stdint.h>

#include "ch.h"

// Can be called from any thread to start game thread
void qmk_start_game_thread(void);

// Can be called from any thread to check if game running
// Needs game mutex locked
bool game_thread_running(void);

// Lock the game mutex
void lock_game_mutex(void);
void unlock_game_mutex(void);

// Shared input (QMK -> game)
#define INPUT_BUFFER_SIZE 32
extern pipe_t qmk_input_pipe;

// Shared output (game -> QMK)
#define OUTPUT_BUFFER_SIZE 32
extern pipe_t qmk_output_pipe;
