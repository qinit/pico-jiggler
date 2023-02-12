#include <stdint.h>
#include <stdbool.h>
#include "tusb.h"
#include "mouse.h"
#include "usb_descriptors.h"

bool mouse_move(const int8_t deltax) {
  // Remote wakeup
  if (tud_suspended()) {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    tud_remote_wakeup();
  }

  if (!tud_hid_ready()) {
    return false;
  }

  tud_hid_mouse_report(REPORT_ID_MOUSE, 0x00, deltax, 0, 0, 0);
  return true;
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(
    uint8_t instance,
    uint8_t report_id,
    hid_report_type_t report_type,
    uint8_t *buffer,
    uint16_t reqlen
) {
  // TODO not Implemented
  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(
    uint8_t instance,
    uint8_t report_id,
    hid_report_type_t report_type,
    uint8_t const *buffer,
    uint16_t bufsize
) {
  // TODO set LED based on CAPLOCK, NUMLOCK etc...
}

