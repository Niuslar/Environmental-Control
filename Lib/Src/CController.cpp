/*
 * CController.cpp
 *
 *  Created on: 24 Jan 2023
 *      Author: salavat.magazov
 */

#include "CController.h"

static constexpr uint32_t COMMAND_QUEUE_SIZE = 5;
static constexpr uint32_t MESSAGE_SIZE = sizeof(CMessage);

CController::CController(uint32_t run_period,
                         const etl::string<configMAX_TASK_NAME_LEN> name,
                         uint32_t stack_depth,
                         osPriority_t priority)
    : CTaskBase(name, stack_depth, priority),
      m_run_period(run_period)
{
    m_command_queue = osMessageQueueNew(COMMAND_QUEUE_SIZE, MESSAGE_SIZE, NULL);
}

CController::~CController()
{
    // Destruction of CController will trigger error handler in CTaskBase.
}
