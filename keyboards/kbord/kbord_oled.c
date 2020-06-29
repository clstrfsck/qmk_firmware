#include <math.h>
#include <stdio.h>

#include "kbord.h"
#include "oled_driver.h"
#include "oled_extra.h"

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    print("oled_init_user\n");
    palSetPadMode(GPIOA, 0, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(GPIOA, 0);
    chThdSleepMilliseconds(10);
    palSetPad(GPIOA, 0);
    chThdSleepMilliseconds(20);
    return rotation;
}

uint16_t seq = 0;
bool vertical = true;

void oled_task_user(void) {
#if 0
    if (vertical) {
        uint16_t line_off = ((seq - 1) % 128) + 2;
        oled_clear_vline(line_off, 0, 63);
        uint16_t line_on = (seq % 128) + 2;
        oled_draw_vline(line_on, 0, 63);
        if (++seq >= 128) {
            vertical = false;
            seq = 0;
        }
    } else {
        uint16_t line_off = (seq - 1) % 64;
        oled_clear_hline(2, 129, line_off);
        uint16_t line_on = seq % 64;
        oled_draw_hline(2, 129, line_on);
        if (++seq >= 64) {
            vertical = true;
            seq = 0;
        }
    }
#elif 0
    oled_draw_line(2, 0, 129, 0);
    oled_draw_line(2, 63, 129, 63);
    oled_draw_line(2, 0, 2, 63);
    oled_draw_line(129, 0, 129, 63);

    oled_draw_line(2, 0, 129, 63);
    oled_draw_line(2, 63, 129, 0);
#elif 0
    double angledeg = seq % 360;
    double anglerad = angledeg * M_PI / 180.0;
    int16_t halfwidth = OLED_DISPLAY_WIDTH / 2.0;
    int16_t halfheight = OLED_DISPLAY_HEIGHT / 2.0;
    double xvect = cos(anglerad) * halfwidth;
    double yvect = sin(anglerad) * halfheight;

    oled_clear();
    oled_draw_line(halfwidth, halfheight, (int16_t)(halfwidth + xvect), (int16_t)(halfheight + yvect));
    seq += 1;
#else
    oled_clear();
    for (int i = 0; i < 8; ++i) {
        char buf[20];
        sprintf(buf, "H%03dI\n", i);
        oled_write(buf, i & 1);
    }
#endif
}
#endif
