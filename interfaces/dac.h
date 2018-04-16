#pragma once

#include "mc_hardware_interfaces_dac.h"
#include "stm32f2xx_hal_dac.h"
#include "stm32f2xx_hal_rcc.h"

#ifdef __cplusplus

struct DacCfg {
	uint32_t			buffer;				// DAC_OUTPUTBUFFER_ENABLE/DAC_OUTPUTBUFFER_DISABLE.
};

class Dac : public DacBase {
public:
	Dac( const DacCfg* const cfg );

	bool	reinit 					( void )										const;
	void	setValue				( const uint32_t ch, const uint32_t value )		const;

	void	clkEnable				( void )										const;
	void	clkDisable				( void )										const;

private:
	mutable DAC_HandleTypeDef				dac;
	mutable DAC_ChannelConfTypeDef			dacCh;

};

#endif
