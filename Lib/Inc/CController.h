/*
 * CController.h
 *
 *  Created on: 24 Jan 2023
 *      Author: salavat.magazov
 */

#ifndef CCONTROLLER_H_
#define CCONTROLLER_H_

#include "CTaskBase.h"
#include "cmsis_os2.h"

#if (INCLUDE_vTaskDelayUntil == 0)
#    error INCLUDE_vTaskDelayUntil must be defined as 1
#endif

class CController : public CTaskBase
{
public:
    CController(uint32_t run_period,
                const etl::string<configMAX_TASK_NAME_LEN> name,
                uint32_t stack_depth,
                osPriority_t priority);
    virtual ~CController();

    virtual void run() = 0;

protected:
    // TODO: does each controller own the command or do we have one queue
    // and each controller has to peek the command.
    uint32_t m_run_period;
};

#endif /* CCONTROLLER_H_ */
