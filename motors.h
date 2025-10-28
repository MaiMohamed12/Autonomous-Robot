#ifndef MOTORS_H_
#define MOTORS_H_

#include <stdint.h>

typedef struct {
    int16_t left_speed;
    int16_t right_speed;
} MotorCommand_t;

void Motors_Init(void);
void Set_Motors(MotorCommand_t *cmd);
void Decision_Logic(SensorData_t *d, MotorCommand_t *cmd, LedState_t *led);

#endif
