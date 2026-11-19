#pragma once

#include "../total_count.h"
#include "esphome/components/button/button.h"

namespace esphome::total_count {

class TotalCount;
class TotalCountButton : public button::Button {
 public:
  void set_parent(TotalCount *parent) { this->parent_ = parent; };

 protected:
  void press_action() override;
  TotalCount *parent_;
};

}  // namespace esphome::total_count
