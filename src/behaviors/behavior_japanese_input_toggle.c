#define DT_DRV_COMPAT zmk_behavior_japanese_input_toggle

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>
#include <dt-bindings/zmk/keys.h>

#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>
#include <zmk/behavior.h>
#include "./behavior_japanese_input.h"

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

// status of japanese input behavior
static bool japanese_input_enabled = false;

bool japanese_input_enablement(void) {
  return japanese_input_enabled;
}

void japanese_input_enable(void) {
  japanese_input_enabled = true;
}

void japanese_input_disable(void) {
  japanese_input_enabled = false;
}

// do nothing. this is placeholder-only
static int on_japanese_input_binding_toggle_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    return ZMK_BEHAVIOR_OPAQUE;
}

// enable/disable the japanese input behaivior based on param1
static int on_japanese_input_binding_toggle_released(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event) {
  if (binding->param1 == 0x1) {
     LOG_DBG("Enable Japanese input");
     japanese_input_enable();
  } else {
     LOG_DBG("Disable Japanese input");
     japanese_input_disable();
  }

  return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api japanese_input_toggle_driver_api = {
    .binding_pressed = on_japanese_input_binding_toggle_pressed,
    .binding_released = on_japanese_input_binding_toggle_released,
};

#define JPT_INST(n)                                                                         \
    BEHAVIOR_DT_INST_DEFINE(n, NULL, NULL, NULL, NULL, POST_KERNEL,  \
                            CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &japanese_input_toggle_driver_api);

DT_INST_FOREACH_STATUS_OKAY(JPT_INST)
