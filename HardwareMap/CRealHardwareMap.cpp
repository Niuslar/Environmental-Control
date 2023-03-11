/*
 * CRealHardwareMap.cpp
 *
 *  Created on: Mar 11, 2023
 *      Author: salavat.magazov
 */

#include <CRealHardwareMap.h>

CRealHardwareMap::CRealHardwareMap(
    uint32_t run_period,
    const etl::string<configMAX_TASK_NAME_LEN> name,
    uint32_t stack_depth,
    osPriority_t priority)
    : CController(run_period, name, stack_depth, priority),
      IHardwareMap()
{
}

CRealHardwareMap::~CRealHardwareMap()
{
    // TODO Auto-generated destructor stub
}

/*
 * CController methods
 */

void CRealHardwareMap::run()
{
    while (true)
    {
        // TODO: this is where all data acquisition is happening. The other
        // methods are for accessing acquired data.
        osThreadDelay(m_run_period);
    }
}

/*
 * IHardwareMap methods
 */
void CRealHardwareMap::init()
{
    /* all hardware initialisation of peripherals goes here. */
    m_adc.init();
    for (int i = 0; i < HARD_PWM_OUTPUTS; i++)
    {
        m_hard_pwm_output[i].init(s_timer_init_map[i].p_timer,
                                  s_timer_init_map[i].channel);
        m_polarity_switch[i].init(s_gpio_init_map[i].p_port,
                                  s_gpio_init_map[i].pin);
    }
    m_breathing_light.init(&htim2, TIM_CHANNEL_1);
    m_power_enable.init(PWR_EN_GPIO_Port, PWR_EN_Pin);
    m_humidifier_enable.init(EVAPORATOR_GPIO_Port, EVAPORATOR_Pin);
    m_bme280_sensor.init(&hspi2, SPI2_NSS2_GPIO_Port, SPI2_NSS2_Pin);
}
// ADC access
float CRealHardwareMap::getInputVoltage() const
{
    return m_adc[INPUT_VOLTAGE_CHANNEL] * INPUT_VOLTAGE_SCALE;
}

float CRealHardwareMap::getTotalCurrent() const
{
    return m_adc[TOTAL_CURRENT_CHANNEL] * TOTAL_CURRENT_SCALE;
}

float CRealHardwareMap::getControlCurrent() const
{
    return m_adc[CONTROL_CURRENT_CHANNEL] * CONTROL_CURRENT_SCALE;
}

float CRealHardwareMap::getAmbientTemp() const
{
    float temperature = m_adc[AMBIENT_TEMP_CHANNEL];
    temperature *= AD22100_SCALE;
    temperature += AD22100_OFFSET;
    return temperature;
}

float CRealHardwareMap::getChannelTemp(uint8_t channel) const
{
    float temperature = m_adc[channel];
    // TODO: calibration for thermistor goes here.
    return temperature;
}

// PWM control
float CRealHardwareMap::setHardPwmOutput(float duty_cycle_percent,
                                         uint8_t channel)
{
    float duty_cycle = 0;
    if (channel < HARD_PWM_OUTPUTS)
    {
        // request for hard PWM output
        m_hard_pwm_output[channel].setDutyCycle(duty_cycle_percent);
        duty_cycle = m_hard_pwm_output[channel].getDutyCycle();
    }
    return duty_cycle;
}

float CRealHardwareMap::getHardPwmOutput(uint8_t channel)
{
    float duty_cycle = 0;
    if (channel < HARD_PWM_OUTPUTS)
    {
        duty_cycle = m_hard_pwm_output[channel].getDutyCycle();
    }
    return duty_cycle;
}

#ifdef SOFT_PWM_OUTPUTS
#    error Software PWM has not been tested and must not be used.
#endif

void CRealHardwareMap::setBreathingLight(float duty_cycle)
{
    m_breathing_light.setDutyCycle(duty_cycle);
}

void CRealHardwareMap::enableControlPower(bool b_enable)
{
    m_power_enable.set(b_enable);
}

void CRealHardwareMap::setHumidifierPower(float power)
{
    if (power > 0)
    {
        m_humidifier_enable.set(true);
    }
    else
    {
        m_humidifier_enable.set(false);
    }
}

bool CRealHardwareMap::getHumidifierPower()
{
    return m_humidifier_enable.get();
}
