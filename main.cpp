#include "hardware/regs/intctrl.h"
#include "pico/platform.h"
#include <hardware/gpio.h>
#include <hardware/irq.h>
#include <pico/stdlib.h>
#include <pico/time.h>

static constexpr uint32_t DEBUG_PIN{25};
static constexpr uint32_t INPUT_PIN{18};
static constexpr uint32_t OUTPUT_PIN{16};
static constexpr uint64_t delay_us{1};
static constexpr uint32_t GPIO_EVENT_EDGE_HIGH{0b0000'1000};

static void send_the_clock_pulse() {
  gpio_put(OUTPUT_PIN, true);
  // sleep a few cycles ?
  for (uint ii = 0; ii < 10; ++ii) {
    asm("nop");
  }
  gpio_put(OUTPUT_PIN, false);
}

static void input_handler(uint gpio, uint32_t events) {
  if (gpio == INPUT_PIN && events == GPIO_EVENT_EDGE_HIGH) // edge high
  {
    send_the_clock_pulse();
  } else {
    gpio_put(DEBUG_PIN, !gpio_get(DEBUG_PIN));
  }
  // gpio_acknowledge_irq(gpio, events);
}

static void init_gpio_channels(bool enable_irq) {
  // the LED on the PICO
  gpio_init(DEBUG_PIN); // SIO for single-cycle action, baby
  gpio_set_dir(DEBUG_PIN, true);

  // Input from the debounce button
  gpio_init(INPUT_PIN); // SIO for single-cycle action, baby
  gpio_pull_down(INPUT_PIN);
  gpio_set_dir(INPUT_PIN, false);
  gpio_set_input_hysteresis_enabled(INPUT_PIN, true);

  // Pin which will clock the external shift register
  gpio_init(OUTPUT_PIN); // SIO for single-cycle action, baby
  gpio_pull_down(OUTPUT_PIN);
  gpio_set_dir(OUTPUT_PIN, true);
  gpio_put(OUTPUT_PIN, false);
  gpio_set_input_hysteresis_enabled(OUTPUT_PIN, true);

  // setup the handler
  gpio_set_irq_enabled_with_callback(INPUT_PIN, GPIO_EVENT_EDGE_HIGH,
                                     enable_irq, input_handler);
}

int main() {
  init_gpio_channels(true);

  // I guess that's it?
  for (;;) {
    tight_loop_contents();
  }
  // in C++, the return is unnecessary ;)
}