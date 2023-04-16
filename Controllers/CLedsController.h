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

	void setLevel(error_types_t error);

private:

	enum
	{
		LED_SPEED_NORMAL = 3,
		LED_SPEED_HIGH = 10,
		LED_SPEED_VERY_HIGH = 50
	};

	uint32_t m_led_speed = LED_SPEED_NORMAL;
	int32_t m_led_duty = 0;
	int8_t m_led_direction = 1; // Set to 1 if the LED is turning on, -1 if off.

	TIM_HandleTypeDef *m_htim = &htim2;
	uint32_t m_channel = TIM_CHANNEL_1;

	uint16_t m_run_period_override = 50;
};

#endif /* CLEDSCONTROLLER_H_ */


