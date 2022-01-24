/*
 * fakefileio.c
 *
 * Stuff that looks like file IO, but comes from memory.
 */
#include "ztypes.h"

/* Static data */
extern int GLOBALVER;

static const zbyte_t file_data[] = {
#include "advent.h"
};
static const long file_size = sizeof(file_data) / sizeof(file_data[0]);

/*
 * read_page
 *
 * Read one game file page.
 */
void read_page( int page, void *buffer ) {
   /* Calculate start of page */
   long read_offset = (long) page * PAGE_SIZE;

   /* Read the page */
   if (read_offset < file_size) {
      unsigned long available = file_size - read_offset;
      unsigned to_read = (available > PAGE_SIZE) ? PAGE_SIZE : (unsigned) available;
      memcpy(buffer, file_data + read_offset, to_read);
   }
}                               /* read_page */

/*
 * read_page
 *
 * Read one game file page.
 */
const zbyte_t *read_page_ptr( int page ) {
   /* Calculate start of page */
   long read_offset = (long) page * PAGE_SIZE;
   return read_offset >= file_size
      ? NULL
      : file_data + read_offset;
}                               /* read_page_ptr */

/*
 * z_verify
 *
 * Verify game ($verify verb). Add all bytes in game file except for bytes in
 * the game file header.
 */
void z_verify( void ) {
   zword_t checksum = 0;

   /* Print version banner */
   z_new_line(  );
   write_string( "Running on " );
   write_string( JZIPVER );
   write_string( ". Reporting spec " );
   write_int( get_byte( H_STANDARD_HIGH ) );
   write_char( '.' );
   write_int( get_byte( H_STANDARD_LOW ) );
   write_string( " compliance." );
   z_new_line(  );

   write_string( "Release " );
   write_string( JZIPRELDATE );
   write_string( "." );
   z_new_line(  );

   write_string( "Playing a version " );
   z_print_num( (zword_t) GLOBALVER );
   write_string( " story." );
   z_new_line(  );

   z_new_line(  );

   /* Calculate game file dimensions */
   for (long i = 64L; i < file_size; ++i) {
      checksum += file_data[i];
   }

   /* Make a conditional jump based on whether the checksum is equal */
   conditional_jump( checksum == h_checksum );
}                               /* z_verify */


/*
 * z_save
 *
 * Saves data to disk. Returns:
 *     0 = save failed
 *     1 = save succeeded
 *
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int z_save( int argc, zword_t table, zword_t bytes, zword_t name ) {
#pragma GCC diagnostic pop
   /* Return result of save to Z-code */
   conditional_jump( 1 );
   return 0;
}                               /* z_save */


/*
 * z_restore
 *
 * Restore game state from disk. Returns:
 *     0 = restore failed
 *     2 = restore succeeded
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
int z_restore( int argc, zword_t table, zword_t bytes, zword_t name ) {
#pragma GCC diagnostic pop
   conditional_jump( 1 );
   return 0;
}                               /* z_restore */

/*
 * z_save_undo
 *
 * Save the current Z machine state in memory for a future undo. Returns:
 *    -1 = feature unavailable
 *     0 = save failed
 *     1 = save succeeded
 */
void z_save_undo( void ) {
   /* Not doing this on this platform */
   store_operand( ( zword_t ) - 1 );
}                               /* z_save_undo */


/*
 * z_restore_undo
 *
 * Restore the current Z machine state from memory. Returns:
 *    -1 = feature unavailable
 *     0 = restore failed
 *     2 = restore succeeded
 */
void z_restore_undo( void ) {
   /* Not doing this on this platform */
   store_operand( ( zword_t ) -1 );
}                               /* z_restore_undo */


/*
 * z_input_stream
 *
 * Take input from command file instead of keyboard.
 *
 */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void z_input_stream( int arg ) {
#pragma GCC diagnostic pop
   /* Nothing to do on this platform */
}                               /* z_input_stream */
