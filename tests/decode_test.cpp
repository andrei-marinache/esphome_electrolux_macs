// g++ -std=c++17 -I components tests/decode_test.cpp -o /tmp/decode_test && /tmp/decode_test
// Expected values come from captures on an Electrolux EW8W261B, checked against its display.
#include <cassert>
#include <cstdio>
#include "electrolux_washing_machine_macs/decode.h"
using namespace esphome::electrolux_washing_machine_macs;

int main() {
  // Time Manager: 5..1 bars
  assert(time_manager_level(0x00, 0x01) == 5);
  assert(time_manager_level(0x00, 0x02) == 4);
  assert(time_manager_level(0x00, 0x08) == 3);
  assert(time_manager_level(0x00, 0x10) == 2);
  assert(time_manager_level(0x20, 0x00) == 1);
  assert(time_manager_level(0x00, 0x81) == 5);  // pre-wash bit (0x80) does not affect the level
  assert(std::isnan(time_manager_level(0x00, 0x00)));
  // Drying
  assert(drying_mode_name(0x00, 0x0A) == "Off");
  assert(drying_mode_name(0x01, 0x0A) == "Off");
  assert(drying_mode_name(0xC1, 0x0A) == "Auto: cupboard dry");
  assert(drying_mode_name(0xC0, 0x0A) == "Auto: extra dry");
  assert(drying_mode_name(0xC2, 0x0A) == "Auto: iron dry");
  assert(drying_mode_name(0x80, 0x0F) == "Timed 15 min");
  // Phases: unknown codes are reported raw
  assert(phase_name(0x02, 0x03) == "Rinse");
  assert(phase_name(0x02, 0x07) == "Unknown phase 0x07");
  assert(phase_name(0x0C, 0x00) == "Unknown state 0x0C");
  puts("ok");
}
