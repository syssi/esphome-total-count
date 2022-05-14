#include "total_count.h"
#include "esphome/core/log.h"

namespace esphome {
namespace total_count {

static const char *const TAG = "total_count";

void TotalCount::setup() {
  uint32_t initial_value = this->initial_value_;

  if (this->restore_ && this->total_count_sensor_ != nullptr) {
    this->pref_ = global_preferences->make_preference<float>(this->total_count_sensor_->get_object_id_hash());
    this->pref_.load(&initial_value);
  }
  this->publish_state_and_save(initial_value);

  this->parent_->add_on_state_callback([this](bool state) { this->process_new_state_(state); });
}

void TotalCount::dump_config() {
  LOG_SENSOR("", "Total Count", this->total_count_sensor_);
  LOG_NUMBER("", "Total Count", this->total_count_number_);
}

void TotalCount::publish_state_and_save(uint32_t state) {
  this->last_update_ = millis();
  this->total_count_ = state;

  this->publish_state_(this->total_count_sensor_, state);
  this->publish_state_(this->total_count_number_, state);

  if (this->restore_ && this->total_count_sensor_ != nullptr) {
    const uint32_t now = millis();
    if (now - this->last_save_ < this->min_save_interval_) {
      return;
    }
    this->last_save_ = now;

    this->pref_.save(&state);
  }
}

void TotalCount::reset_counter() { this->publish_state_and_save(this->initial_value_); }

void TotalCount::set_value(float value) { this->publish_state_and_save((uint32_t) value); }

void TotalCount::process_new_state_(bool state) {
  if (std::isnan(state))
    return;

  if (state) {
    this->publish_state_and_save(this->total_count_ + this->step_);
  }
}

void TotalCount::publish_state_(sensor::Sensor *sensor, float value) {
  if (sensor == nullptr)
    return;

  sensor->publish_state(value);
}

void TotalCount::publish_state_(number::Number *sensor, float value) {
  if (sensor == nullptr)
    return;

  sensor->publish_state(value);
}

}  // namespace total_count
}  // namespace esphome
