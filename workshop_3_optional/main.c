#include <stdbool.h>
#include <stdint.h>
#include "nrf_gpio.h"
#include "nrf_delay.h"

// Определение пинов для светодиодов и кнопки
#define YELLOW_LED_PIN NRF_GPIO_PIN_MAP(0, 6)
#define RED_LED_PIN    NRF_GPIO_PIN_MAP(0, 8)
#define GREEN_LED_PIN  NRF_GPIO_PIN_MAP(1, 9)
#define BLUE_LED_PIN   NRF_GPIO_PIN_MAP(0, 12)
#define SW_BUTTON_PIN  NRF_GPIO_PIN_MAP(1, 6)

// Определение последовательности светодиодов: "YYYYYYYRRBB"
const uint32_t led_sequence[] = {YELLOW_LED_PIN, YELLOW_LED_PIN, YELLOW_LED_PIN, YELLOW_LED_PIN, YELLOW_LED_PIN, YELLOW_LED_PIN, YELLOW_LED_PIN,
                                 RED_LED_PIN, RED_LED_PIN,
                                 BLUE_LED_PIN, BLUE_LED_PIN};
const uint32_t sequence_length = sizeof(led_sequence) / sizeof(led_sequence[0]);


void gpio_init(void) {
    nrf_gpio_cfg_output(YELLOW_LED_PIN);
    nrf_gpio_cfg_output(RED_LED_PIN);
    nrf_gpio_cfg_output(GREEN_LED_PIN);
    nrf_gpio_cfg_output(BLUE_LED_PIN);

    nrf_gpio_cfg_input(SW_BUTTON_PIN, NRF_GPIO_PIN_PULLUP);
}

void led_on(uint32_t led_pin) {
    nrf_gpio_pin_clear(led_pin); 
}


void led_off(uint32_t led_pin) {
    nrf_gpio_pin_set(led_pin); 
}

bool is_button_pressed(void) {
    return !nrf_gpio_pin_read(SW_BUTTON_PIN); 
}

void delay_one_second(void) {
    nrf_delay_ms(1000);
}

int main(void) {
    gpio_init();

    uint32_t current_led = 0; 

    while (true) {
        if (is_button_pressed()) {
            while (is_button_pressed()) {
                led_on(led_sequence[current_led]);
                nrf_delay_ms(500);  
                led_off(led_sequence[current_led]);
                nrf_delay_ms(500); 
                
                current_led = (current_led + 1) % sequence_length;
            }
        } else {
            led_off(RED_LED_PIN);
            led_off(GREEN_LED_PIN);
            led_off(BLUE_LED_PIN);
            led_on(led_sequence[current_led]);
            nrf_delay_ms(100);
        }
    }
}
