/*
 * screen.c
 *
 * Generic screen manipulation routines. Most of these routines call the machine
 * specific routines to do the actual work.
 */

#include "ztypes.h"

/*
 * z_set_window
 *
 * Put the cursor in the text or status window. The cursor is free to move in
 * the status window, but is fixed to the input line in the text window.
 */
void z_set_window( zword_t w ) {
   flush_buffer( false );
   screen_window = w;

   if ( screen_window == STATUS_WINDOW ) {
      /* Status window: disable formatting and select status window */
      formatting = OFF;
      select_status_window(  );
   } else {
      /* Text window: enable formatting and select text window */
      select_text_window(  );
      formatting = ON;
   }
}                               /* z_set_window */

/*
 * z_split_window
 *
 * Set the size of the status window. The default size for the status window is
 * zero lines for both type 3 and 4 games. The status line is handled specially
 * for type 3 games and always occurs the line immediately above the status
 * window.
 */
void z_split_window( zword_t lines ) {
   /* Maximum status window size is 255 */
   lines &= 0xff;

   /* The top line is always set for V1 to V3 games, so account for it here. */
   lines += 1;

   if ( lines ) {
      /* Bound the status size to one line less than the total screen height */
      if ( lines > ( zword_t ) ( screen_rows - 1 ) )
         status_size = ( zword_t ) ( screen_rows - 1 );
      else
         status_size = lines;

      /* Need to clear the status window for type 3 games */
      z_erase_window( STATUS_WINDOW );
   } else {
      /* Reset the status size */
      status_size = 0;

      /* Return cursor to text window */
      select_text_window(  );
   }

}                               /* z_split_window */

/*
 * z_erase_window
 *
 * Clear one or all windows on the screen.
 */
void z_erase_window( zword_t w ) {
   flush_buffer( true );

   if ( ( zbyte_t ) w == ( zbyte_t ) Z_SCREEN ) {
      clear_screen(  );
   } else if ( ( zbyte_t ) w == TEXT_WINDOW ) {
      clear_text_window(  );
   } else if ( ( zbyte_t ) w == STATUS_WINDOW ) {
      /* No status window on this platform */
   }
}                               /* z_erase_window */

/*
 * z_erase_line
 *
 * Clear one line on the screen.
 */
void z_erase_line( zword_t flag ) {
   /* Nothing on this platform */
}                               /* z_erase_line */

/*
 * z_set_cursor
 *
 * Set the cursor position in the status window only.
 */
void z_set_cursor( zword_t row, zword_t column ) {
   /* Nothing on this platform */
}                               /* z_set_cursor */

/*
 * z_show_status
 *
 * Format and output the status line for type 3 games only.
 *
 */
void z_show_status( void ) {
   /* No status line on this platform */
}                               /* z_show_status */

/*
 * output_string
 *
 * Output a string of characters.
 */
void output_string( const char *s ) {
   while ( *s )
      output_char( *s++ );
}                               /* output_string */

/*
 * output_line
 *
 * Output a string of characters followed by a new line.
 */
void output_line( const char *s ) {
   output_string( s );
   output_new_line(  );
}                               /* output_line */

/*
 * output_char
 *
 * Output a character.
 */
void output_char( int c ) {
   /* If output is enabled then either select the rendition attribute
    * or just display the character */
   if ( outputting == ON ) {
      display_char( (unsigned int)(c & 0xff) );
   }
}                               /* output_char */

/*
 * output_new_line
 *
 * Scroll the text window up one line and pause the window if it is full.
 */
void output_new_line( void ) {
   /* Don't print if output is disabled or replaying commands */
   if ( outputting == ON ) {
      /* If this is the status window then just output a new line */
      output_char( '\n' );
   }
}                               /* output_new_line */

/*
 * z_print_table
 *
 * Writes text into a rectangular window on the screen.
 *
 *    argv[0] = start of text address
 *    argv[1] = rectangle width
 *    argv[2] = rectangle height (default = 1)
 *
 * FIXME: Could do better than this for dumb IO
 */
void z_print_table( int argc, zword_t * argv ) {
   unsigned long address;
   unsigned int width, height;

   /* Supply default arguments */
   if ( argc < 3 )
      argv[2] = 1;

   /* Don't do anything if the window is zero high or wide */
   if ( argv[1] == 0 || argv[2] == 0 )
      return;

   /* Get coordinates of top left corner of rectangle */
   address = argv[0];

   /* Write text in width * height rectangle */
   for ( height = 0; height < argv[2]; height++ ) {

      for ( width = 0; width < argv[1]; width++ )
         write_char( read_data_byte( &address ) );
   }
}                               /* z_print_table */

/*
 * z_set_colour
 *
 * Set the colour of the screen. Colour can be set on four things:
 *    Screen background
 *    Text typed by player
 *    Text written by game
 *    Graphics characters
 *
 * Colors can be set to 1 of 9 values:
 *    1 = machine default (IBM/PC = blue background, everything else white)
 *    2 = black
 *    3 = red
 *    4 = green
 *    5 = brown
 *    6 = blue
 *    7 = magenta
 *    8 = cyan
 *    9 = white
 */
void z_set_colour( zword_t foreground, zword_t background ) {
   if ( ( zint_t ) foreground < -1 || ( zint_t ) foreground > 9 || ( zint_t ) background < -1 ||
        ( zint_t ) background > 9 )
      fatal( "Bad colour!" );

   flush_buffer( false );
   /* Nothing else to do on this platform */
}                               /* z_set_colour */
