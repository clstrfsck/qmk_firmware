/* minio.c
 *
 * Smallest possible IO stuff.
 */
#include "ztypes.h"
#include "platform.h"

static bool status_mode = false;

static int inc( void ) {
   int c = inchar(  );
   if ( c < 0 ) {
      write_string( "\nEOT\n" );
      flush_buffer( false );
      return 0;
   }
   return c;
}

void initialize_screen( void ) {
   status_mode = false;
}                               /* initialize_screen */

void restart_screen( void ) {
   zbyte_t high = 1, low = 0;

   set_byte( H_STANDARD_HIGH, high );
   set_byte( H_STANDARD_LOW, low );

   set_byte( H_CONFIG, ( get_byte( H_CONFIG ) | CONFIG_WINDOWS ) );

   /* Force graphics off as we can't do them */
   set_word( H_FLAGS, ( get_word( H_FLAGS ) & ( ~GRAPHICS_FLAG ) ) );
}                               /* restart_screen */

void reset_screen( void ) {
   select_text_window(  );
}                               /* reset_screen */

void clear_screen( void ) {
   outchar( '\n' );
}                               /* clear_screen */

void select_status_window( void ) {
   status_mode = true;
}                               /* select_status_window */

void select_text_window( void ) {
   status_mode = false;
}                               /* select_text_window */

void clear_text_window( void ) {
   clear_screen(  );
}                               /* clear_text_window */

void display_char( int c ) {
   if (!status_mode) {
      outchar( c );
   }
}                               /* display_char */

int input_character( void ) {
   int c = inc(  );

   /* Bureaucracy expects CR, not NL.  */
   return ( ( c == '\n' ) ? '\r' : c );
}                               /* input_character */

int input_line( int buflen, char *buffer, int *read_size ) {
   int c;

   *read_size = 0;

   for ( c = inc(  ); c != '\n' && c != 0; c = inc(  ) ) {
      if ( *read_size < buflen ) {
         buffer[( *read_size )++] = c;
      }
   }
   return c;
}                               /* input_line */
