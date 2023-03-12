/*
 * CTemperatureController.cpp
 *
 *  Created on: 6 Mar 2023
 *      Author: salavat.magazov
 */

#include <CTemperatureController.h>

static constexpr char command[] = "temperature";
static constexpr char help[] =
    "temperature [?] C<channel> S<setpoint> : \n "
    "? - return temperature report\n"
    "C<channel> - channel number. Skip to apply to all channels.\n"
    "S<setpoint> - change control setpoint. Set to zero to disable control.\n";

static constexpr CLI_Command_Definition_t get_temperature{
    command,
    help,
    &(CTemperatureController::requestTemperature)};

static constexpr float CALIB_COEFF[] = {-5.16917E-13,
                                        1.70585E-09,
                                        5.82242E-06,
                                        -0.059851305,
                                        180.289278};

CTemperatureController::CTemperatureController(
    uint32_t run_period,
    const etl::string<configMAX_TASK_NAME_LEN> name,
    uint32_t stack_depth,
    osPriority_t priority)
    : CController(run_period, name, stack_depth, priority)
{
    for (uint8_t i = 0; i < CHANNEL_COUNT; i++)
    {
        m_sensor[i].setCalibration(CALIB_COEFF, 4);
        m_control[i].reset();
    }

    FreeRTOS_CLIRegisterCommand(&get_temperature);
}

CTemperatureController::~CTemperatureController()
{
    // TODO Auto-generated destructor stub
}

void CTemperatureController::run()
{
    while (true)
    {
        float temperature;
        float power;
        for (uint8_t i = 0; i < CHANNEL_COUNT; i++)
        {
            temperature = m_sensor[i].getTemperature(mp_hw->getChannelTemp(i));
            power = m_control[i].run(m_target[i], temperature);
            mp_hw->setHardPwmOutput(power, i);
        }
        osDelayUntil(m_run_period);
    }
}

// CLI command processors

BaseType_t CTemperatureController::requestTemperature(
    char *pcWriteBuffer,
    size_t xWriteBufferLen,
    const char *pcCommandString)
{
    // TODO: create a parser for commands.
    return 0;
}
