#include "mc_hardware_interfaces_rcc.h"
#include "stm32f2xx_hal_rcc.h"
#include "stm32f2xx_hal_flash.h"
#include <stdint.h>

struct rcc_cfg {
    RCC_OscInitTypeDef          osc_cfg;
    RCC_ClkInitTypeDef          clk_cfg;
    uint32_t                    f_latency;
};

class rcc : public rcc_base {
public:
    rcc( const rcc_cfg* const array_cfg_st, const uint32_t number_cfg ) : array_cfg_st( array_cfg_st ), number_cfg( number_cfg ) {}
    RCC_RESULT set_cfg ( uint32_t number_cfg_set ) const;

private:
    const rcc_cfg*              const array_cfg_st;
    const uint32_t              number_cfg;
};
