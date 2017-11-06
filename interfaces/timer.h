#pragma once

#include "mc_hardware_interfaces_timer.h"

class tim_comp_one_channel : public tim_comp_one_channel_base {
    tim_comp_one_channel();
    void reinit ( void ) const;
    void on ( void ) const;
    void off ( void ) const;
};

class tim_interrupt : public tim_interrupt_base {
public:
    void reinit ( void ) const;
    void on ( void ) const;
    void off ( void ) const;
    void clear_interrupt_flag ( void ) const;
};
