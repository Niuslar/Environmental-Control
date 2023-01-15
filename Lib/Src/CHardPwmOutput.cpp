/**
 *@file CHardPwmOutput.cpp
 *
 */

/*
 * CHardPwmOutput.cpp
 *
 *  Created on: 20 Feb 2022
 *      Author: salavat.magazov
 */

#include "CHardPwmOutput.h"

CHardPwmOutput::CHardPwmOutput()
    : mp_timer(nullptr),
      m_channel(0),
      mb_initialised(false),
      mb_stopped(false)
{
}

/**
 * @brief Initialise PWM channel hardware.
 * @note This class assumes that hardware is configured correctly with respect
 * to all hardware registers. This method will only initialise class internal
 * control structures and start hardware PWM.
 *
 * @param p_timer Pointer to Timer control register structure.
 * @param channel PWM channel.
 */
void CHardPwmOutput::init(TIM_HandleTypeDef *const p_timer,
                          const uint8_t channel)
{
    /* sanitise all inputs */
    if (p_timer == nullptr)
    {
        Error_Handler();
    }
    // TODO: some timers have more than 4 channels. might need to find a way to
    // check against actual timer capabilities.
    if (channel != TIM_CHANNEL_1 && channel != TIM_CHANNEL_2 &&
        channel != TIM_CHANNEL_3 && channel != TIM_CHANNEL_4)
    {
        Error_Handler();
    }

    mp_timer = p_timer;
    m_channel = channel;
    if (HAL_TIM_PWM_Start(mp_timer, m_channel) == HAL_OK)
    {
        mb_initialised = true;
    }
    else
    {
        Error_Handler();
    }
}

/**
 * @brief Set duty cycle of the PWM output.
 * @note This method will only work if PWM channel has been configured.
 *
 * @param duty_cycle_percent Duty cycle in percent. Actual duty cycle will
 * differ slightly due to discretisation within timer engine.
 */
void CHardPwmOutput::setDutyCycle(float duty_cycle_percent)
{
    if (mb_initialised)
    {
        uint32_t capture_compare_reg;
        duty_cycle_percent *= mp_timer->Instance->ARR + 1;
        capture_compare_reg = (uint32_t)((duty_cycle_percent / 100) + 0.5);
        if (capture_compare_reg > mp_timer->Instance->ARR + 1)
        {
            // TODO: test if it's legal to have CCR register larger value than
            // ARR. Might cause crash of the timer.
            capture_compare_reg = mp_timer->Instance->ARR + 1;
        }
        __HAL_TIM_SET_COMPARE(mp_timer, m_channel, capture_compare_reg);
    }
}

/**
 * @brief Get current duty cycle.
 *
 * @return True duty cycle as generated by the timer.
 */
float CHardPwmOutput::getDutyCycle() const
{
    float duty_cycle = -1;
    if (mb_initialised)
    {
        duty_cycle = __HAL_TIM_GET_COMPARE(mp_timer, m_channel);
        duty_cycle /= (mp_timer->Instance->ARR + 1);
    }
    return duty_cycle;
}