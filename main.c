#include <stdint.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#include "ultrasonic.h"
#include "motors.h"
#include "leds.h"
#include "logger.h"

QueueHandle_t xSensorDataQueue;
QueueHandle_t xMotorCommandQueue;
QueueHandle_t xLedCommandQueue;
QueueHandle_t xLogQueue;

void vSensorReadTask(void *pvParameters);
void vDecisionTask(void *pvParameters);
void vMotorControlTask(void *pvParameters);
void vLedControlTask(void *pvParameters);
void vUartLogTask(void *pvParameters);

int main(void)
{
    Hardware_Init_All();

    xSensorDataQueue = xQueueCreate(1, sizeof(SensorData_t));
    xMotorCommandQueue = xQueueCreate(1, sizeof(MotorCommand_t));
    xLedCommandQueue = xQueueCreate(1, sizeof(LedState_t));
    xLogQueue = xQueueCreate(10, sizeof(LogMessage_t));

    xTaskCreate(vSensorReadTask, "SensorTask", 256, NULL, 3, NULL);
    xTaskCreate(vDecisionTask, "DecisionTask", 256, NULL, 2, NULL);
    xTaskCreate(vMotorControlTask, "MotorTask", 256, NULL, 4, NULL);
    xTaskCreate(vLedControlTask, "LedTask", 128, NULL, 1, NULL);
    xTaskCreate(vUartLogTask, "LogTask", 256, NULL, 0, NULL);

    vTaskStartScheduler();
    while(1);
}

/******************** TASKS ********************/

void vSensorReadTask(void *pvParameters)
{
    SensorData_t data;
    TickType_t last = xTaskGetTickCount();
    while(1)
    {
        vTaskDelayUntil(&last, pdMS_TO_TICKS(200));
        data.front_dist = Read_Distance_Front();
        data.left_dist  = Read_Distance_Left();
        data.right_dist = Read_Distance_Right();
        xQueueOverwrite(xSensorDataQueue, &data);
    }
}

void vDecisionTask(void *pvParameters)
{
    SensorData_t d;
    MotorCommand_t cmd;
    LedState_t led;

    while(1)
    {
        xQueueReceive(xSensorDataQueue, &d, portMAX_DELAY);
        Decision_Logic(&d, &cmd, &led);
        xQueueOverwrite(xMotorCommandQueue, &cmd);
        xQueueOverwrite(xLedCommandQueue, &led);
    }
}

void vMotorControlTask(void *pvParameters)
{
    MotorCommand_t cmd;
    while(1)
    {
        xQueueReceive(xMotorCommandQueue, &cmd, portMAX_DELAY);
        Set_Motors(&cmd);
    }
}

void vLedControlTask(void *pvParameters)
{
    LedState_t state;
    while(1)
    {
        xQueueReceive(xLedCommandQueue, &state, portMAX_DELAY);
        Update_LED(state);
    }
}

void vUartLogTask(void *pvParameters)
{
    LogMessage_t msg;
    while(1)
    {
        if(xQueueReceive(xLogQueue, &msg, portMAX_DELAY))
            UART_Log(msg);
    }
}
