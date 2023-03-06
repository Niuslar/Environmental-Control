/*
 * CHumidityController.cpp
 *
 *  Created on: Mar 6, 2023
 *      Author: salavat.magazov
 */

#include <CHumidityController.h>

static constexpr char command[] = "humidity";
static constexpr char help[] =
    "humidity [?] S<setpoint> : \n "
    "? - return humidity report\n"
    "S<setpoint> - change control setpoint. Set to zero to disable control.\n";

static constexpr CLI_Command_Definition_t get_humidity{
    command,
    help,
    &(CHumidityController::requestHumidity)};

CHumidityController::CHumidityController(
    uint32_t run_period,
    const etl::string<configMAX_TASK_NAME_LEN> name,
    uint32_t stack_depth,
    osPriority_t priority)
    : CController(run_period, name, stack_depth, priority)
{
    // TODO Auto-generated constructor stub
}

CHumidityController::~CHumidityController()
{
    // TODO Auto-generated destructor stub
}

void CHumidityController::run() {}

BaseType_t CHumidityController::requestHumidity(char *pcWriteBuffer,
                                                size_t xWriteBufferLen,
                                                const char *pcCommandString)
{
    /*
     * Process humidity command here.
     */
    return 0;
}
