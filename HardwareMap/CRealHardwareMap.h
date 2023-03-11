/*
 * CRealHardwareMap.h
 *
 *  Created on: Mar 11, 2023
 *      Author: salavat.magazov
 */

#ifndef CREALHARDWAREMAP_H_
#define CREALHARDWAREMAP_H_

#include <FreeRTOS_CLI.h>
#include "CAdcData.h"
#include "CBME280.h"
#include "CController.h"
#include "CGpioWrapper.h"
#include "CHardPwmOutput.h"
#include "CThermistor.h"
#include "IHardwareMap.h"

/**
 * @note All of these parameters are subject to PCB design layout. Refer to
 * specific PCB this code will run on for correct information on what
 * peripherals are being used.
 */
#define V_REF 5.0

#define EVAPORATOR_T_CHANNEL    8
#define INPUT_VOLTAGE_CHANNEL   9
#define TOTAL_CURRENT_CHANNEL   10
#define CONTROL_CURRENT_CHANNEL 11
#define AMBIENT_TEMP_CHANNEL    12

#define INPUT_VOLTAGE_SCALE   ((28.0 + 3.01) / 3.01)  // voltage divider on PCB
#define TOTAL_CURRENT_SCALE   (750E-6 * 200)  // 750uOhm resistor 200x amplifier
#define CONTROL_CURRENT_SCALE (750E-6 * 200)
#define AD22100_SCALE         ((V_REF / 5.0) * (1 / 22.5E-3))
#define AD22100_OFFSET        ((V_REF / 5.0) * (-1.375 / 22.5E-3))

/* This section maps generic names of the pins to something that makes sense.
 * We'll do it this way for now until hardware configuration settles down at
 * which point the pin names will be renamed. */
#define EVAPORATOR_GPIO_Port ENABLE_8_GPIO_Port
#define EVAPORATOR_Pin       ENABLE_8_Pin

const CRealHardwareMap::timer_init_map_t CRealHardwareMap::s_timer_init_map[] =
    {{&htim1, TIM_CHANNEL_1},
     {&htim4, TIM_CHANNEL_1},
     {&htim2, TIM_CHANNEL_2},
     {&htim1, TIM_CHANNEL_4},
     {&htim3, TIM_CHANNEL_1},
     {&htim3, TIM_CHANNEL_2},
     {&htim3, TIM_CHANNEL_3},
     {&htim3, TIM_CHANNEL_4}};

const CRealHardwareMap::gpio_init_map_t CRealHardwareMap::s_gpio_init_map[] = {
    {PWM_1_GPIO_Port, PWM_1_Pin},
    {PWM_2_GPIO_Port, PWM_2_Pin},
    {PWM_3_GPIO_Port, PWM_3_Pin},
    {PWM_4_GPIO_Port, PWM_4_Pin},
    {PWM_5_GPIO_Port, PWM_5_Pin},
    {PWM_6_GPIO_Port, PWM_6_Pin},
    {PWM_7_GPIO_Port, PWM_7_Pin},
    {PWM_8_GPIO_Port, PWM_8_Pin}};

class CRealHardwareMap : public CController, IHardwareMap
{
public:
    CRealHardwareMap(uint32_t run_period,
                     const etl::string<configMAX_TASK_NAME_LEN> name,
                     uint32_t stack_depth,
                     osPriority_t priority);
    virtual ~CRealHardwareMap();
    /*
     * CController methods
     */
    virtual void run();

    /*
     * IHardwareMap methods
     */
    virtual void init();
    // ADC access
    virtual float getInputVoltage() const;
    virtual float getTotalCurrent() const;
    virtual float getControlCurrent() const;
    virtual float getAmbientTemp() const;
    virtual float getChannelTemp(uint8_t channel) const;
    // PWM control
    virtual float setHardPwmOutput(float power, uint8_t channel);
    virtual float getHardPwmOutput(uint8_t channel);
#ifdef SOFT_PWM_OUTPUTS
    virtual float setSoftPwmOutput(float power, uint8_t channel);
    virtual float getSoftPwmOutput(uint8_t channel);
#endif
    virtual void setBreathingLight(float duty_cycle);
    virtual void enableControlPower(bool b_enable);
    virtual void setHumidifierPower(float power);
    virtual bool getHumidifierPower();

private:
    typedef struct TIMER_INIT_MAP_T
    {
        TIM_HandleTypeDef *p_timer;
        uint8_t channel;
    } timer_init_map_t;
    typedef struct GPIO_INIT_MAP_T
    {
        GPIO_TypeDef *p_port;
        uint16_t pin;
    } gpio_init_map_t;

    static const timer_init_map_t s_timer_init_map[HARD_PWM_OUTPUTS];
    static const gpio_init_map_t s_gpio_init_map[HARD_PWM_OUTPUTS];
    CAdcData m_adc;
    CHardPwmOutput m_hard_pwm_output[HARD_PWM_OUTPUTS];
    CGpioWrapper m_polarity_switch[HARD_PWM_OUTPUTS];
    CHardPwmOutput m_breathing_light;
    CGpioWrapper m_power_enable;
    CGpioWrapper m_humidifier_enable;
    CGpioWrapper m_bme_ss;
    CBME280 m_bme280_sensor;
#ifdef SOFT_PWM_OUTPUTS
    CSoftPwmOutput m_soft_pwm_output[SOFT_PWM_OUTPUTS];
#endif
};

#endif /* CREALHARDWAREMAP_H_ */
