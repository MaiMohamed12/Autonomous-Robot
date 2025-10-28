#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include <stdint.h>

#define TIMEOUT_VAL 0xFFFFFFFFU

typedef struct {
    uint32_t front_dist;
    uint32_t left_dist;
    uint32_t right_dist;
} SensorData_t;

void Ultrasonic_Init(void);
uint32_t Read_Distance_Front(void);
uint32_t Read_Distance_Left(void);
uint32_t Read_Distance_Right(void);

#endif
