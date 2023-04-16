/*
 * CTaskBase.cpp
 *
 *  Created on: Apr 15, 2023
 *      Author: Niuslar
 */

#include "CTaskBase.h"

CTaskBase::CTaskBase(const etl::string<configMAX_TASK_NAME_LEN> name,
		configSTACK_DEPTH_TYPE stack_depth,
		UBaseType_t priority)
		: m_name(name),
		  m_stack_depth(stack_depth),
		  m_priority(priority)
{
}

CTaskBase::~CTaskBase()
{
	setErrorLevel(SYSTEM_ERROR);
}

bool CTaskBase::start()
{
	BaseType_t status = xTaskCreate(taskRunner,
						m_name.c_str(),
						m_stack_depth,
						this,
						m_priority,
						&m_task_handle);

	return (status == pdPASS);
}

void CTaskBase::taskRunner(void *p_param)
{
	CTaskBase *p_task = static_cast<CTaskBase *>(p_param);
	p_task->run();

	// Code execution should never get to this point.
	// TODO: ErrorHanlder("Task returned from runner unexpectedly.");
}
