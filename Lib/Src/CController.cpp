/*
 * CController.cpp
 *
 *  Created on: 24 Jan 2023
 *      Author: salavat.magazov
 */

#include "CController.h"

CController::CController(const etl::string<configMAX_TASK_NAME_LEN> name,
                         uint16_t stack_depth,
                         UBaseType_t priority)
    : CTaskBase(name, stack_depth, priority)
{
}

CController::~CController()
{
    // Destruction of CController will trigger error handler in CTaskBase.
}
