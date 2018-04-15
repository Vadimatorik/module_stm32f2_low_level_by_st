#pragma once

#ifdef __cplusplus

#include "pin.h"

#ifdef HAL_GPIO_MODULE_ENABLED

class GlobalPort : public GlobalPortBase {
public:
	GlobalPort( const pinCfg* const cfg, uint32_t countCfg ) : cfg( cfg ), countCfg( countCfg ) {}
    void reinitAllPorts ( void ) const;

private:
    const pinCfg*				const cfg;
    const uint32_t				countCfg;
};

#endif

#endif
