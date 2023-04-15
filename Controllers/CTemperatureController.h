/*
 * CTemperatureController.h
 *
 *  Created on: 6 Mar 2023
 *      Author: salavat.magazov
 */

#ifndef CTEMPERATURECONTROLLER_H_
#define CTEMPERATURECONTROLLER_H_

#include <CController.h>
#include "CPIDLoop.h"
#include "CThermistor.h"

// TODO: consider making these classes singletons.

class CTemperatureController : public CController
{
public:
    CTemperatureController(uint32_t run_period,
                           const etl::string<configMAX_TASK_NAME_LEN> name,
                           configSTACK_DEPTH_TYPE stack_depth,
                           UBaseType_t priority);
    virtual ~CTemperatureController();

    virtual void run();


private:
};

#endif /* CTEMPERATURECONTROLLER_H_ */
