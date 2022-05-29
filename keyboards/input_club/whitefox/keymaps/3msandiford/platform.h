#ifndef INCLUDE_PLATFORM_H
#define INCLUDE_PLATFORM_H

#include <stdbool.h>

void start( void );
void finished( bool success )  __attribute__ ((noreturn));
void init_random( void );
void set_random_seed( unsigned int seed );
unsigned int get_random( unsigned int max );

int inchar( void );
void outchar( int ch );

#endif // INCLUDE_PLATFORM_H
