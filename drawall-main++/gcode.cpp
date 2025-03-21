/* gcode.c - Interprétation du G-code */

#include "grbl.h"
#include "motion_control.h"
#include "gcode.h"

static float last_x = 0.0, last_y = 0.0;

void gcode_execute_line(char *line) {
    float x, y, feed_rate;
    if (parse_gcode(line, &x, &y, &feed_rate)) {
        interpolate_line(last_x, last_y, x, y, feed_rate);
        last_x = x;
        last_y = y;
    }
}

bool parse_gcode(char *line, float *x, float *y, float *feed_rate) {
    sscanf(line, "G1 X%f Y%f F%f", x, y, feed_rate);
    return true;
}
