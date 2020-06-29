#include "kbord.h"

#include "ch.h"
#include "hal.h"

#ifdef QWIIC_MICRO_OLED_ENABLE
#include "micro_oled.h"
#include "qwiic.h"
#endif

void matrix_scan_kb(void) {
#ifdef QWIIC_MICRO_OLED_ENABLE
    draw_ui();
#endif
}
