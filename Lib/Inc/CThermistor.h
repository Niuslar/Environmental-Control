/**
 * @file CThermistor.h
 */

/*
 *  Created on: Jan 14, 2023
 *      Author: Niuslar
 */

#ifndef CTHERMISTOR_H_
#define CTHERMISTOR_H_

#include "main.h"
#include "CAdcData.h"

extern uint16_t delayInMs;

class CThermistor {
public:
	CThermistor(uint8_t adc_channel, CAdcData *p_adc_handler);

    float getTemperature() const;
    void setLimits(float min_voltage, float max_voltage);
    void setCalibration(float *p_calibration_coeff = nullptr,
                        uint8_t calibration_order = 0);


private:
	static constexpr float min_volt_range = 0.57;
	static constexpr float max_volt_range = 2.67;
	static constexpr int max_order  = 5;

	static constexpr float out_of_range = 999.9;
    static const float s_default_coeff[];
    static const uint8_t s_default_order;

    float m_min_volt_limit = min_volt_range;
    float m_max_volt_limit = max_volt_range;
    float m_calibration_coeff[max_order + 1];
    uint8_t m_calibration_order;

    uint8_t m_adc_channel = 0;
    CAdcData *mp_adc_handler;
};

#endif /* CTHERMISTOR_H_ */
