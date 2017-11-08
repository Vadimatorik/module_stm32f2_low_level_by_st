#pragma once

#include "mc_hardware_interfaces_timer.h"

struct tim_comp_one_channel_cfg {

};

class tim_comp_one_channel : public tim_comp_one_channel_base {
public:
    tim_comp_one_channel( const tim_comp_one_channel_cfg* const cfg ) : cfg( cfg ) {}
    void reinit ( void ) const;
    void on ( void ) const;
    void off ( void ) const;

private:
    const tim_comp_one_channel_cfg* const cfg;
};

struct tim_interrupt_cfg {

};

class tim_interrupt : public tim_interrupt_base {
public:
    tim_interrupt( const tim_interrupt_cfg* const cfg ) : cfg( cfg ) {}

    void reinit ( void ) const;
    void on ( void ) const;
    void off ( void ) const;
    void clear_interrupt_flag ( void ) const;

private:
    const tim_interrupt_cfg* const cfg;
};
