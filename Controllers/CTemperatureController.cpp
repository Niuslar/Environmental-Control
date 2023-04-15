/*
 * CTemperatureController.cpp
 *
 *  Created on: 6 Mar 2023
 *      Author: salavat.magazov
 */

#include <CTemperatureController.h>


static constexpr float CALIB_COEFF[] = {-5.16917E-13,
                                        1.70585E-09,
                                        5.82242E-06,
                                        -0.059851305,
                                        180.289278};

CTemperatureController::CTemperatureController(
		uint32_t run_period,
		const etl::string<configMAX_TASK_NAME_LEN> name,
		configSTACK_DEPTH_TYPE stack_depth,
		UBaseType_t priority)
    : CController(run_period, name, stack_depth, priority)
{
}

CTemperatureController::~CTemperatureController()
{
    // TODO Auto-generated destructor stub
}

void CTemperatureController::run()
{
    while (true)
    {
        // TODO: Add implementation
        vTaskDelay(m_run_period);
    }
}

