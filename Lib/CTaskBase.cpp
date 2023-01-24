/*
 * CTaskBase.cpp
 *
 *  Created on: 24 Jan 2023
 *      Author: salavat.magazov
 */

#include "CTaskBase.h"

CTaskBase::CTaskBase(const etl::string<configMAX_TASK_NAME_LEN> name,
                     uint16_t stack_depth,
                     UBaseType_t priority)
    : m_name(name),
      m_stack_depth(stack_depth),
      m_priority(priority)
{
}

CTaskBase::~CTaskBase()
{
    // TODO: ErrorHandler("Task deleted unexpectedly.");
}

bool CTaskBase::start()
{
    BaseType_t result = xTaskCreate(taskRunner,
                                    m_name.c_str(),
                                    m_stack_depth,
                                    this,
                                    m_priority,
                                    &m_handle);
    return (result == pdPASS ? true : false);
}

void CTaskBase::delay(const TickType_t delay)
{
    vTaskDelay(delay);
}

void CTaskBase::delayUntil(TickType_t *const p_previous_wake_time,
                           const TickType_t delay)
{
    vTaskDelayUntil(p_previous_wake_time, delay);
}

void CTaskBase::taskRunner(void *p_param)
{
    CTaskBase *p_task = static_cast<CTaskBase *>(p_param);
    p_task->run();
    // TODO: ErrorHanlder("Task returned from runner unexpectedly.");
}
