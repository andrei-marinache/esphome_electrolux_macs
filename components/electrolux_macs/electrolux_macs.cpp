#include "electrolux_macs.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace electrolux_macs {

static const char *const TAG = "electrolux_macs";

std::string ElectroluxMacsComponent::print_vector_hex(std::vector<uint8_t> bytes) {
  std::string res;
  size_t len = bytes.size();
  char buf[5] = {0};
  for (size_t i = 0; i < len; i++) {
    if (i > 0) res += ' ';
    sprintf(buf, "%02X", bytes[i]);
    res += buf;
  }
  return res;
}


void ElectroluxMacsComponent::setup() {}

void ElectroluxMacsComponent::loop() {
  const uint32_t now = App.get_loop_component_start_time();
  
  if (this->receiving_ && (now - this->last_transmission_ >= this->receive_timeout_)) {
    ESP_LOGW(TAG, "Last transmission too long ago. Reset RX index.");
    this->data_.clear();
    this->receiving_ = false;
  }
  
  if (available()) this->last_transmission_ = now;
  
  while (available()) {
    uint8_t c;
    read_byte(&c);
    if (!this->receiving_) {
      if (c != MACS_MESSAGE_MARKER && c != MACS_ACK_MARKER)
        continue;
      this->receiving_ = true;
    }
    this->data_.push_back(c);
    
    switch (this->data_[0]) {
      case MACS_ACK_MARKER:
        if (this->data_.size() == 3) {
          this->data_.clear();
          this->receiving_ = false;
        }
        break;
      case MACS_MESSAGE_MARKER:
        if (this->data_.size() == 4)
          this->data_count_ = c;
        if ((this->data_.size() > 4) and (data_.size() == this->data_count_ + 5)) {
          this->process_data_(this->data_);
          this->data_.clear();
          this->receiving_ = false;
        }
        break;
    }

  }
}

uint8_t ElectroluxMacsComponent::calculate_checksum_(std::vector<uint8_t> frame) {
	uint8_t checksum = 0;
	size_t len = frame.size();
	for (size_t i = 0; i < len - 1; i++)
	{
		checksum = checksum ^ frame[i];
	}
	return checksum;
}

void ElectroluxMacsComponent::process_data_(std::vector<uint8_t> frame) {
	uint8_t marker_ = frame[0];
	uint8_t target_ = frame[1];
	uint8_t source_ = frame[2];
	uint8_t length_ = frame[3];

	if (length_ == 0) return;
	if (5 + length_ < frame.size()) return;
	std::vector<uint8_t> data(&frame[4], &frame[4 + length_]);

	ESP_LOGD(TAG, "Received MSG from %X, to %X, data: %s", source_, target_, print_vector_hex(data).c_str());

	if (this->verify_checksum_) {
		uint8_t checksum_ = frame[4 + length_];
		uint8_t checksum_calc_ = this->calculate_checksum_(frame);
		if (checksum_ != checksum_calc_) {
			ESP_LOGW(TAG, "Checksum error (%X != %X), skipping 1 frame", checksum_, checksum_calc_);
			return;
		}
	}
	
	this->decode_data_(target_, source_, data);
}


void ElectroluxMacsComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Electrolux MACS");
  ESP_LOGCONFIG(TAG, "  Receive timeout: %d", this->receive_timeout_);
  ESP_LOGCONFIG(TAG, "  Verify checksum: %s", this->verify_checksum_ ? "true" : "false");
  check_uart_settings(9600, 1, esphome::uart::UART_CONFIG_PARITY_EVEN, 8);
}

}  // namespace electrolux_macs
}  // namespace esphome

