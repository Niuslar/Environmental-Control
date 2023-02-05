/*
 * @file SytemConfig.h
 * @brief Header file with the system configuration constants
 *
 *  Created on: Jan 28, 2023
 *      Author: Niuslar
 */

#ifndef SYTEMCONFIG_H_
#define SYTEMCONFIG_H_

/* CMSIS-RTOS variables found in freertos.c */
extern osMessageQueueId_t messagesOutHandle;
extern osMessageQueueId_t commandsInHandle;
extern osEventFlagsId_t commsInOutHandle;

/* ------------------------------------------*/

#define TEMP_CHANNELS_COUNT 8
#define TEMP_1_ADC_CH 0
#define TEMP_2_ADC_CH 1
#define TEMP_3_ADC_CH 4
#define TEMP_4_ADC_CH 6
#define TEMP_5_ADC_CH 7
#define TEMP_6_ADC_CH 8
#define TEMP_7_ADC_CH 9
#define TEMP_8_ADC_CH 10



#endif /* SYTEMCONFIG_H_ */
