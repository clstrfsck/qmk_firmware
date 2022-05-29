/*
 * Make sure condition variables are available.
 */

#pragma once

#define CH_CFG_USE_MUTEXES TRUE
#define CH_CFG_USE_PIPES TRUE

#include_next <chconf.h>
