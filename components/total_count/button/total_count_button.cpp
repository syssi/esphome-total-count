#include "total_count_button.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

// Fallback for ESPHome < 2026.10.0
#ifndef ESPHOME_LOG_TAG
#define ESPHOME_LOG_TAG(name, tag) static const char *const name = tag
#endif

namespace esphome::total_count {

ESPHOME_LOG_TAG(TAG, "total_count.button");

void TotalCountButton::dump_config() { LOG_BUTTON("", "TotalCount Button", this); }
void TotalCountButton::press_action() { this->parent_->reset_counter(); }

}  // namespace esphome::total_count
