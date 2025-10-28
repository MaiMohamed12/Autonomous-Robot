#include "ultrasonic.h"
#include "logger.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"

uint32_t Measure(uint32_t trigPort, uint8_t trigPin, uint32_t echoPort, uint8_t echoPin);

void Ultrasonic_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOInput(GPIO_PORTB_BASE, GPIO_PIN_1);
}

uint32_t Read_Distance_Front(void)
{
    return Measure(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_PORTB_BASE, GPIO_PIN_1);
}

uint32_t Read_Distance_Left(void)
{
    return 300; // Simplified for demo
}

uint32_t Read_Distance_Right(void)
{
    return 300; // Simplified for demo
}

// ✅ simplified measurement for GitHub version
uint32_t Measure(uint32_t trigPort, uint8_t trigPin, uint32_t echoPort, uint8_t echoPin)
{
    return 500; // Dummy safe value (replace with full ISR version later)
}
