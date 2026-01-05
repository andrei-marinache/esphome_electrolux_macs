#pragma once

#include "esphome/core/log.h"
#include "esphome/core/defines.h"
#include "esphome/components/uart/uart.h"

#include <vector>

namespace esphome {
namespace electrolux_macs {

static const uint8_t MACS_ID_DRYER_CONTROLLER = 0x22;
static const uint8_t MACS_ID_FRONT_PANEL = 0x2A;

static const uint8_t MACS_MESSAGE_MARKER = 0xC9;
static const uint8_t MACS_ACK_MARKER = 0x98;

static const uint8_t MACS_MESSAGE_TYPE_PROGRAM_SET = 0x50;
static const uint8_t MACS_MESSAGE_TYPE_PROGRAM = 0x55;
static const uint8_t MACS_MESSAGE_TYPE_STATE_SET = 0x51;
static const uint8_t MACS_MESSAGE_TYPE_STATE = 0x52;
static const uint8_t MACS_MESSAGE_TYPE_TIME_CHANGE = 0x56;
static const uint8_t MACS_MESSAGE_TYPE_HEARTBEAT = 0x5F;

static const uint8_t MACS_APPLIANCE_STATE_STANDBY = 0x0B;
static const uint8_t MACS_APPLIANCE_STATE_IDLE = 0x01;
static const uint8_t MACS_APPLIANCE_STATE_RUNNING = 0x02;
static const uint8_t MACS_APPLIANCE_STATE_FINISHED = 0x03;
static const uint8_t MACS_APPLIANCE_STATE_PAUSED = 0x04;
static const uint8_t MACS_APPLIANCE_STATE_PENDING_START = 0x08;


class ElectroluxMacsComponent : public Component, public uart::UARTDevice {
 public:
  ElectroluxMacsComponent(uart::UARTComponent *uart) : uart::UARTDevice(uart) {}

  void setup() override;
  void loop() override;
  void dump_config() override;
  
  // float get_setup_priority() const override { return esphome::setup_priority::HARDWARE_LATE; }

  void set_verify_checksum(bool verify_checksum) { this->verify_checksum_ = verify_checksum; }
  void set_receive_timeout(uint32_t receive_timeout) { this->receive_timeout_ = receive_timeout; }

 protected:
  void process_data_(std::vector<uint8_t> frame);
  uint8_t calculate_checksum_(std::vector<uint8_t> frame);
  virtual void decode_data_(uint8_t target, uint8_t source, std::vector<uint8_t> data);
  
  std::vector<uint8_t> data_;
  bool receiving_{false};
  uint8_t data_count_{0};
  uint32_t last_transmission_{0};
  
  uint32_t receive_timeout_{200};
  bool verify_checksum_{true};
  std::string print_vector_hex(std::vector<uint8_t> bytes);

};
}  // namespace electrolux_macs
}  // namespace esphome

