#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/uart/uart.h"
#include "esphome/core/log.h"
#include "esphome/core/defines.h"
#include "esphome/components/electrolux_macs/electrolux_macs.h"

#include <vector>

namespace esphome {
namespace electrolux_washing_machine_macs {

static const uint8_t MACS_WM_WASH_PHASE_IDLE = 0x0B;
static const uint8_t MACS_WM_WASH_PHASE_HEATING = 0x01;
static const uint8_t MACS_WM_WASH_PHASE_COOLING = 0x02;
static const uint8_t MACS_WM_WASH_PHASE_ANTI_CREASE = 0x04;

class ElectroluxWashingMachineMacsComponent : public esphome::electrolux_macs::ElectroluxMacsComponent {
  public:
  ElectroluxWashingMachineMacsComponent(uart::UARTComponent *uart) : esphome::electrolux_macs::ElectroluxMacsComponent(uart) {}
  void dump_config() override;

#ifdef USE_SENSOR
  SUB_SENSOR(remaining_time)
  SUB_SENSOR(start_delay_time)
  SUB_SENSOR(selected_program_number)
  SUB_SENSOR(time_manager)
  SUB_SENSOR(wash_temperature)
  SUB_SENSOR(spin_speed)
#endif

#ifdef USE_TEXT_SENSOR
  SUB_TEXT_SENSOR(active_alarm)
//  SUB_TEXT_SENSOR(selected_program_name)
#endif

#ifdef USE_BINARY_SENSOR
  SUB_BINARY_SENSOR(powered_on)
  SUB_BINARY_SENSOR(running)
  SUB_BINARY_SENSOR(door_locked)
  SUB_BINARY_SENSOR(pre_wash_enabled)
  SUB_BINARY_SENSOR(stain_wash)
  SUB_BINARY_SENSOR(extra_rinse)
  SUB_BINARY_SENSOR(soft_plus)
  SUB_BINARY_SENSOR(easy_iron)
#endif

  protected:
  void decode_data_(uint8_t target, uint8_t source, std::vector<uint8_t> data) override;
  void decode_ui_(uint8_t target, uint8_t source, std::vector<uint8_t> data);
  
};
}  // namespace electrolux_washing_machine_macs
}  // namespace esphome

