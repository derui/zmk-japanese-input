/*
 * Copyright (c) 2025 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_japanese_input
#define JAPANESE_INPUT_CAPTURE_SIZE 3

#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>
#include <dt-bindings/zmk/keys.h>

#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>
#include <zmk/behavior.h>
#include "./behavior_japanese_input.h"

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

// data model of the japanese input
struct behavior_japanese_input_definition {
  // resultと対応するキーコードのマッピング。releaseされたときに適用される
  uint32_t mapping[JAPANESE_INPUT_CAPTURE_SIZE];

  // 実際に押されるキーコードの一覧。0から順に送出される
  uint32_t result_seq[JAPANESE_INPUT_CAPTURE_SIZE];
};

struct behavior_japanese_input_definition behavior_japanese_input_definitions[] = {
    {.mapping = { Q }, .result_seq = {V, U}},
    {.mapping = { W }, .result_seq = {S, U}},
    {.mapping = { E }, .result_seq = {I}},
    {.mapping = { R }, .result_seq = {X, T, U}},
    {.mapping = { U }, .result_seq = {K, O}},
    {.mapping = { I }, .result_seq = {T, O}},
    {.mapping = { O }, .result_seq = {T, A}},

    {.mapping = { A }, .result_seq = {S, H, I}},
    {.mapping = { S }, .result_seq = {N, O}},
    {.mapping = { D }, .result_seq = {K, U}},
    {.mapping = { F }, .result_seq = {R, U}},
    {.mapping = { G }, .result_seq = {N, I}},
    {.mapping = { H }, .result_seq = {M, O}},
    {.mapping = { J }, .result_seq = {K, A}},
    {.mapping = { K }, .result_seq = {N, N}},
    {.mapping = { L }, .result_seq = {N, A}},
    {.mapping = { SCLN }, .result_seq = {U}},
    {.mapping = { Z }, .result_seq = {R, E}},
    {.mapping = { X }, .result_seq = {R, I}},
    {.mapping = { C }, .result_seq = {K, I}},
    {.mapping = { V }, .result_seq = {W, O}},
    {.mapping = { B }, .result_seq = {O}},
    {.mapping = { N }, .result_seq = {A}},
    {.mapping = { M }, .result_seq = {H, A}},
    {.mapping = { COMMA }, .result_seq = {T, E}},
    {.mapping = { DOT }, .result_seq = {M, A}},
    {.mapping = { SLASH }, .result_seq = {T, I}},

    // シフトキー
    {.mapping = {SPACE}, .result_seq = {SPACE}},
    {.mapping = {ENTER}, .result_seq = {ENTER}},

    // シフト面
    {.mapping = {SPACE, R}, .result_seq = {H, E}},
    {.mapping = {SPACE, U}, .result_seq = {Y, U}},
    {.mapping = {SPACE, I}, .result_seq = {W, A}},
    {.mapping = {SPACE, O}, .result_seq = {R, O}},
    {.mapping = {SPACE, A}, .result_seq = {E}},
    {.mapping = {SPACE, S}, .result_seq = {S, E}},
    {.mapping = {SPACE, D}, .result_seq = {M, I}},
    {.mapping = {SPACE, F}, .result_seq = {R, A}},
    {.mapping = {SPACE, G}, .result_seq = {H, O}},
    {.mapping = {SPACE, H}, .result_seq = {S, O}},
    {.mapping = {SPACE, J}, .result_seq = {Y, O}},
    {.mapping = {SPACE, K}, .result_seq = {T, U}},
    {.mapping = {SPACE, L}, .result_seq = {S, A}},
    {.mapping = {SPACE, SCLN}, .result_seq = {K, E}},
    {.mapping = {SPACE, Z}, .result_seq = {H, I}},
    {.mapping = {SPACE, X}, .result_seq = {F, U}},
    {.mapping = {SPACE, M}, .result_seq = {N, E}},
    {.mapping = {SPACE, COMMA}, .result_seq = {Y, A}},
    {.mapping = {SPACE, DOT}, .result_seq = {M, U}},
    {.mapping = {SPACE, SLASH}, .result_seq = {N, U}},

    {.mapping = {ENTER, R}, .result_seq = {H, E}},
    {.mapping = {ENTER, U}, .result_seq = {Y, U}},
    {.mapping = {ENTER, I}, .result_seq = {W, A}},
    {.mapping = {ENTER, O}, .result_seq = {R, O}},
    {.mapping = {ENTER, A}, .result_seq = {E}},
    {.mapping = {ENTER, S}, .result_seq = {S, E}},
    {.mapping = {ENTER, D}, .result_seq = {M, I}},
    {.mapping = {ENTER, F}, .result_seq = {R, A}},
    {.mapping = {ENTER, G}, .result_seq = {H, O}},
    {.mapping = {ENTER, H}, .result_seq = {S, O}},
    {.mapping = {ENTER, J}, .result_seq = {Y, O}},
    {.mapping = {ENTER, K}, .result_seq = {T, U}},
    {.mapping = {ENTER, L}, .result_seq = {S, A}},
    {.mapping = {ENTER, SCLN}, .result_seq = {K, E}},
    {.mapping = {ENTER, Z}, .result_seq = {H, I}},
    {.mapping = {ENTER, X}, .result_seq = {F, U}},
    {.mapping = {ENTER, M}, .result_seq = {N, E}},
    {.mapping = {ENTER, COMMA}, .result_seq = {Y, A}},
    {.mapping = {ENTER, DOT}, .result_seq = {M, U}},
    {.mapping = {ENTER, SLASH}, .result_seq = {N, U}},

    // 濁音・半濁音
    {.mapping = {W, J}, .result_seq = {Z, U}},
    {.mapping = {R, J}, .result_seq = {B, E}},
    {.mapping = {U, F}, .result_seq = {G, O}},
    {.mapping = {I, F}, .result_seq = {D, O}},
    {.mapping = {O, F}, .result_seq = {D, A}},
    {.mapping = {A, J}, .result_seq = {Z, I}},
    {.mapping = {S, J}, .result_seq = {Z, E}},
    {.mapping = {D, J}, .result_seq = {G, U}},
    {.mapping = {G, J}, .result_seq = {B, O}},
    {.mapping = {H, F}, .result_seq = {Z, O}},
    {.mapping = {J, F}, .result_seq = {G, A}},
    {.mapping = {K, F}, .result_seq = {D, U}},
    {.mapping = {L, F}, .result_seq = {Z, A}},
    {.mapping = {SCLN, F}, .result_seq = {G, E}},
    {.mapping = {Z, J}, .result_seq = {B, I}},
    {.mapping = {X, J}, .result_seq = {B, U}},
    {.mapping = {C, J}, .result_seq = {G, I}},
    {.mapping = {M, F}, .result_seq = {B, A}},
    {.mapping = {COMMA, F}, .result_seq = {D, E}},
    {.mapping = {SLASH, F}, .result_seq = {D, I}},
    {.mapping = {R, M}, .result_seq = {P, E}},
    {.mapping = {G, M}, .result_seq = {P, O}},
    {.mapping = {Z, M}, .result_seq = {P, I}},
    {.mapping = {X, M}, .result_seq = {P, U}},
    {.mapping = {V, M}, .result_seq = {P, A}},

    // special
    {.mapping = {ENTER, C}, .result_seq = {DOT}},
    {.mapping = {ENTER, V}, .result_seq = {COMMA}},
    {.mapping = {SPACE, C}, .result_seq = {DOT}},
    {.mapping = {SPACE, V}, .result_seq = {COMMA}},

    // 小書き
    {.mapping = { Y, B }, .result_seq = { X, O }},
    {.mapping = { T, N }, .result_seq = { X, A }},
    {.mapping = { Y, E }, .result_seq = { X, I }},
    {.mapping = { Y, A }, .result_seq = { X, E }},
    {.mapping = { T, SCLN }, .result_seq = { X, U }},
    {.mapping = { T, U }, .result_seq = { X, Y, U }},
    {.mapping = { T, J }, .result_seq = { X, Y, O }},
    {.mapping = { T, COMMA }, .result_seq = { X, Y, A }},

    // 拗音拡張
    {.mapping = {A, I}, .result_seq = {S, Y, U}},
    {.mapping = {A, K}, .result_seq = {S, Y, O}},
    {.mapping = {A, COMMA}, .result_seq = {S, Y, A}},

    {.mapping = {C, I}, .result_seq = {K, Y, U}},
    {.mapping = {C, K}, .result_seq = {K, Y, O}},
    {.mapping = {C, COMMA}, .result_seq = {K, Y, A}},

    {.mapping = {SLASH, E}, .result_seq = {T, Y, U}},
    {.mapping = {SLASH, D}, .result_seq = {T, Y, O}},
    {.mapping = {SLASH, C}, .result_seq = {T, Y, A}},

    {.mapping = {G, I}, .result_seq = {N, Y, U}},
    {.mapping = {G, K}, .result_seq = {N, Y, O}},
    {.mapping = {G, COMMA}, .result_seq = {N, Y, A}},

    {.mapping = {D, I}, .result_seq = {M, Y, U}},
    {.mapping = {D, K}, .result_seq = {M, Y, O}},
    {.mapping = {D, COMMA}, .result_seq = {M, Y, A}},

    {.mapping = {Z, I}, .result_seq = {H, Y, U}},
    {.mapping = {Z, K}, .result_seq = {H, Y, O}},
    {.mapping = {Z, COMMA}, .result_seq = {H, Y, A}},

    {.mapping = {X, I}, .result_seq = {R, Y, U}},
    {.mapping = {X, K}, .result_seq = {R, Y, O}},
    {.mapping = {X, COMMA}, .result_seq = {R, Y, A}},
    
    {.mapping = {A, I, O}, .result_seq = {Z, Y, U}},
    {.mapping = {A, K, L}, .result_seq = {Z, Y, O}},
    {.mapping = {A, COMMA, DOT}, .result_seq = {Z, Y, A}},

    {.mapping = {C, I, O}, .result_seq = {G, Y, U}},
    {.mapping = {C, K, L}, .result_seq = {G, Y, O}},
    {.mapping = {C, COMMA, DOT}, .result_seq = {G, Y, A}},

    {.mapping = {SLASH, E, W}, .result_seq = {D, Y, U}},
    {.mapping = {SLASH, D, S}, .result_seq = {D, Y, O}},
    {.mapping = {SLASH, C, X}, .result_seq = {D, Y, A}},

    {.mapping = {Z, I, O}, .result_seq = {B, Y, U}},
    {.mapping = {Z, K, L}, .result_seq = {B, Y, O}},
    {.mapping = {Z, COMMA, DOT}, .result_seq = {B, Y, A}},

    {.mapping = {Z, I, U}, .result_seq = {P, Y, U}},
    {.mapping = {Z, K, J}, .result_seq = {P, Y, O}},
    {.mapping = {Z, COMMA, M}, .result_seq = {P, Y, A}},
};

// 押されているkeycodeを保持する配列
static uint32_t captured_keycodes[JAPANESE_INPUT_CAPTURE_SIZE] = {0, 0, 0};
bool continued_shift = false;

void japanese_input_reset_capture(bool continue_shift) {
  uint32_t shift_key = 0;
  
  // captureされたkeycodeをリセットする
  for (int i = 0; i < JAPANESE_INPUT_CAPTURE_SIZE; i++) {
    if (shift_key == 0 && (captured_keycodes[i] == ZMK_HID_USAGE_ID(SPACE) || captured_keycodes[i] == ZMK_HID_USAGE_ID(ENTER))) {
      shift_key = captured_keycodes[i];
    }
    captured_keycodes[i] = 0;
  }

  // シフトキーが押されている場合は、SPACEとENTERを保持する
  if (continue_shift && shift_key != 0) {
    captured_keycodes[0] = shift_key;
    continued_shift = true;
  } else {
    continued_shift = false;
  }
}

// 対象とするキーコードをcaptureする
// captureされたkeycodeは常に0番目に設定され、各々の値は後ろにずらしていく
void japanese_input_capture_keycode(uint32_t keycode) {
  captured_keycodes[2] = captured_keycodes[1];
  captured_keycodes[1] = captured_keycodes[0];
  captured_keycodes[0] = keycode;
}

// seqをkeycodeの順にsortする
void japanese_input_sort_sequence(uint32_t *seq, size_t size) {
    for (size_t i = 0; i < size - 1; ++i) {
        for (size_t j = i + 1; j < size; ++j) {
            if (seq[i] > seq[j]) {
                uint32_t temp = seq[i];
                seq[i] = seq[j];
                seq[j] = temp;
            }
        }
    }
}

struct behavior_japanese_input_definition* japanese_input_find_defintion(uint32_t captured[JAPANESE_INPUT_CAPTURE_SIZE]) {
  int def_size = sizeof(behavior_japanese_input_definitions) / sizeof(behavior_japanese_input_definitions[0]);

  // 並びは正規化されているものとする
  uint32_t copied[JAPANESE_INPUT_CAPTURE_SIZE] = {};
  memcpy(copied, captured, sizeof(uint32_t) * JAPANESE_INPUT_CAPTURE_SIZE);
  japanese_input_sort_sequence(copied, JAPANESE_INPUT_CAPTURE_SIZE);

  for (int i = 0; i < def_size; i++) {
    bool match = true;
    for (int j = 0; j < JAPANESE_INPUT_CAPTURE_SIZE; j++) {
      if (ZMK_HID_USAGE_ID(behavior_japanese_input_definitions[i].mapping[j]) != copied[j]) {
        match = false;
        break;
      }
    }
    if (match) {
      LOG_DBG("Found definition at %d", i);
      return &behavior_japanese_input_definitions[i];
    }
  }

  return NULL;
}

void japanese_input_raise_keycode_state_changed_event(struct behavior_japanese_input_definition* def, uint32_t timestamp) {

    if (def == NULL) {
        LOG_ERR("Definition is null, detect invalid code flow");
        return;
    }

    uint16_t page = HID_USAGE_KEY;
    uint8_t implicit_modifiers = 0x00;
    uint8_t explicit_modifiers = 0x00;
    uint32_t event_timestamp = timestamp;

    for (int i = 0; i < JAPANESE_INPUT_CAPTURE_SIZE; i++) {
      if (def->result_seq[i] == 0) {
        // 0は無視する
        continue;
      }
      struct zmk_keycode_state_changed press_event = {.usage_page = page,
                                                      .keycode = ZMK_HID_USAGE_ID(def->result_seq[i]),
                                                      .implicit_modifiers = implicit_modifiers,
                                                      .explicit_modifiers = explicit_modifiers,
                                                      .state = true,
                                                      .timestamp = event_timestamp++};


      struct zmk_keycode_state_changed release_event = {.usage_page = page,
                                                        .keycode = ZMK_HID_USAGE_ID(def->result_seq[i]),
                                                        .implicit_modifiers = implicit_modifiers,
                                                        .explicit_modifiers = explicit_modifiers,
                                                        .state = false,
                                                        .timestamp = event_timestamp++};
      
      LOG_DBG("Rising event for keycode 0x%02X", ZMK_HID_USAGE_ID(def->result_seq[i]));
      raise_zmk_keycode_state_changed(press_event);
      raise_zmk_keycode_state_changed(release_event);
    }
}

static int on_japanese_input_binding_pressed(struct zmk_behavior_binding *binding,
                                     struct zmk_behavior_binding_event event) {
    uint16_t id = ZMK_HID_USAGE_ID(binding->param1);
    LOG_DBG("position %d keycode 0x%02X", event.position, id);

    if (japanese_input_enablement() == false) {
      // 日本語入力が無効な場合は、2つめのパラメーターにフォールバックする
      raise_zmk_keycode_state_changed_from_encoded(binding->param2, true, event.timestamp);
      LOG_DBG("fallback to 0x%02X", ZMK_HID_USAGE_ID(binding->param2));
      return ZMK_BEHAVIOR_OPAQUE;
    }
    
    japanese_input_capture_keycode(id);

    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_japanese_input_binding_released(struct zmk_behavior_binding *binding,
                                      struct zmk_behavior_binding_event event) {
    uint16_t id = ZMK_HID_USAGE_ID(binding->param1);
    LOG_DBG("position %d keycode 0x%02X", event.position, id);

    if (japanese_input_enablement() == false) {
      // 日本語入力が無効な場合は、2つめのパラメーターにフォールバックする
      raise_zmk_keycode_state_changed_from_encoded(binding->param2, false, event.timestamp);
      LOG_DBG("fallback to 0x%02X", ZMK_HID_USAGE_ID(binding->param2));
      return ZMK_BEHAVIOR_OPAQUE;
    }

    if ((binding->param1 == SPACE || binding->param1 == ENTER) && continued_shift) {
      // 連続シフトの間にSPACEとENTER自体が離された場合は、単独での押下は行われない
      japanese_input_reset_capture(false);
      return ZMK_BEHAVIOR_OPAQUE;
    }

    struct behavior_japanese_input_definition* def = japanese_input_find_defintion(captured_keycodes);
    if (def != NULL) {
      japanese_input_raise_keycode_state_changed_event(def, event.timestamp);
    }
    japanese_input_reset_capture(!(binding->param1 == SPACE || binding->param1 == ENTER));

    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_japanese_input_driver_api = {
    .binding_pressed = on_japanese_input_binding_pressed,
    .binding_released = on_japanese_input_binding_released,
};

static int japanese_input_init(const struct device *dev) {
  static bool initialized = false;

  if (!initialized) {
    // initialize the captured keycodes to zero
    for (int i = 0; i < JAPANESE_INPUT_CAPTURE_SIZE; i++) {
      captured_keycodes[i] = 0;
    }

    // stadardize order of mapping
    int definition_size = sizeof(behavior_japanese_input_definitions) / sizeof(behavior_japanese_input_definitions[0]);
    for (int i = 0; i < definition_size; i++) {
      japanese_input_sort_sequence(behavior_japanese_input_definitions[i].mapping, JAPANESE_INPUT_CAPTURE_SIZE);
    }
  }
  initialized = true;
  return 0;
};

#define JP_INST(n)                                                                                 \
    BEHAVIOR_DT_INST_DEFINE(n, japanese_input_init, NULL, NULL, NULL, POST_KERNEL,                                \
                            CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &behavior_japanese_input_driver_api);

DT_INST_FOREACH_STATUS_OKAY(JP_INST)
