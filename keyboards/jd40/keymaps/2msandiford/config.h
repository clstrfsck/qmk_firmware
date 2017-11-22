#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define KEYMAP_RAW(                                                 \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12,     \
    K13, K14, K15, K16, K17, K18, K19, K20, K21, K22, K23,          \
    K24, K25, K26, K27, K28, K29, K30, K31, K32, K33, K34,          \
    K35, K36, K37, K38, K39, K40, K41, K42, K43, K44                \
    ) {                                                             \
	{ K01,K02,K03,K04,K05,K06,K07,K08,K09,K10,K11,K12 },        \
	{ K13, K14,K15,K16,K17,K18,K19,K20,K21,K22,K23,    KC_NO }, \
	{ K24,   K25,K26,K27,K28,K29,K30,K31,K32,K33,K34,  KC_NO }, \
	{ K35,K36,K37,K38, K39,KC_NO,K40, K41,K42,K43,K44, KC_NO }  \
    }

// Have left and right side modifiers in different layers on the same keys
#define PREVENT_STUCK_MODIFIERS

// Not sure why this isn't default
#define PERMISSIVE_HOLD

#endif
