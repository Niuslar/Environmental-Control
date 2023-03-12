/*
 * CRealHardwareMap.h
 *
 *  Created on: Mar 11, 2023
 *      Author: salavat.magazov
 */

#ifndef CREALHARDWAREMAP_H_
#define CREALHARDWAREMAP_H_

#include <CController.h>
#include <FreeRTOS_CLI.h>
#include <freertos_os2.h>
#include "CAdcData.h"
#include "CBME280.h"
#include "CController.h"
#include "CGpioWrapper.h"
#include "CHardPwmOutput.h"
#include "CThermistor.h"
#include "IHardwareMap.h"
#include "main.h"
#include "tim.h"

class CRealHardwareMap : public CController, public IHardwareMap
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

    // CLI command processor prototype
    static BaseType_t requestHw(char *pcWriteBuffer,
                                size_t xWriteBufferLen,
                                const char *pcCommandString);

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
