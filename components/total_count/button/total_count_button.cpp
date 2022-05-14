#include "total_count_button.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"

namespace esphome {
namespace total_count {

static const char *const TAG = "total_count.button";

void TotalCountButton::dump_config() { LOG_BUTTON("", "TotalCount Button", this); }
void TotalCountButton::press_action() { this->parent_->reset_counter(); }

}  // namespace total_count
}  // namespace esphome
