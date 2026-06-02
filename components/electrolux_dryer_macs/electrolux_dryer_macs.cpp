#include "electrolux_dryer_macs.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

using namespace esphome::electrolux_macs;
namespace esphome {
namespace electrolux_dryer_macs {

static const char *const TAG = "electrolux_dryer_macs";

void ElectroluxDryerMacsComponent::decode_data_(uint8_t target, uint8_t source, std::vector<uint8_t> data) {  
  uint8_t msg_type_ = data[0];
  uint16_t tmp_ = 0;
  switch (msg_type_) {
  
    case MACS_MESSAGE_TYPE_TIME_CHANGE:
#ifdef USE_SENSOR
      if (data[2] == MACS_TIME_CHANGE_PROGRAM_TIME) {
        tmp_ = encode_uint16(data[3], data[4]);
        if (this->remaining_time_sensor_) {
          if (tmp_ == 65535) this->remaining_time_sensor_->publish_state(NAN);
          else this->remaining_time_sensor_->publish_state((float) tmp_);
        }
      } else if (data[2] == MACS_TIME_CHANGE_START_DELAY) {
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
          if (this->delicate_mode_binary_sensor_) this->delicate_mode_binary_sensor_->publish_state(0);
          if (this->heating_binary_sensor_) this->heating_binary_sensor_->publish_state(0);
#endif
#ifdef USE_SENSOR
          if (this->remaining_time_sensor_) this->remaining_time_sensor_->publish_state(NAN);
          if (this->program_dryness_level_sensor_) this->program_dryness_level_sensor_->publish_state(NAN);
          if (this->start_delay_time_sensor_) this->start_delay_time_sensor_->publish_state(NAN);
          if (this->selected_program_number_sensor_) this->selected_program_number_sensor_->publish_state(NAN);
#endif
          break;
        case MACS_APPLIANCE_STATE_IDLE:
        case MACS_APPLIANCE_STATE_PAUSED:
        case MACS_APPLIANCE_STATE_FINISHED:
#ifdef USE_BINARY_SENSOR
          if (this->powered_on_binary_sensor_) this->powered_on_binary_sensor_->publish_state(1);
          if (this->running_binary_sensor_) this->running_binary_sensor_->publish_state(0);
          if (this->heating_binary_sensor_) this->heating_binary_sensor_->publish_state(0);
#endif
          break;
        case MACS_APPLIANCE_STATE_RUNNING:
#ifdef USE_BINARY_SENSOR
          if (this->powered_on_binary_sensor_) this->powered_on_binary_sensor_->publish_state(1);
          if (this->running_binary_sensor_) this->running_binary_sensor_->publish_state(1);
          if (this->heating_binary_sensor_) this->heating_binary_sensor_->publish_state(data[3] == MACS_DRYER_DRYING_PHASE_HEATING);
#endif
          break;
        default:
          break;
      }
      break;
      
    case MACS_MESSAGE_TYPE_PROGRAM_SET:
#ifdef USE_SENSOR
      if (this->program_dryness_level_sensor_) this->program_dryness_level_sensor_->publish_state((float) (data[2] & 0x0F));
      if (this->start_delay_time_sensor_) this->start_delay_time_sensor_->publish_state((float) encode_uint16(0, data[7])*30);
      if (this->selected_program_number_sensor_) this->selected_program_number_sensor_->publish_state((float) data[9]);
#endif
#ifdef USE_BINARY_SENSOR
      if (this->delicate_mode_binary_sensor_) this->delicate_mode_binary_sensor_->publish_state((data[4] & 0x02) != 0);
#endif
      break;
      
    default:
      break;
  }
}

void ElectroluxDryerMacsComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Electrolux Dryer MACS");
  esphome::electrolux_macs::ElectroluxMacsComponent::dump_config();
}

}  // namespace electrolux_dryer_macs
}  // namespace esphome

