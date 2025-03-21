/* planner.c - Planification des mouvements */

#include "grbl.h"
#include "planner.h"

void plan_line(int32_t steps_L1, int32_t steps_L2, float feed_rate) {
    plan_line_data_t pl_data;
    pl_data.target[L1_AXIS] = steps_L1;
    pl_data.target[L2_AXIS] = steps_L2;
    pl_data.feed_rate = feed_rate;
    plan_buffer_line_steps(&pl_data);
}
