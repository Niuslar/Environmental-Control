/*
 * TemperatureController.cpp
 *
 *  Created on: Jan 14, 2023
 *      Author: Niuslar
 */

#include "main.h"
#include "cmsis_os2.h"
#include "etl/string.h"

#ifdef __cplusplus
extern "C"
{
#endif

extern osMessageQueueId_t messagesOutHandle;
extern osMessageQueueId_t commandsInHandle;

void TemperatureControllerInit()
{

}

void TemperatureControllerRun()
{
	etl::string<MAX_STRING_SIZE> commandIn;

	osMessageQueueGet(commandsInHandle, &commandIn, NULL, 100);

	// For testing: If we get a command, we send it back
	if(!commandIn.empty())
	{
		osMessageQueuePut(messagesOutHandle, &commandIn, 1, 100);
	}
}

#ifdef __cplusplus
}
#endif


