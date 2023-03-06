/*
 * CCO2Controller.cpp
 *
 *  Created on: Mar 6, 2023
 *      Author: salavat.magazov
 */

#include <CCO2Controller.h>

CCO2Controller::CCO2Controller(uint32_t run_period,
                               const etl::string<configMAX_TASK_NAME_LEN> name,
                               uint32_t stack_depth,
                               osPriority_t priority)
    : CController(run_period, name, stack_depth, priority)
{
    // TODO Auto-generated constructor stub
}

CCO2Controller::~CCO2Controller()
{
    // TODO Auto-generated destructor stub
}

void CCO2Controller::run()
{
    while (true)
    {
        osDelayUntil(m_run_period);
    }
}

BaseType_t CCO2Controller::requestCO2(char *pcWriteBuffer,
                                      size_t xWriteBufferLen,
                                      const char *pcCommandString)
{
    return 0;
}
