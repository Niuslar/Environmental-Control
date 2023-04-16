/*
 * CLedsController.cpp
 *
 *  Created on: Apr 15, 2023
 *      Author: Niuslar
 */

#include <CLedsController.h>

CLedsController::CLedsController(
		uint32_t run_period,
				const etl::string<configMAX_TASK_NAME_LEN> name,
				configSTACK_DEPTH_TYPE stack_depth,
				UBaseType_t priority)
		    : CController(run_period, name, stack_depth, priority)
{

}

void CLedsController::run()
{
	HAL_TIM_PWM_Start(m_htim, m_channel); //Breathing GPIO Channel

    while (true)
    {
    	// Set BREATHING LED PWM
    	m_led_duty += (m_led_direction*m_led_speed);

    	if(m_led_duty >= 100)
    	{
    		m_led_duty = 100;
    		m_led_direction = -1;

    	}
    	else if(m_led_duty <= 0)
    	{
    		m_led_duty = 0;
    		m_led_direction = 1;
    	}

    	float pulse_resolution = ((float)(m_htim->Init.Period + 1)/100.0f);

    	uint16_t pulse = pulse_resolution * m_led_duty;

    	__HAL_TIM_SET_COMPARE(m_htim, m_channel, pulse);

    	vTaskDelay(m_run_period_override); //Ignore m_run_period variable set by user
    }
}

/**
 * @brief Set system error level to change the LED speed.
 * The error levels are defined in main.h and are of the type:
 * SYSTEM_OK,
 * SYSTEM_WARNING,
 * SYSTEM_ERROR
 */
void CLedsController::setLevel(error_types_t error)
{
	switch(error)
	{
	case SYSTEM_ERROR:
		m_led_speed = LED_SPEED_VERY_HIGH;
		break;
	case SYSTEM_WARNING:
		m_led_speed = LED_SPEED_HIGH;
		break;
	case SYSTEM_OK:
	default:
		m_led_speed = LED_SPEED_NORMAL;
	}
}

