#pragma once

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/preferences.h"

namespace esphome {
namespace total_count {

class TotalCount : public sensor::Sensor, public Component {
 public:
  void set_restore(bool restore) { restore_ = restore; }
  void set_min_save_interval(uint32_t min_interval) { this->min_save_interval_ = min_interval; }
  void set_parent(binary_sensor::BinarySensor *parent) { parent_ = parent; }
  void set_initial_value(uint32_t initial_value) { initial_value_ = initial_value; }
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

  void publish_state_and_save(uint32_t state);

 protected:
  void process_new_state_(bool state);

  ESPPreferenceObject pref_;
  binary_sensor::BinarySensor *parent_;
  uint32_t initial_value_{0};
  uint32_t last_update_{0};
  uint32_t last_save_{0};
  uint32_t min_save_interval_{0};
  uint32_t total_count_{0};
  bool restore_;
};

}  // namespace total_count
}  // namespace esphome
