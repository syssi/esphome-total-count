#pragma once

#include "../total_count.h"
#include "esphome/core/component.h"
#include "esphome/components/button/button.h"

namespace esphome {
namespace total_count {

class TotalCount;
class TotalCountButton : public button::Button, public Component {
 public:
  void set_parent(TotalCount *parent) { this->parent_ = parent; };
  void dump_config() override;
  void loop() override {}
  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  void press_action() override;
  TotalCount *parent_;
};

}  // namespace total_count
}  // namespace esphome
