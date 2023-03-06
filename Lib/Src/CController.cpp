/*
 * CController.cpp
 *
 *  Created on: 24 Jan 2023
 *      Author: salavat.magazov
 */

#include "CController.h"

CController::CController(uint32_t run_period,
                         const etl::string<configMAX_TASK_NAME_LEN> name,
                         uint32_t stack_depth,
                         osPriority_t priority)
    : CTaskBase(name, stack_depth, priority),
      m_run_period(run_period)
{
}

CController::~CController()
{
    // Destruction of CController will trigger error handler in CTaskBase.
}
