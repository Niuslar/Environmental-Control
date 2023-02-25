/*
 * CommsController.cpp
 *
 *  Created on: Jan 15, 2023
 *      Author: Niuslar
 */

#include "main.h"
#include "CUartCom.h"
#include "cmsis_os2.h"
#include "SystemConfig.h"
#include "Commands-CLI.h"

#define MAX_OUTPUT_LENGTH 100
#define MAX_INPUT_LENGTH  50

#ifdef __cplusplus
extern "C"
{
#endif

CUartCom uart_2("DebugComms");
CUartCom uart_1("ControlComms");
static constexpr int MAX_MESSAGE_SIZE = 200;
etl::string<MAX_MESSAGE_SIZE> message;

void CommsControllerInit()
{
	uart_2.init(&huart2);
	uart_1.init(&huart1, USART1_DE_GPIO_Port, USART1_DE_Pin);

	message.append("Initialising: ");
	message.append(uart_2.getName());
	message.append("\n");
	uart_2.send(message);

	message.clear();
	message.append("Initialising: ");
	message.append(uart_1.getName());
	message.append("\n");
	uart_2.send(message);

	message.clear();
	message.append("Ready to receive commands\n");
	uart_2.send(message);

	RegisterCommands();

}

void CommsControllerRun()
{
	osEventFlagsWait(commsInOutHandle, 1, osFlagsWaitAny, osWaitForever);
	message.clear();

	static char outputBuf[MAX_MESSAGE_SIZE];
	etl::string<MAX_STRING_SIZE> commandIn;

	BaseType_t xMoreDataToFollow = pdFALSE;

	// Clear output buffer
	for(uint8_t i = 0; i < MAX_MESSAGE_SIZE; i++)
	{
		outputBuf[i] = 0;
	}

	if(uart_2.isDataAvailable())
	{
		commandIn.append(uart_2.getData());
		do
		{
			xMoreDataToFollow = FreeRTOS_CLIProcessCommand(commandIn.c_str(), outputBuf, MAX_OUTPUT_LENGTH);
			uart_2.send((uint8_t*)outputBuf, strlen(outputBuf));
		}while(xMoreDataToFollow != pdFALSE);
//		osMessageQueuePut(commandsInHandle, &commandIn, 1, 100);

		commandIn.clear();
	}
}

#ifdef __cplusplus
}
#endif




