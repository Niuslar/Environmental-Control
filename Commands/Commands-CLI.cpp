/**
 * @file Commands-CLI.cpp
 * @brief This file contains all the commands to be registered on FreeRTOS-Plus-CLI.
 *  Created on: Feb 25, 2023
 *      Author: Niuslar
 */

#include "SystemConfig.h"
#include "Commands-CLI.h"
#include "etl/string.h"
#include <string>

/* ---------- Print Hello World Command ---------------------------*/
/* Command callback */
BaseType_t xHelloWorldCallback( char *pcWriteBuffer,
        size_t xWriteBufferLen,
        const char *pcCommandString)
{
	const char *helloWorld = "Hello World\n";
	for(uint8_t i = 0;  i < strlen(helloWorld); i++)
	{
		pcWriteBuffer[i] = helloWorld[i];
	}

	return pdFALSE;
}

/* Command definition */
static const CLI_Command_Definition_t xHelloWorldCommand =
{
		"hello", //Name
		"hello: Print hello world\n", // Help string
		xHelloWorldCallback, // Callback function
		0  // Number of parameters
};

/* ---------- Read Temperatures Command ---------------------------*/
/* Command callback */
BaseType_t xReadTemperaturesCallback( char *pcWriteBuffer,
        size_t xWriteBufferLen,
        const char *pcCommandString)
{
	osEventFlagsSet(tempControlFlagsHandle, 1); // We set the flag that tells the temp controller to fill a queue with the temperatures.

	std::string temps;
	osMessageQueueGet(messagesOutHandle, &temps, NULL, osWaitForever);

	for(uint32_t i = 0; i <= temps.size(); i++)
	{
		const char * c_str = temps.c_str();
		char c = c_str[i];
		pcWriteBuffer[i] = c;
	}
	pcWriteBuffer[temps.size() + 1] = '\n';
	pcWriteBuffer[temps.size() + 2] = '\0';

	return pdFALSE;
}

/* Command definition */
static const CLI_Command_Definition_t xReadTemperatures =
{
		"readTemps", //Name
		"readTemps: Read temperature from all channels\n", // Help string
		xReadTemperaturesCallback,// Callback function
		0  // Number of parameters
};

void RegisterCommands()
{
	FreeRTOS_CLIRegisterCommand(&xHelloWorldCommand);
	FreeRTOS_CLIRegisterCommand(&xReadTemperatures);
}
