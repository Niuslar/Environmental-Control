/*
 * TemperatureController.cpp
 *
 *  Created on: Jan 14, 2023
 *      Author: Niuslar
 */

#include "main.h"
#include "cmsis_os2.h"
#include "etl/string.h"
#include "CThermistor.h"
#include "adc.h"
#include "SystemConfig.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* Controller variables */
CAdcData    adc1(&hadc1);

CThermistor thermistor1(TEMP_1_ADC_CH, &adc1);
CThermistor thermistor2(TEMP_2_ADC_CH, &adc1);
CThermistor thermistor3(TEMP_3_ADC_CH, &adc1);
CThermistor thermistor4(TEMP_4_ADC_CH, &adc1);
CThermistor thermistor5(TEMP_5_ADC_CH, &adc1);
CThermistor thermistor6(TEMP_6_ADC_CH, &adc1);
CThermistor thermistor7(TEMP_7_ADC_CH, &adc1);
CThermistor thermistor8(TEMP_8_ADC_CH, &adc1);

CThermistor *thermistors[TEMP_CHANNELS_COUNT] = {&thermistor1,
		&thermistor2,
		&thermistor3,
		&thermistor4,
		&thermistor5,
		&thermistor6,
		&thermistor7,
		&thermistor8
};


void TemperatureControllerInit()
{
	adc1.init();

}

void TemperatureControllerRun()
{
	etl::string<MAX_STRING_SIZE> commandIn;

	osMessageQueueGet(commandsInHandle, &commandIn, NULL, 100);

	// For testing: If we get a command, we send it back
	if(!commandIn.empty())
	{
		osEventFlagsSet(commsInOutHandle,2);
		osMessageQueuePut(messagesOutHandle, &commandIn, 1, 100);
	}

	/* Loop through temperature sensors and send the right output*/
	for(uint8_t i = 0; i < TEMP_CHANNELS_COUNT; i++)
	{

	}

	adc1.trigger();
}

#ifdef __cplusplus
}
#endif


