#include <stdbool.h>
#include <stdint.h>
#include "nrfx_systick.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"

// Определяем пины для светодиодов и кнопки
#define LED_YELLOW_PIN  NRF_GPIO_PIN_MAP(0,6)
#define LED_RED_PIN     NRF_GPIO_PIN_MAP(0,8)
#define LED_GREEN_PIN   NRF_GPIO_PIN_MAP(1,9)
#define LED_BLUE_PIN    NRF_GPIO_PIN_MAP(0,12)
#define BUTTON_PIN      NRF_GPIO_PIN_MAP(1,6)

#define LED_COUNT 4

// Частота и период для ШИМ
#define PWM_HZ 1000                       // Частота ШИМ - 1 кГц
#define PWM_PERIOD_US (16000000 / PWM_HZ) // Период ШИМ в микросекундах

// Инициализация GPIO для светодиодов и кнопки
void init_gpio(void);
void turn_off_leds(void);
void turn_on_led(int pin);
bool is_button_pressed(void);
void delay_ms_700(void);
void delay_us_systick(uint32_t us);
void set_pwm_led_brightness(int led_pin, int brightness_percent);

int main(void)
{
    init_gpio();
    nrfx_systick_init();

    // Определяем последовательность мигания светодиодов
    const int blink_sequence[LED_COUNT] = {7, 2, 0, 2};
    const int led_pins[LED_COUNT] = {LED_YELLOW_PIN, LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN};
    
    int current_led = 0;
    int blink_counter = 0;

    // Параметры для плавного мигания
    int brightness = 0;       
    int fade_step = 1;

    turn_off_leds();

    while (true)
    {
        if (is_button_pressed()) 
        {
            for (int i = current_led; i < LED_COUNT; i++) 
            {
                for (int j = blink_counter; j < blink_sequence[i]; j++) 
                {
                    // Плавное включение светодиода от 0% до 100%
                    for (brightness = 0; brightness <= 100; brightness += fade_step) 
                    {
                        set_pwm_led_brightness(led_pins[i], brightness);
                    }

                    // Плавное выключение светодиода от 100% до 0%
                    for (brightness = 100; brightness >= 0; brightness -= fade_step)
                    {
                        set_pwm_led_brightness(led_pins[i], brightness);
                    }

                    if (!is_button_pressed()) 
                    { 
                        current_led = i;
                        blink_counter = j + 1;
                        
                        if (blink_counter >= blink_sequence[i]) 
                        { 
                            blink_counter = 0;
                            current_led = (i + 1) % LED_COUNT;
                        }
                        break;
                    }
                }

                if (!is_button_pressed()) 
                    break;

                blink_counter = 0;
                nrf_delay_ms(1000);
            }

            if ((current_led == (blink_sequence[3] - 1)) && blink_counter == 0 && is_button_pressed()) 
            {
                current_led = 0;
                blink_counter = 0;
            }
        }
    }
}

void delay_us_systick(uint32_t delay_us) {
    nrfx_systick_state_t start;
    nrfx_systick_get(&start);
    while (!nrfx_systick_test(&start, delay_us));
}

// Функция для изменения яркости светодиода с помощью ШИМ
void set_pwm_led_brightness(int led_pin, int brightness_percent) {
    int on_time = (brightness_percent * PWM_PERIOD_US) / 100; 
    int off_time = PWM_PERIOD_US - on_time;

    nrf_gpio_pin_write(led_pin, 0);
    delay_us_systick(on_time);

    nrf_gpio_pin_write(led_pin, 1);
    delay_us_systick(off_time);
}

// Инициализация GPIO для светодиодов и кнопки
void init_gpio(void)
{
    nrf_gpio_cfg_output(LED_YELLOW_PIN);
    nrf_gpio_cfg_output(LED_RED_PIN);
    nrf_gpio_cfg_output(LED_GREEN_PIN);
    nrf_gpio_cfg_output(LED_BLUE_PIN);
    nrf_gpio_cfg_input(BUTTON_PIN, NRF_GPIO_PIN_PULLUP);
}

void turn_off_leds(void)
{
    nrf_gpio_pin_write(LED_YELLOW_PIN, 1);
    nrf_gpio_pin_write(LED_RED_PIN, 1);
    nrf_gpio_pin_write(LED_GREEN_PIN, 1);
    nrf_gpio_pin_write(LED_BLUE_PIN, 1);
}

void turn_on_led(int led_pin)
{
    nrf_gpio_pin_write(led_pin, 0);
}

void delay_ms_700(void)
{
    nrf_delay_ms(700);
}

bool is_button_pressed(void)
{
    return !nrf_gpio_pin_read(BUTTON_PIN);
}
