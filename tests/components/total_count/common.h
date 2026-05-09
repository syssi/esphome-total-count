#pragma once
#include "esphome/components/total_count/total_count.h"

namespace esphome::total_count::testing {

class TestableTotalCount : public TotalCount {
 public:
  using TotalCount::process_new_state_;
};

}  // namespace esphome::total_count::testing
