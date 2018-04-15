#pragma once

#include "mc_hardware_interfaces_dac.h"
#include "stm32f2xx_hal_dac.h"
#include "stm32f2xx_hal_rcc.h"

#ifdef __cplusplus

struct DacOneChannelCfg {
	uint32_t			channel;			// DAC_CHANNEL_1/DAC_CHANNEL_2.
	uint32_t			buffer;				// DAC_OUTPUTBUFFER_ENABLE/DAC_OUTPUTBUFFER_DISABLE.
};

class DacOneChannel : public DacOneChannelBase {
public:
	DacOneChannel( const DacOneChannelCfg* const cfg );

	bool	reinit 					( void )					const;

	void	setValue				( uint32_t& value )			const;
	void	setValue				( const uint32_t value )	const;

	void	clkEnable				( void )					const;
	void	clkDisable				( void )					const;

private:
	mutable DAC_HandleTypeDef				dac;
	mutable DAC_ChannelConfTypeDef			dacCh;
	const uint32_t							chName;
};

#endif
