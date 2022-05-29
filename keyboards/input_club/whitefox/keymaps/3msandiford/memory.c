/*
 * memory.c
 *
 * Code and data caching routines
 */
#include "ztypes.h"

/* Static data storage to maximum size */
#define MAX_DATA_SIZE (18 * 1024)
static zbyte_t data_area[ MAX_DATA_SIZE ];

static unsigned int calc_data_pages( void );

/*
 * load_cache
 *
 * Not really doing caching here, as the full game is in memory.
 */
void load_cache( void ) {
   /* Calculate dynamic cache pages required */
   unsigned int data_pages = ( h_config & CONFIG_MAX_DATA )
      ? calc_data_pages(  )
      : ( h_data_size + PAGE_MASK ) >> PAGE_SHIFT;
   data_size = data_pages * PAGE_SIZE;

   if ( data_size > MAX_DATA_SIZE ) {
      fatal( "This game requires too much memory to play on this machine" );
   }

   /* Allocate static data area and initialise it */
   datap = data_area;
   for ( unsigned int i = 0; i < data_pages; i++ ) {
      read_page( i, datap + (i * PAGE_SIZE) );
   }
}                               /* load_cache */

/*
 * unload_cache
 *
 * Deallocate cache and other memory objects.
 */
void unload_cache( void ) {
   /* Make sure all output has been flushed */
   z_new_line(  );
}                               /* unload_cache */

/*
 * read_code_word
 *
 * Read a word from the instruction stream.
 */
zword_t read_code_word( void ) {
   return ( ( zword_t ) read_code_byte(  ) << 8 )
      | ( ( zword_t ) read_code_byte(  ) );
}                               /* read_code_word */

/*
 * read_code_byte
 *
 * Read a byte from the instruction stream.
 */
zbyte_t read_code_byte( void ) {
   unsigned int page_number, page_offset;

   /* Calculate page and offset values */
   page_number = ( unsigned int ) ( pc >> PAGE_SHIFT );
   page_offset = ( unsigned int ) pc & PAGE_MASK;

   const zbyte_t *page_ptr = read_page_ptr( page_number );

   /* Return byte from page offset */
   if ( !page_ptr ) {
      fatal( "read_code_byte(): read from non-existant page!" );
   }

   /* Update the PC */
   pc++;

   return ( page_ptr[ page_offset ] );
}                               /* read_code_byte */

/*
 * read_data_word
 *
 * Read a word from the data area.
 */
zword_t read_data_word( unsigned long *addr ) {
   return ( ( zword_t ) read_data_byte( addr ) << 8 )
      | ( ( zword_t ) read_data_byte( addr ) );
}                               /* read_data_word */

/*
 * read_data_byte
 *
 * Read a byte from the data area.
 */
zbyte_t read_data_byte( unsigned long *addr ) {
   zbyte_t value;

   /* Check if byte is in non-paged cache */
   if ( *addr < ( unsigned long ) data_size ) {
      value = datap[*addr];
   } else {
      /* Calculate page and offset values */
      unsigned int page_number = ( int ) ( *addr >> PAGE_SHIFT );
      unsigned int page_offset = ( int ) *addr & PAGE_MASK;
      const zbyte_t *page_ptr = read_page_ptr( page_number );
      if ( page_ptr ) {
         value = page_ptr[ page_offset ];
      } else {
         fatal( "read_data_byte(): Fetching data from invalid page!" );
      }
   }

   /* Update the address */
   ( *addr ) += 1;

   return ( value );
}                               /* read_data_byte */

/*
 * calc_data_pages
 *
 * Compute the best size for the data area cache. Some games have the data size
 * header parameter set too low. This causes a write outside of data area on
 * some games. To alleviate this problem the data area size is set to the
 * maximum of the restart size and the data size.
 */
static unsigned int calc_data_pages( void ) {
   unsigned long data_end;

   /* Calculate end of data area, use restart size if data size is too low */
   if ( h_data_size > h_restart_size ) {
      data_end = h_data_size;
   } else {
      data_end = h_restart_size;
   }

   return ( unsigned int ) ( ( data_end + PAGE_MASK ) >> PAGE_SHIFT );
}                               /* calc_data_pages */
