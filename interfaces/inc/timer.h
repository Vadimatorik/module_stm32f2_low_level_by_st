#pragma once

#include "mc_hardware_interfaces_timer.h"
#include "stm32f2xx_hal_tim.h"
#include "stm32f2xx_hal_rcc.h"

/*!
 * Параметры делителя и вершины.
 * Для формирования массива конфигураций
 * таймера в зависимости от выбранной
 * частоты RCC.
 */
struct clkTimBaseCfg {
	const uint16_t					period;					// 0..0xFFFF.
	const uint16_t					prescaler;				// 0..0xFFFF.

	/// Используется только в:
	/// 1. timCompOneChannelCfg
	const uint16_t					pulse;					// 0..0xFFFF.
};

/*!
 * Таймер предназначен для генерации прямоугольного сигнала.
 */
struct timCompOneChannelCfg {
	// Используемый таймер.
	TIM_TypeDef*				tim;

	// Параметры таймера.
	HAL_TIM_ActiveChannel		timChannel;

	const clkTimBaseCfg*		const cfg;
	uint32_t					countCfg;

	// Параметры выходного канала.
	uint8_t						outChannel;		// TIM_CHANNEL_x.
	uint32_t					polarity;		// TIM_OCPOLARITY_LOW  / TIM_OCPOLARITY_HIGH.

};

class TimCompOneChannel : public TimCompOneChannelBase {
public:
	TimCompOneChannel( const timCompOneChannelCfg* const cfg );

	bool		reinit			( uint32_t cfg_number )			const;
	bool		on				( void )						const;
	bool		off				( void )						const;

private:
	const timCompOneChannelCfg*		const cfg;
	mutable TIM_HandleTypeDef		hal_tim_cfg;
	mutable	TIM_OC_InitTypeDef		hal_tim_ch_cfg;
};

//**********************************************************************
// TimPwmOneChannel
//**********************************************************************
struct timPwmOneChannelCfg {
	// Используемый таймер.
	TIM_TypeDef*				tim;

	// Параметры таймера.
	HAL_TIM_ActiveChannel		timChannel;

	const clkTimBaseCfg*		const cfg;
	uint32_t					countCfg;

	// Параметры выходного канала.
	uint8_t						outChannel;			// TIM_CHANNEL_x.
	uint32_t					polarity;				// TIM_OCPOLARITY_LOW  / TIM_OCPOLARITY_HIGH.
};

class TimPwmOneChannel : public TimPwmOneChannelBase {
public:
	TimPwmOneChannel( const timPwmOneChannelCfg* const cfg );
	bool	reinit		( uint32_t cfg_number ) 			const;
	bool	on			( void ) 							const;
	bool	off			( void ) 							const;
	void	setDuty		( float duty ) 						const;

private:
	const timPwmOneChannelCfg*		const cfg;
	mutable TIM_HandleTypeDef		tim;
	mutable	TIM_OC_InitTypeDef		timCh;
};

//**********************************************************************
// TimInterrupt
//**********************************************************************
struct timInterruptCfg {
	TIM_TypeDef*				tim;

	HAL_TIM_ActiveChannel		timChannel;

	const clkTimBaseCfg*		const cfg;
	uint32_t					countCfg;
};

class TimInterrupt : public TimInterruptBase {
public:
	TimInterrupt( const timInterruptCfg* const cfg );

	bool	reinit					( uint32_t cfg_number = 0 )	const;
	bool	on						( void )					const;
	bool	off						( void )					const;
	void	clearInterruptFlag		( void )					const;

private:
	const timInterruptCfg*			const cfg;
	mutable TIM_HandleTypeDef		tim;
};
