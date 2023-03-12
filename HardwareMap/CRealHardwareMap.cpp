/*
 * CRealHardwareMap.cpp
 *
 *  Created on: Mar 11, 2023
 *      Author: salavat.magazov
 */

#include <CRealHardwareMap.h>

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
static constexpr char command[] = "hw";
static constexpr char help[] =
    "hw [?] : \n "
    "? - return comprehensive low level report\n";

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
static constexpr CLI_Command_Definition_t get_hardware_map{
    command,
    help,
    &(CRealHardwareMap::requestHw)};

CRealHardwareMap::CRealHardwareMap(
    uint32_t run_period,
    const etl::string<configMAX_TASK_NAME_LEN> name,
    uint32_t stack_depth,
    osPriority_t priority)
    : CController(run_period, name, stack_depth, priority),
      m_adc(&hadc1)
{
    FreeRTOS_CLIRegisterCommand(&get_hardware_map);
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
        osDelayUntil(m_run_period);
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

// CLI command processors
BaseType_t CRealHardwareMap::requestHw(char *pcWriteBuffer,
                                       size_t xWriteBufferLen,
                                       const char *pcCommandString)
{
    // TODO: create a parser for commands.
    return 0;
}
