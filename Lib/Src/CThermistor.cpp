/*
 * CThermistor.cpp
 *
 *  Created on: Jan 14, 2023
 *      Author: Niuslar
 */

#include "CThermistor.h"

CThermistor::CThermistor() {
	// TODO Auto-generated constructor stub

}

void CThermistor::Init()
{
}

void CThermistor::ReadTemp()
{
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
}



