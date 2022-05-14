#pragma once

#include "../total_count.h"
#include "esphome/core/component.h"
#include "esphome/components/number/number.h"
#include "esphome/core/preferences.h"

namespace esphome {
namespace total_count {

class TotalCount;

class TotalCountNumber : public number::Number, public Component {
 public:
  void set_parent(TotalCount *parent) { this->parent_ = parent; };
  void dump_config() override;

 protected:
  void control(float value) override;

  TotalCount *parent_;
};

}  // namespace total_count
}  // namespace esphome
