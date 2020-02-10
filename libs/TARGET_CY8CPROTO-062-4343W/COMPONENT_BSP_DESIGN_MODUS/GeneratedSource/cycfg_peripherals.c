/*******************************************************************************
* File Name: cycfg_peripherals.c
*
* Description:
* Peripheral Hardware Block configuration
* This file was automatically generated and should not be modified.
* Device Configurator: 2.0.0.1483
* Device Support Library (../../../psoc6pdl): 1.4.0.1889
*
********************************************************************************
* Copyright 2017-2019 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
********************************************************************************/

#include "cycfg_peripherals.h"

#define TIMER_TRANSMITTER_INPUT_DISABLED 0x7U

cy_stc_csd_context_t cy_csd_0_context = 
{
	.lockKey = CY_CSD_NONE_KEY,
};
#if defined (CY_USING_HAL)
	const cyhal_resource_inst_t lcd_0_drive_0_obj = 
	{
		.type = CYHAL_RSC_LCD,
		.block_num = 0U,
		.channel_num = 0,
	};
#endif //defined (CY_USING_HAL)
const cy_stc_sysanalog_config_t ADC_REF_config = 
{
	.startup = CY_SYSANALOG_STARTUP_FAST,
	.iztat = CY_SYSANALOG_IZTAT_SOURCE_LOCAL,
	.vref = CY_SYSANALOG_VREF_SOURCE_LOCAL_1_2V,
	.deepSleep = CY_SYSANALOG_DEEPSLEEP_DISABLE,
};
const cy_stc_sar_config_t ADCT_config = 
{
	.ctrl = (uint32_t) ADCT_CTRL,
	.sampleCtrl = (uint32_t) ADCT_SAMPLE,
	.sampleTime01 = (1023UL << CY_SAR_SAMPLE_TIME0_SHIFT) | (4UL << CY_SAR_SAMPLE_TIME1_SHIFT),
	.sampleTime23 = (2UL << CY_SAR_SAMPLE_TIME2_SHIFT) | (2UL << CY_SAR_SAMPLE_TIME3_SHIFT),
	.rangeThres = (0UL << CY_SAR_RANGE_HIGH_SHIFT) | (0UL << CY_SAR_RANGE_LOW_SHIFT),
	.rangeCond = CY_SAR_RANGE_COND_BELOW,
	.chanEn = 3UL,
	.chanConfig = {(uint32_t) ADCT_CH0_CONFIG, (uint32_t) ADCT_CH1_CONFIG, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL},
	.intrMask = (uint32_t) CY_SAR_INTR_EOS_MASK,
	.satIntrMask = 0UL,
	.rangeIntrMask = 0UL,
	.muxSwitch = ADCT_MUX_SWITCH,
	.muxSwitchSqCtrl = ADCT_MUX_SWITCH_HW_CTRL,
	.configRouting = true,
	.vrefMvValue = ADCT_VREF_MV,
};
#if defined (CY_USING_HAL)
	const cyhal_resource_inst_t ADCT_obj = 
	{
		.type = CYHAL_RSC_ADC,
		.block_num = 0,
		.channel_num = 0,
	};
#endif //defined (CY_USING_HAL)
const cy_stc_rtc_config_t RTC_config = 
{
	.sec = 0U,
	.min = 57U,
	.hour = 23U,
	.amPm = CY_RTC_AM,
	.hrFormat = CY_RTC_24_HOURS,
	.dayOfWeek = CY_RTC_SUNDAY,
	.date = 31U,
	.month = CY_RTC_DECEMBER,
	.year = 20U,
};
#if defined (CY_USING_HAL)
	const cyhal_resource_inst_t RTC_obj = 
	{
		.type = CYHAL_RSC_RTC,
		.block_num = 0U,
		.channel_num = 0U,
	};
#endif //defined (CY_USING_HAL)
const cy_stc_tcpwm_pwm_config_t TIMER_TRANSMITTER_config = 
{
	.pwmMode = CY_TCPWM_PWM_MODE_PWM,
	.clockPrescaler = CY_TCPWM_PWM_PRESCALER_DIVBY_1,
	.pwmAlignment = CY_TCPWM_PWM_LEFT_ALIGN,
	.deadTimeClocks = 0,
	.runMode = CY_TCPWM_PWM_CONTINUOUS,
	.period0 = 30000,
	.period1 = 32768,
	.enablePeriodSwap = false,
	.compare0 = 500,
	.compare1 = 16384,
	.enableCompareSwap = false,
	.interruptSources = CY_TCPWM_INT_ON_TC,
	.invertPWMOut = CY_TCPWM_PWM_INVERT_DISABLE,
	.invertPWMOutN = CY_TCPWM_PWM_INVERT_DISABLE,
	.killMode = CY_TCPWM_PWM_STOP_ON_KILL,
	.swapInputMode = TIMER_TRANSMITTER_INPUT_DISABLED & 0x3U,
	.swapInput = CY_TCPWM_INPUT_0,
	.reloadInputMode = TIMER_TRANSMITTER_INPUT_DISABLED & 0x3U,
	.reloadInput = CY_TCPWM_INPUT_0,
	.startInputMode = TIMER_TRANSMITTER_INPUT_DISABLED & 0x3U,
	.startInput = CY_TCPWM_INPUT_0,
	.killInputMode = TIMER_TRANSMITTER_INPUT_DISABLED & 0x3U,
	.killInput = CY_TCPWM_INPUT_0,
	.countInputMode = TIMER_TRANSMITTER_INPUT_DISABLED & 0x3U,
	.countInput = CY_TCPWM_INPUT_1,
};
#if defined (CY_USING_HAL)
	const cyhal_resource_inst_t TIMER_TRANSMITTER_obj = 
	{
		.type = CYHAL_RSC_TCPWM,
		.block_num = 0U,
		.channel_num = 3U,
	};
#endif //defined (CY_USING_HAL)


void init_cycfg_peripherals(void)
{
	Cy_SysClk_PeriphAssignDivider(PCLK_CSD_CLOCK, CY_SYSCLK_DIV_8_BIT, 0U);

#if defined (CY_USING_HAL)
	cyhal_hwmgr_reserve(&lcd_0_drive_0_obj);
#endif //defined (CY_USING_HAL)

	Cy_SysClk_PeriphAssignDivider(PCLK_PASS_CLOCK_SAR, CY_SYSCLK_DIV_16_BIT, 0U);
#if defined (CY_USING_HAL)
	cyhal_hwmgr_reserve(&ADCT_obj);
#endif //defined (CY_USING_HAL)

#if defined (CY_USING_HAL)
	cyhal_hwmgr_reserve(&RTC_obj);
#endif //defined (CY_USING_HAL)

	Cy_SysClk_PeriphAssignDivider(PCLK_TCPWM0_CLOCKS3, CY_SYSCLK_DIV_16_BIT, 1U);
#if defined (CY_USING_HAL)
	cyhal_hwmgr_reserve(&TIMER_TRANSMITTER_obj);
#endif //defined (CY_USING_HAL)
}
