/** @file
 *
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example
 * @brief Blinky Example Application main file.
 *
 * This file contains the source code for a sample application to blink LEDs.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"


void blink_led(uint32_t led_number, uint32_t times)
{
    for (uint32_t j = 0; j < times; j++)
    {
        bsp_board_led_invert(led_number);
        nrf_delay_ms(500);
        bsp_board_led_invert(led_number); 
        nrf_delay_ms(500); 
    }
}

// Функция для обработки идентификатора устройства
void update_blink_pattern(const char* device_id)
{
    if (device_id[0] != '#' || device_id[1] == '\0') {
        return; 
    }
    
    for (uint32_t i = 1; device_id[i] != '\0' && i <= LEDS_NUMBER; i++) {
        uint32_t times = device_id[i] - '0'; 
        blink_led(i - 1, times); 
        nrf_delay_ms(1000); 
    }
}

/**
 * @brief Function for application main entry.
 */
int main(void)
{
    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);

    const char* device_id = "#7202";
     
    while (true)
    {
        update_blink_pattern(device_id); 
    }
}

/**
 *@}
 **/
