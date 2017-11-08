#include "stm32f2xx_hal_dma.h"
#include "stm32f2xx_hal_rcc.h"

class dma {
public:
    dma( DMA_HandleTypeDef *dma_handle ): dma_handle( dma_handle ) {}
    dma( void ): dma_handle( nullptr ) {}                                     // На случай, когда изначально не известен адрес структуры конфигурации DMA.

    // dr - data register в периферии (куда).
    // d - данные в памяти (откуда).
    void    start        ( void* dr, void* d, int l ) const;

    // 0 - idle, 1 - end of transfer, negative - error code (или не указана структура)
    int     handler      ( void ) const;          // Данный hendler должен вызываться в пользовательском
                                            // коде на используемом stream нужного dma.
    // Метод нужен тогда, когда изначально не известен указатель на структуру DMA.
    // Или же объект входит в состав другого объекта и указать ее явно не выходит.
    // В таком случае, можно инициализировать объект без указателя с использованием.
    // Пустого конструктора и в последствии, перед первым использованием start,
    // переадть указатель на структуру конфигурации DMA.
    void    rewrite_dma_handle    ( DMA_HandleTypeDef* dma_handle ) const;

    void    init_irq              ( void ) const;        // Включаем прерывание по используемому stream.
    void    clock_enable          ( void ) const;        // Включаем тактирование DMA.
    int     init                  ( void ) const;        // Инициализация канала DMA по структуре.

private:
    bool    check_dma_handle      ( void ) const;        // Функция проверяет, что dma_handle указаен (не nullptr).
                                                // Возвращает true, когда не нулевой.
    mutable DMA_HandleTypeDef*              dma_handle;
};
