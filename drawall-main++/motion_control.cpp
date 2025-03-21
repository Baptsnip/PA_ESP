/* motion_control.c - Gestion du mouvement pour le traceur vertical */

#include "grbl.h"
#include "motion_control.h"

// Fonction pour convertir (X, Y) en longueurs de courroies (L1, L2)
void compute_belt_lengths(float x, float y, float *L1, float *L2) {
    *L1 = sqrt(x * x + y * y);
    *L2 = sqrt((DISTANCE_MOTEURS - x) * (DISTANCE_MOTEURS - x) + y * y);
}

void mc_line(float x, float y, float feed_rate) {
    float L1, L2;
    compute_belt_lengths(x, y, &L1, &L2);
    int32_t steps_L1 = (int32_t)(L1 * PAS_PAR_MM);
    int32_t steps_L2 = (int32_t)(L2 * PAS_PAR_MM);
    plan_line(steps_L1, steps_L2, feed_rate);
}

void interpolate_line(float x0, float y0, float x1, float y1, float feed_rate) {
    float dx = x1 - x0;
    float dy = y1 - y0;
    float dist = sqrt(dx * dx + dy * dy);
    int steps = (int)(dist / INTERPOLATION_STEP);
    for (int i = 0; i <= steps; i++) {
        float t = (float)i / steps;
        float x = x0 + t * dx;
        float y = y0 + t * dy;
        mc_line(x, y, feed_rate);
    }
}
