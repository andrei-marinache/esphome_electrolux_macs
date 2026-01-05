#include "electrolux_washing_machine_macs.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

using namespace esphome::electrolux_macs;
namespace esphome {
namespace electrolux_washing_machine_macs {

static const char *const TAG = "electrolux_washing_machine_macs";

void ElectroluxWashingMachineMacsComponent::decode_data_(uint8_t target, uint8_t source, std::vector<uint8_t> data) {  
  uint8_t msg_type_ = data[0];
  uint16_t tmp_ = 0;
  switch (msg_type_) {
  
    case MACS_MESSAGE_TYPE_TIME_CHANGE:
#ifdef USE_SENSOR
      if (data[2] == 0) {
        tmp_ = encode_uint16(data[3], data[4]);
        if (this->remaining_time_sensor_) {
          if (tmp_ == 65535) this->remaining_time_sensor_->publish_state(NAN);
          else this->remaining_time_sensor_->publish_state((float) tmp_);
        }
      } else if (data[2] == 1) {
        tmp_ = encode_uint16(data[3], data[4]);
        if (this->start_delay_time_sensor_) {
          if (tmp_ == 65535) this->start_delay_time_sensor_->publish_state(NAN);
          else this->start_delay_time_sensor_->publish_state(((float) tmp_) / 6);
        }
      }
#endif
      break;
      
    case MACS_MESSAGE_TYPE_STATE:
      switch (data[2]) {
        case MACS_APPLIANCE_STATE_STANDBY:
#ifdef USE_BINARY_SENSOR
          if (this->powered_on_binary_sensor_) this->powered_on_binary_sensor_->publish_state(0);
          if (this->running_binary_sensor_) this->running_binary_sensor_->publish_state(0);
          if (this->door_locked_binary_sensor_) this->door_locked_binary_sensor_->publish_state(0);
          if (this->pre_wash_enabled_binary_sensor_) this->pre_wash_enabled_binary_sensor_->publish_state(NAN);
          if (this->stain_wash_binary_sensor_) this->stain_wash_binary_sensor_->publish_state(NAN);
          if (this->extra_rinse_binary_sensor_) this->extra_rinse_binary_sensor_->publish_state(NAN);
          if (this->soft_plus_binary_sensor_) this->soft_plus_binary_sensor_->publish_state(NAN);
          if (this->easy_iron_binary_sensor_) this->easy_iron_binary_sensor_->publish_state(NAN);
#endif
#ifdef USE_SENSOR
          if (this->remaining_time_sensor_) this->remaining_time_sensor_->publish_state(NAN);
          if (this->start_delay_time_sensor_) this->start_delay_time_sensor_->publish_state(NAN);
          if (this->selected_program_number_sensor_) this->selected_program_number_sensor_->publish_state(NAN);
          if (this->wash_temperature_sensor_) this->wash_temperature_sensor_->publish_state(NAN);
          if (this->spin_speed_sensor_) this->spin_speed_sensor_->publish_state(NAN);
          if (this->time_manager_sensor_) this->time_manager_sensor_->publish_state(NAN);
#endif
          break;
        case MACS_APPLIANCE_STATE_IDLE:
        case MACS_APPLIANCE_STATE_PAUSED:
        case MACS_APPLIANCE_STATE_FINISHED:
#ifdef USE_BINARY_SENSOR
          if (this->powered_on_binary_sensor_) this->powered_on_binary_sensor_->publish_state(1);
          if (this->running_binary_sensor_) this->running_binary_sensor_->publish_state(0);
#endif
          break;
        case MACS_APPLIANCE_STATE_RUNNING:
        case MACS_APPLIANCE_STATE_PENDING_START:
#ifdef USE_BINARY_SENSOR
          if (this->powered_on_binary_sensor_) this->powered_on_binary_sensor_->publish_state(1);
          if (this->running_binary_sensor_) this->running_binary_sensor_->publish_state(1);
#endif
          break;
        default:
          break;
      }
      if (this->door_locked_binary_sensor_) this->door_locked_binary_sensor_->publish_state((data[5] & 0x03) == 0);
      break;
      
    case MACS_MESSAGE_TYPE_PROGRAM_SET:
#ifdef USE_SENSOR
      if (this->wash_temperature_sensor_) this->wash_temperature_sensor_->publish_state((float) data[2]);
      if (this->spin_speed_sensor_) this->spin_speed_sensor_->publish_state((float) encode_uint16(0, data[3])*50);
      if (this->start_delay_time_sensor_) this->start_delay_time_sensor_->publish_state((float) encode_uint16(0, data[9])*30);
      if (this->selected_program_number_sensor_) this->selected_program_number_sensor_->publish_state((float) data[12]);
      // if (this->time_manager_sensor_) this->time_manager_sensor_->publish_state((float) data[12]);
#endif
#ifdef USE_BINARY_SENSOR
      if (this->easy_iron_binary_sensor_) this->easy_iron_binary_sensor_->publish_state((data[6] & 0x01) != 0);
      if (this->stain_wash_binary_sensor_) this->stain_wash_binary_sensor_->publish_state((data[6] & 0x04) != 0);
      if (this->extra_rinse_binary_sensor_) this->extra_rinse_binary_sensor_->publish_state((data[6] & 0x10) != 0);
      if (this->soft_plus_binary_sensor_) this->soft_plus_binary_sensor_->publish_state((data[6] & 0x20) != 0);
      if (this->pre_wash_enabled_binary_sensor_) this->pre_wash_enabled_binary_sensor_->publish_state((data[7] & 0x80) != 0);
#endif
      break;
      
    default:
      break;
  }
}

}  // namespace electrolux_washing_machine_macs
}  // namespace esphome

