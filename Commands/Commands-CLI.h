/*
 * Commands-CLI.h
 *
 *  Created on: Feb 25, 2023
 *      Author: Niuslar
 */

#ifndef COMMANDS_CLI_H_
#define COMMANDS_CLI_H_

#include "FreeRTOS.h"
#include "FreeRTOS_CLI.h"


void RegisterCommands();

/* List of registered commands */
BaseType_t xPrintHelloWorld( char *pcWriteBuffer,
        size_t xWriteBufferLen,
        const char *pcCommandString);





#endif /* COMMANDS_CLI_H_ */
