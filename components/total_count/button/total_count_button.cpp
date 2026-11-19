#include "total_count_button.h"

namespace esphome::total_count {

void TotalCountButton::press_action() { this->parent_->reset_counter(); }

}  // namespace esphome::total_count
