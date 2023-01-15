/*
 * @file SystemData.h
 * @brief Here is all the shared data for the different tasks. This includes structures that are used in queues and other shared elements
 *
 *  Created on: Jan 14, 2023
 *      Author: Niuslar
 */

#ifndef SYSTEMDATA_H_
#define SYSTEMDATA_H_

#define MAX_COMMAND_NAME_SIZE 100
#define MAX_ARGUMENTS 10

typedef struct
{
	char commandName[MAX_COMMAND_NAME_SIZE];
	float args[MAX_ARGUMENTS];
}command_t;


#endif /* SYSTEMDATA_H_ */
