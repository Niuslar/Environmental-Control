/*
 * TemperatureController.cpp
 *
 *  Created on: Jan 14, 2023
 *      Author: Niuslar
 */

#include "main.h"
#include "CThermistor.h"

CThermistor thermistor1;

#ifdef __cplusplus
extern "C"
{
#endif

void TemperatureControllerInit()
{

}

void TemperatureControllerRun()
{
	thermistor1.ReadTemp();
	HAL_Delay(1000);
}

#ifdef __cplusplus
}
#endif


