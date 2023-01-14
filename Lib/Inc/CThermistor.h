/*
 * CThermistor.h
 *
 *  Created on: Jan 14, 2023
 *      Author: Niuslar
 */

#ifndef CTHERMISTOR_H_
#define CTHERMISTOR_H_

#include "main.h"

class CThermistor {
public:
	CThermistor();

	void Init();
	void ReadTemp();
};

#endif /* CTHERMISTOR_H_ */
