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
namespace electrolux_dryer_macs {

static const uint8_t MACS_DRYER_DRYING_PHASE_IDLE = 0x0B;
static const uint8_t MACS_DRYER_DRYING_PHASE_HEATING = 0x01;
static const uint8_t MACS_DRYER_DRYING_PHASE_COOLING = 0x02;
static const uint8_t MACS_DRYER_DRYING_PHASE_ANTI_CREASE = 0x04;

class ElectroluxDryerMacsComponent : public esphome::electrolux_macs::ElectroluxMacsComponent {
  public:
  ElectroluxDryerMacsComponent(uart::UARTComponent *uart) : esphome::electrolux_macs::ElectroluxMacsComponent(uart) {}
  void dump_config() override;
 
#ifdef USE_SENSOR
  SUB_SENSOR(remaining_time)
  SUB_SENSOR(start_delay_time)
  SUB_SENSOR(selected_program_number)
  SUB_SENSOR(program_dryness_level)
#endif

//#ifdef USE_TEXT_SENSOR
//  SUB_TEXT_SENSOR(selected_program_name)
//#endif

#ifdef USE_BINARY_SENSOR
  SUB_BINARY_SENSOR(powered_on)
  SUB_BINARY_SENSOR(running)
  SUB_BINARY_SENSOR(delicate_mode)
  SUB_BINARY_SENSOR(heating)
#endif

  protected:
  void decode_data_(uint8_t target, uint8_t source, std::vector<uint8_t> data) override;

};
}  // namespace electrolux_dryer_macs
}  // namespace esphome

