/*
 * CController.h
 *
 *  Created on: 24 Jan 2023
 *      Author: salavat.magazov
 */

#ifndef CCONTROLLER_H_
#define CCONTROLLER_H_

#include "CTaskBase.h"
#include "queue.h"

class CController : public CTaskBase
{
public:
    CController(const etl::string<configMAX_TASK_NAME_LEN> name,
                uint16_t stack_depth,
                UBaseType_t priority);
    virtual ~CController();

private:
    // TODO: does each controller own the command or do we have one queue and
    // each controller has to peek the command.
    QueueHandle_t *mp_command_queue;
    QueueHandle_t *mp_response_queue;
};

#endif /* CCONTROLLER_H_ */
