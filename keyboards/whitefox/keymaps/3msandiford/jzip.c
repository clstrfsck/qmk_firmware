/*
 * jzip.c
 * see ``LICENSE'' file for license information.
 *
 * Z code interpreter main routine.
 */
#include "ztypes.h"
#include "platform.h"

extern int GLOBALVER;

static void configure( zbyte_t, zbyte_t );

/*
 * start
 *
 * Initialise environment, start interpreter, clean up.
 */
void start( void ) {
   configure( V1, V3 );
   initialize_screen(  );
   load_cache(  );
   z_restart(  );
   interpret(  );
   unload_cache(  );
   reset_screen(  );
   finished( true );
}                               /* main */

/*
 * configure
 *
 * Initialise global and type specific variables.
 */
static void configure( zbyte_t min_version, zbyte_t max_version ) {
   // FIXME: dodgy const cast
   datap = (zbyte_t *) read_page_ptr( 0 );

   h_type = get_byte( H_TYPE );

   GLOBALVER = h_type;

   if ( h_type < min_version || h_type > max_version ||
        ( get_byte( H_CONFIG ) & CONFIG_BYTE_SWAPPED ) ) {
      fatal( "Wrong game or version" );
   }

   story_scaler = 2;
   property_mask = P3_MAX_PROPERTIES - 1;
   property_size_mask = 0xe0;

   h_config = get_byte( H_CONFIG );
   h_version = get_word( H_VERSION );
   h_data_size = get_word( H_DATA_SIZE );
   h_start_pc = get_word( H_START_PC );
   h_words_offset = get_word( H_WORDS_OFFSET );
   h_objects_offset = get_word( H_OBJECTS_OFFSET );
   h_globals_offset = get_word( H_GLOBALS_OFFSET );
   h_restart_size = get_word( H_RESTART_SIZE );
   h_flags = get_word( H_FLAGS );
   h_synonyms_offset = get_word( H_SYNONYMS_OFFSET );
   h_checksum = get_word( H_CHECKSUM );
   h_alternate_alphabet_offset = get_word( H_ALTERNATE_ALPHABET_OFFSET );

   datap = NULL;
}                               /* configure */
