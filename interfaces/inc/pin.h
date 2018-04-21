#pragma once

#ifdef __cplusplus

#include "stm32f2xx_hal_conf.h"
#include "mc_hardware_interfaces_pin.h"

#ifdef HAL_GPIO_MODULE_ENABLED

#define PIN_COUNT(x) sizeof(x)/sizeof(x[0])

// Структуры должны быть объявлены в extern "C" области или C файле.
struct pinCfg {
	const GPIO_TypeDef*		 const GPIOx;
	const GPIO_InitTypeDef	init;
};

class Pin : public PinBase {
public:
	Pin( const pinCfg* const cfg ) : cfg( cfg ) {}

	void	init	( void )			const;						// Перед инициализацией включается тактирование портов.

	void	set	 ( void )			const;
	void	reset	( void )			const;
	void	toggle	( void )			const;

	void	set	 ( bool state )		const;
	void	set	 ( int state )		const;
	void	set	 ( uint8_t state )	const;

	bool	read	( void )			const;

protected:
	const pinCfg*		const cfg;

};

class PinMultifunc : public Pin, public PinMultifuncBase {
public:
	PinMultifunc( const pinCfg* const cfg, uint32_t countCfg ) : Pin( cfg ), countCfg( countCfg ) {}
	bool	reinit	( uint32_t numberCfg )	const;

protected:
	const uint32_t		countCfg;
};

/// exitPin - GPIO_PIN_x.
class PinMultifuncIt : public PinMultifunc, public PinMultifuncItBase {
public:
	PinMultifuncIt( const pinCfg* const cfg, uint32_t countCfg, uint32_t exitPin	) : PinMultifunc( cfg, countCfg ), exitPin( exitPin ) {}

	bool	checkIt	( void )				const;
	void	clearIt	( void )				const;

private:
	const uint32_t			exitPin;
};

#endif

#endif
