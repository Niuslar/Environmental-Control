/*
 * CAdcData.h
 *
 *  Created on: Jan 15, 2023
 *      Author: Niuslar
 */

#ifndef CADCDATA_H_
#define CADCDATA_H_

#include "adc.h"

class CAdcData {
public:
	CAdcData(ADC_HandleTypeDef *p_hadc);

	void init();

	float operator[](uint8_t adc_channel) const;
	void trigger();
private:
	/**
	 *  @brief Number of active ADC Channels,
	 *   change this according to hardware
	 *  @Note: This does not set the number of channels,
	 *  	   and it should match the number set in
	 *  	   hadc.Init.NbrOfConversions
	 */
	static constexpr int adc_channels = 13;

	/** adc_res should change depending on the resolution selected (4096 for
	 * 12-bits) */
	static constexpr int adc_res = 4096;
	static constexpr float adc_vdda = 3.3;
	static constexpr int adc_start_bit = 2;
	static constexpr float adc_conversion_coeff = adc_vdda/adc_res;

	ADC_HandleTypeDef *const mp_hadc = nullptr;
	uint16_t m_adc_data_buf[adc_channels];
};

#endif /* CADCDATA_H_ */
