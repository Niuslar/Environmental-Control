/*
 * TemperatureController.cpp
 *
 *  Created on: Jan 14, 2023
 *      Author: Niuslar
 */

#include "main.h"
#include "FreeRTOS.h"
#include "CThermistor.h"
#include "queue.h"

CThermistor thermistor1;
extern QueueHandle_t commandsIn;

#ifdef __cplusplus
extern "C"
{
#endif

void TemperatureControllerInit()
{

}

void TemperatureControllerRun()
{

}

#ifdef __cplusplus
}
#endif


