#include <stdlib.h>

#include "bsp/board.h"
#include "tusb.h"

#include "led.h"
#include "mouse.h"

// Poll every 100ms
static const uint32_t INTERVAL_MS = 100;
static const int8_t JIGGLE_DELTA = 50;

static struct context {
  uint32_t start_ms;
  uint32_t ticks;
};

static void context_init(struct context *ctx) {
  ctx->start_ms = 0;
  ctx->ticks = 0;
}

static void light(uint32_t ticks) {
  switch (ticks & 0x0f) {
    case 0x0:
      led_toggle(true);
      break;
    case 0x3:
      led_toggle(false);
      break;
    default:
      break;
  }
}

static void jiggle(uint32_t ticks) {
  switch (ticks & 0x7f) {
    case 0:
    case 3:
      // no button, right, no scroll pan
      mouse_move(JIGGLE_DELTA);
      break;
    case 1:
    case 2:
      // no button, left, no scroll pan
      mouse_move(-JIGGLE_DELTA);
      break;
  }
}

static void run(struct context *ctx) {
  if (board_millis() - ctx->start_ms < INTERVAL_MS)
    return; // not enough time

  ctx->start_ms += INTERVAL_MS;
  light(ctx->ticks);
  jiggle(ctx->ticks);

  ++ctx->ticks;
}

/*------------- MAIN -------------*/
int main() {
  board_init();
  tusb_init();

  struct context ctx;
  context_init(&ctx);

  while (1) {
    tud_task(); // tinyusb device task
    run(&ctx);
  }

  return 0;
}
