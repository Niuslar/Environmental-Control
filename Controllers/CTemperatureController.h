/*
 * CTemperatureController.h
 *
 *  Created on: 6 Mar 2023
 *      Author: salavat.magazov
 */

#ifndef CTEMPERATURECONTROLLER_H_
#define CTEMPERATURECONTROLLER_H_

#include <CController.h>

class CTemperatureController : public CController
{
public:
    CTemperatureController();
    virtual ~CTemperatureController();

    virtual void run();
};

#endif /* CTEMPERATURECONTROLLER_H_ */
