/*
 * CLedsController.h
 *
 *  Created on: Apr 15, 2023
 *      Author: Niuslar
 */

#ifndef CLEDSCONTROLLER_H_
#define CLEDSCONTROLLER_H_

#include "CController.h"
#include "tim.h"

class CLedsController : public CController {
public:
	CLedsController(uint32_t run_period,
            const etl::string<configMAX_TASK_NAME_LEN> name,
            configSTACK_DEPTH_TYPE stack_depth,
            UBaseType_t priority);

	virtual void run();

private:
	uint32_t m_led_speed = 3; // This will determine how fast the LED turns on/off. 3 is a "soothing" speed.
	int32_t m_led_duty = 0;
	int8_t m_led_direction = 1; // Set to 1 if the LED is turning on, -1 if off.

	TIM_HandleTypeDef *m_htim = &htim2;
	uint32_t m_channel = TIM_CHANNEL_1;

	uint16_t m_run_period_override = 50;
};

#endif /* CLEDSCONTROLLER_H_ */


