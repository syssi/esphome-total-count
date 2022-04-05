#include "total_count.h"
#include "esphome/core/log.h"

namespace esphome {
namespace total_count {

static const char *const TAG = "total_count";

void TotalCount::setup() {
  uint32_t initial_value = this->initial_value_;

  if (this->restore_) {
    this->pref_ = global_preferences->make_preference<float>(this->get_object_id_hash());
    this->pref_.load(&initial_value);
  }
  this->publish_state_and_save(initial_value);

  this->total_count_ = initial_value;
  this->last_update_ = millis();
  this->last_save_ = this->last_update_;

  this->parent_->add_on_state_callback([this](bool state) { this->process_new_state_(state); });
}

void TotalCount::dump_config() { LOG_SENSOR("", "Total Count", this); }

void TotalCount::publish_state_and_save(uint32_t state) {
  this->publish_state(state);
  const uint32_t now = millis();
  if (now - this->last_save_ < this->min_save_interval_) {
    return;
  }
  this->last_save_ = now;
  this->pref_.save(&state);
}

void TotalCount::process_new_state_(bool state) {
  if (std::isnan(state))
    return;

  if (state) {
    this->total_count_++;
    this->last_update_ = millis();
    this->publish_state_and_save(this->total_count_);
  }
}

}  // namespace total_count
}  // namespace esphome
