/* planner.h - Déclarations pour la planification des mouvements */

#ifndef PLANNER_H
#define PLANNER_H

#include <stdint.h>

void plan_line(int32_t steps_L1, int32_t steps_L2, float feed_rate);

#endif
