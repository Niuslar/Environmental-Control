/*
 * Commands-CLI.cpp
 *
 *  Created on: Feb 25, 2023
 *      Author: Niuslar
 */

#include "Commands-CLI.h"


/* Print Hello World Command */

BaseType_t xPrintHelloWorld( char *pcWriteBuffer,
        size_t xWriteBufferLen,
        const char *pcCommandString)
{
	char helloWorld[] = "Hello World\n";
	for(uint8_t i = 0;  i < 12; i++)
	{
		pcWriteBuffer[i] = helloWorld[i];
	}

	return pdFALSE;
}

static const CLI_Command_Definition_t xHelloWorldCommand =
{
		"hello",
		"hello: Print hello world\n",
		xPrintHelloWorld,
		0
};

void RegisterCommands()
{
	FreeRTOS_CLIRegisterCommand(&xHelloWorldCommand);
}
