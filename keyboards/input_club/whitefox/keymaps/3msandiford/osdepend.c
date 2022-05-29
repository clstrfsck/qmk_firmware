/*
 * osdepend.c
 *
 * All non screen specific operating system dependent routines.
 *
 * Olaf Barthel 28-Jul-1992
 * Modified John Holder(j-holder@home.com) 25-July-1995
 * Support for standalone storyfiles by Magnu Olsson (mol@df.lth.se) Nov.1995
 */
#include "ztypes.h"
#include "platform.h"

/*
 * sound
 *
 * Play a sound file or a note.
 *
 * argc = 1: argv[0] = note# (range 1 - 3)
 *
 *           Play note.
 *
 * argc = 2: argv[0] = 0
 *           argv[1] = 3
 *
 *           Stop playing current sound.
 *
 * argc = 2: argv[0] = 0
 *           argv[1] = 4
 *
 *           Free allocated resources.
 *
 * argc = 3: argv[0] = ID# of sound file to replay.
 *           argv[1] = 2
 *           argv[2] = Volume to replay sound with, this value
 *                     can range between 1 and 8.
 *
 * argc = 4: argv[0] = ID# of sound file to replay.
 *           argv[1] = 2
 *           argv[2] = Control information
 *           argv[3] = Volume information
 *
 *           Volume information:
 *
 *               0x34FB -> Fade sound in
 *               0x3507 -> Fade sound out
 *               other  -> Replay sound at maximum volume
 *
 *           Control information:
 *
 *               This word is divided into two bytes,
 *               the upper byte determines the number of
 *               cycles to play the sound (e.g. how many
 *               times a clock chimes or a dog barks).
 *               The meaning of the lower byte is yet to
 *               be discovered :)
 *
 */
void sound( int argc, zword_t * argv ) {
   /* Supply default parameters */
   if ( argc < 4 )
      argv[3] = 0;
   if ( argc < 3 )
      argv[2] = 0xff;
   if ( argc < 2 )
      argv[1] = 2;

   /* Generic bell sounder */
   if ( argc == 1 || argv[1] == 2 )
      display_char( '\007' );
}                               /* sound */


/*
 * fatal
 *
 * Display message and stop interpreter.
 */
void fatal( const char *s ) {
   reset_screen(  );
   write_string( "\nFatal error: " );
   write_string( s );
   write_string( " (PC = " );
   write_int( pc );
   write_string( ")\n" );
   flush_buffer( true );
   finished( false );
}                               /* fatal */

/*
 * fit_line
 *
 * This routine determines whether a line of text will still fit
 * on the screen.
 *
 * line : Line of text to test.
 * pos  : Length of text line (in characters).
 * max  : Maximum number of characters to fit on the screen.
 */
int fit_line( int pos, int max ) {
   return ( pos < max );
}                               /* fit_line */
