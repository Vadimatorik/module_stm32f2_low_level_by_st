#include "mc_hardware_interfaces_rcc.h"
#include "stm32f2xx_hal_rcc.h"
#include "stm32f2xx_hal_flash.h"
#include <stdint.h>

struct rcc_cfg {
	RCC_OscInitTypeDef			osc;
	RCC_ClkInitTypeDef			clk;
	uint32_t                    f_latency;
};

class rcc : public rcc_base {
public:
    rcc( const rcc_cfg* const cfg, const uint32_t cfgCount ) : cfg( cfg ), cfgCount( cfgCount ) {}
    RCC_RESULT setCfg ( const uint32_t number_cfg_set ) const;

private:
    const rcc_cfg*              const cfg;
    const uint32_t              cfgCount;
};
