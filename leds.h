#ifndef LEDS_H_
#define LEDS_H_

typedef enum {
    LED_STATE_STOP,
    LED_STATE_SLOW,
    LED_STATE_NORMAL,
    LED_STATE_TURN_L,
    LED_STATE_TURN_R,
    LED_STATE_TIMEOUT
} LedState_t;

void Leds_Init(void);
void Update_LED(LedState_t state);
void Hardware_Init_All(void);

#endif
