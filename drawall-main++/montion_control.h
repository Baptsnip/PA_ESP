/* motion_control.h - Déclarations pour le mouvement du traceur vertical */

#ifndef MOTION_CONTROL_H
#define MOTION_CONTROL_H

#include <stdint.h>

void compute_belt_lengths(float x, float y, float *L1, float *L2);
void mc_line(float x, float y, float feed_rate);
void interpolate_line(float x0, float y0, float x1, float y1, float feed_rate);

#endif
