#include "motors.h"
#include "ultrasonic.h"
#include "leds.h"

#define SPEED_STOP    0
#define SPEED_SLOW   40
#define SPEED_NORMAL 70
#define SPEED_TURN   50

#define DIST_STOP_FRONT 200
#define DIST_SLOW_FRONT 500
#define DIST_TURN_SIDE  300

void Motors_Init(void) {}

void Set_Motors(MotorCommand_t *cmd)
{
    (void)cmd;
}

void Decision_Logic(SensorData_t *d, MotorCommand_t *cmd, LedState_t *led)
{
    cmd->left_speed = cmd->right_speed = SPEED_NORMAL;
    *led = LED_STATE_NORMAL;

    if (d->front_dist < DIST_STOP_FRONT)
    {
        if(d->left_dist > d->right_dist)
        {
            cmd->left_speed = -SPEED_TURN;
            cmd->right_speed = SPEED_TURN;
            *led = LED_STATE_TURN_L;
        }
        else
        {
            cmd->left_speed = SPEED_TURN;
            cmd->right_speed = -SPEED_TURN;
            *led = LED_STATE_TURN_R;
        }
    }
    else if(d->front_dist < DIST_SLOW_FRONT)
    {
        cmd->left_speed = cmd->right_speed = SPEED_SLOW;
        *led = LED_STATE_SLOW;
    }
}
