#include "pico/stdlib.h"
#include "led.h"

static const uint LED_PIN = PICO_DEFAULT_LED_PIN;

void led_init() {
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
}

void led_toggle(bool on) {
  gpio_put(LED_PIN, on ? 1 : 0);
}

