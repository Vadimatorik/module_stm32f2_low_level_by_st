#pragma once

#ifdef __cplusplus

#include "dma.h"
#include "mc_hardware_interfaces_uart.h"
#include "stm32f2xx_hal_conf.h"
#include "user_os.h"

struct uartCfg {
	USART_TypeDef               *uart;
	uint32_t					baudrate;
	uint32_t					mode;						// UART_MODE_RX/UART_MODE_TX/UART_MODE_TX_RX.
    DMA_Stream_TypeDef*         dmaTx;						// Из мерии DMAx_Streamx.
    uint32_t                    dmaTxCh;					// Из серии DMA_CHANNEL_x.
};

class Uart : public UartBase {
public:
	Uart( const uartCfg* const cfg );

	bool 			reinit		( void )								const;

	void 			on     		( void )								const;
	void 			off    		( void )								const;

    BASE_RESULT		tx			(	const uint8_t* const  p_array_tx,
    								const uint16_t& length,
									const uint32_t& timeout_ms	)		const;

    BASE_RESULT		getByte		( uint8_t* data )						const;

    void			irqHandler				( void )					const;

    /// Для внутреннего пользования HAL-а.
    void			giveSemaphore			( void )					const;

private:
    bool 			clkInit	 				( void )					const;

    const uartCfg*										const cfg;
    mutable DMA_HandleTypeDef							hdma_tx;
    mutable	UART_HandleTypeDef							handle;
    mutable USER_OS_STATIC_BIN_SEMAPHORE				s = nullptr;
    mutable USER_OS_STATIC_MUTEX                    	m = nullptr;
    mutable USER_OS_STATIC_BIN_SEMAPHORE_BUFFER     	sb;
    mutable USER_OS_STATIC_MUTEX_BUFFER             	mb;
};

#endif
