/*
 * CTaskBase.cpp
 *
 *  Created on: 24 Jan 2023
 *      Author: salavat.magazov
 */

#include "CTaskBase.h"

CTaskBase::CTaskBase(const etl::string<configMAX_TASK_NAME_LEN> name,
                     uint32_t stack_depth,
                     osPriority_t priority)
    : m_name(name),
      m_stack_depth(stack_depth),
      m_priority(priority),
      m_id(NULL)
{
}

CTaskBase::~CTaskBase()
{
    // TODO: ErrorHandler("Task deleted unexpectedly.");
}

bool CTaskBase::start()
{
    osThreadAttr_t attributes;
    attributes.name = m_name.c_str();
    attributes.priority = m_priority;
    attributes.stack_size = m_stack_depth;
    m_id = osThreadNew(taskRunner, this, &attributes);
}

void CTaskBase::taskRunner(void *p_param)
{
    CTaskBase *p_task = static_cast<CTaskBase *>(p_param);
    p_task->run();
    // TODO: ErrorHanlder("Task returned from runner unexpectedly.");
}
