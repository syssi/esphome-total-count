#include "total_count_number.h"
#include "esphome/core/log.h"

namespace esphome::total_count {

static const char *const TAG = "total_count.number";

void TotalCountNumber::control(float value) { this->parent_->set_value(value); }
void TotalCountNumber::dump_config() { LOG_NUMBER(TAG, "TotalCount Number", this); }

}  // namespace esphome::total_count
