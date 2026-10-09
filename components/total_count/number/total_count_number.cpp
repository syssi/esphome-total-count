#include "total_count_number.h"
#include "esphome/core/log.h"

// Fallback for ESPHome < 2026.10.0
#ifndef ESPHOME_LOG_TAG
#define ESPHOME_LOG_TAG(name, tag) static const char *const name = tag
#endif

namespace esphome::total_count {

ESPHOME_LOG_TAG(TAG, "total_count.number");

void TotalCountNumber::control(float value) { this->parent_->set_value(value); }
void TotalCountNumber::dump_config() { LOG_NUMBER(TAG, "TotalCount Number", this); }

}  // namespace esphome::total_count
