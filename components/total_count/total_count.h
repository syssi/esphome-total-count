#pragma once

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/number/number.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/core/preferences.h"

namespace esphome {
namespace total_count {

class TotalCount : public Component {
 public:
  void set_total_count_sensor(sensor::Sensor *total_count_sensor) { total_count_sensor_ = total_count_sensor; }
  void set_total_count_number(number::Number *total_count_number) { total_count_number_ = total_count_number; }

  void set_restore(bool restore) { restore_ = restore; }
  void set_min_save_interval(uint32_t min_interval) { this->min_save_interval_ = min_interval; }
  void set_parent(binary_sensor::BinarySensor *parent) { parent_ = parent; }
  void set_initial_value(uint32_t initial_value) { initial_value_ = initial_value; }
  void set_step(uint32_t step) { step_ = step; }
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::PROCESSOR; }

  void publish_state_and_save(uint32_t state);
  void reset_counter();
  void set_value(float value);

 protected:
  void process_new_state_(bool state);
  void publish_state_(sensor::Sensor *sensor, float value);
  void publish_state_(number::Number *sensor, float value);

  ESPPreferenceObject pref_;
  binary_sensor::BinarySensor *parent_;
  sensor::Sensor *total_count_sensor_;
  number::Number *total_count_number_;
  uint32_t initial_value_{0};
  uint32_t step_{1};
  uint32_t last_update_{0};
  uint32_t last_save_{0};
  uint32_t min_save_interval_{0};
  uint32_t total_count_{0};
  bool restore_;
};

}  // namespace total_count
}  // namespace esphome
