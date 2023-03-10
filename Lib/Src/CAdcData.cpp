/**
 *@file CAdcData.cpp
 *@brief This files contains the methods for the CAdcData class
 *
 */

/*
 *  Created on: Jan 15, 2023
 *      Author: Niuslar
 */

#include <CAdcData.h>

CAdcData::CAdcData(ADC_HandleTypeDef *p_hadc) : mp_hadc(p_hadc)
{
	 // Check mp_hadc is not null
	if (!mp_hadc)
	{
		Error_Handler();
	}
}


/**
 * @brief Calibrate and Start ADC
 * @note The ADC will read all the channels once and then stop.
 * To read the channels again, use the triggerADC() method.
 */
void CAdcData::init()
{
    // Start ADC with DMA
    if (HAL_ADC_Start_DMA(mp_hadc,
                          (uint32_t *)m_adc_data_buf,
                          adc_channels) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief read data converted to volts for a specific adc_channel
 * @param adc_channel Number of channel starting from 0
 * @retval Volts
 */
float CAdcData::operator[](uint8_t adc_channel) const
{
    // Check channel is within defined range
    if (adc_channel >= adc_channels)
    {
        // Return 0 if it's an invalid channel
        return 0;
    }

    float volts = ((float)m_adc_data_buf[adc_channel]) * adc_conversion_coeff;

    return volts;
}

/**
 * @brief Trigger a sequence read of all ADC Channels
 * @note This function will replace all the values in the adc_data_buf.
 */
void CAdcData::trigger()
{
    // Restart ADC Readings
    if (HAL_ADC_Start_DMA(mp_hadc,
                          (uint32_t *)m_adc_data_buf,
                          adc_channels) != HAL_OK)
    {
        Error_Handler();
    }
}
