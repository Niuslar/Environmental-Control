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

class CController : public CTaskBase
{
public:
    CController(uint32_t run_period,
                const etl::string<configMAX_TASK_NAME_LEN> name,
                uint32_t stack_depth,
                osPriority_t priority);
    virtual ~CController();

    virtual void run();

    void setCommandQueue(osMessageQueueId_t *p_queue)
    {
        if (p_queue != NULL)
        {
            mp_command_queue = p_queue;
        }
    }

protected:
    virtual void processCommand() = 0;
    virtual void processControl() = 0;

private:
    // TODO: does each controller own the command or do we have one queue
    // and each controller has to peek the command.
    uint32_t m_run_period;
    osMessageQueueId_t mp_command_queue;
};

#endif /* CCONTROLLER_H_ */
