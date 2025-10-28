#include "leds.h"
#include "ultrasonic.h"
#include "motors.h"
#include "logger.h"

void Leds_Init(void) {}
void Update_LED(LedState_t state) { (void)state; }

void Hardware_Init_All(void)
{
    Ultrasonic_Init();
    Motors_Init();
    Leds_Init();
    Logger_Init();
}
