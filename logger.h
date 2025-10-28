#ifndef LOGGER_H_
#define LOGGER_H_

typedef char LogMessage_t[80];

void Logger_Init(void);
void UART_Log(const char *msg);

#endif
