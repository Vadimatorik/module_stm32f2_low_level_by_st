#include "mc_hardware_interfaces_rcc.h"

struct rcc_cfg {

};

class rcc : public rcc_base {
public:
    rcc( const rcc_cfg* const array_cfg_st ) : array_cfg_st( array_cfg_st ) {}
    RCC_RESULT set_cfg ( uint32_t number_cfg_set ) const;

private:
    const rcc_cfg* const array_cfg_st;
};
