/*
 * CommsController.cpp
 *
 *  Created on: Jan 15, 2023
 *      Author: Niuslar
 */

#include "main.h"
#include "CUartCom.h"
#include "cmsis_os2.h"

#ifdef __cplusplus
extern "C"
{
#endif

CUartCom uart_2("DebugComms");
CUartCom uart_1("ControlComms");
static constexpr int MAX_MESSAGE_SIZE = 50;
etl::string<MAX_MESSAGE_SIZE> message;

extern osMessageQueueId_t messagesOutHandle;
extern osMessageQueueId_t commandsInHandle;
extern osEventFlagsId_t commsInOutHandle;

void CommsControllerInit()
{
	uart_2.init(&huart2);
	uart_2.startRx();

	uart_1.init(&huart1);
	uart_1.startRx();

	message.append("Initialising: ");
	message.append(uart_2.getName());
	message.append("\n");
	uart_2.send(message);

	message.clear();
	message.append("Initialising: ");
	message.append(uart_1.getName());
	message.append("\n");
	uart_2.send(message);

}

void CommsControllerRun()
{
	osEventFlagsWait(commsInOutHandle, 1, osFlagsWaitAny, osWaitForever);
	message.clear();

	etl::string<MAX_STRING_SIZE> commandIn;

	if(uart_2.isDataAvailable())
	{
		commandIn.append(uart_2.getData());
		osMessageQueuePut(commandsInHandle, &commandIn, 1, 100);
	}
	osMessageQueueGet(messagesOutHandle, &message, NULL, 100);

	if(!message.empty())
	{
		uart_2.send(message);
	}
}

#ifdef __cplusplus
}
#endif




