/*
 * extern.c
 * see ``LICENSE'' file for license information.
 *
 * Global data.
 */
#include "ztypes.h"

int GLOBALVER;

/* Game header data */
zbyte_t h_type = 0;
zbyte_t h_config = 0;
zword_t h_version = 0;
zword_t h_data_size = 0;
zword_t h_start_pc = 0;
zword_t h_words_offset = 0;
zword_t h_objects_offset = 0;
zword_t h_globals_offset = 0;
zword_t h_restart_size = 0;
zword_t h_flags = 0;
zword_t h_synonyms_offset = 0;
zword_t h_file_size = 0;
zword_t h_checksum = 0;
zbyte_t h_interpreter = INTERP_MSDOS;
zbyte_t h_interpreter_version = 'B'; /* Interpreter version 2 */
zword_t h_alternate_alphabet_offset = 0;

/* Game version specific data */
int story_scaler = 0;
int property_mask = 0;
int property_size_mask = 0;

/* Stack and PC data */
zword_t stack[STACK_SIZE];
zword_t sp = STACK_SIZE;
zword_t fp = STACK_SIZE - 1;
zword_t frame_count = 0;        /* frame pointer for get_fp */
unsigned long pc = 0;
int interpreter_state = RUN;
int interpreter_status = 0;

/* Data region data */
unsigned int data_size = 0;
zbyte_t *datap = NULL;


/* Screen size data */
const int screen_rows = DEFAULT_ROWS;
const int screen_cols = DEFAULT_COLS;
const int right_margin = DEFAULT_RIGHT_MARGIN;

/* Current window data */
int screen_window = TEXT_WINDOW;
int interp_initialized = 0;

/* Formatting and output control data */
int formatting = ON;
int outputting = ON;

/* Text output buffer data */
int status_size;
int status_pos = 0;

/* Fixed buffer data */
char line[DEFAULT_COLS + 1];
char status_line[DEFAULT_COLS + 1];

/* Character translation tables */

char lookup_table[3][26];
