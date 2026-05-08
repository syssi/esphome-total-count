#include <gtest/gtest.h>
#include "esphome/components/sensor/sensor.h"
#include "common.h"

namespace esphome::total_count::testing {

class TotalCountTest : public ::testing::Test {
 protected:
  TestableTotalCount counter_;
  sensor::Sensor total_count_sensor_;

  void SetUp() override {
    counter_.set_restore(false);
    counter_.set_initial_value(0);
    counter_.set_step(1);
    counter_.set_total_count_sensor(&total_count_sensor_);
  }
};

TEST_F(TotalCountTest, SetValuePublishes) {
  counter_.set_value(5.0f);
  EXPECT_FLOAT_EQ(total_count_sensor_.state, 5.0f);
}

TEST_F(TotalCountTest, PublishStateAndSave) {
  counter_.publish_state_and_save(42);
  EXPECT_FLOAT_EQ(total_count_sensor_.state, 42.0f);
}

TEST_F(TotalCountTest, ResetCounterToInitialValue) {
  counter_.set_value(99.0f);
  counter_.reset_counter();
  EXPECT_FLOAT_EQ(total_count_sensor_.state, 0.0f);
}

TEST_F(TotalCountTest, ResetCounterToCustomInitialValue) {
  counter_.set_initial_value(10);
  counter_.set_value(99.0f);
  counter_.reset_counter();
  EXPECT_FLOAT_EQ(total_count_sensor_.state, 10.0f);
}

TEST_F(TotalCountTest, ProcessNewStateIncrements) {
  counter_.publish_state_and_save(3);
  counter_.process_new_state_(true);
  EXPECT_FLOAT_EQ(total_count_sensor_.state, 4.0f);
}

TEST_F(TotalCountTest, ProcessNewStateFalseNoIncrement) {
  counter_.publish_state_and_save(3);
  counter_.process_new_state_(false);
  EXPECT_FLOAT_EQ(total_count_sensor_.state, 3.0f);
}

TEST_F(TotalCountTest, StepTwo) {
  counter_.set_step(2);
  counter_.publish_state_and_save(0);
  counter_.process_new_state_(true);
  EXPECT_FLOAT_EQ(total_count_sensor_.state, 2.0f);
}

TEST_F(TotalCountTest, MultipleIncrements) {
  counter_.publish_state_and_save(0);
  counter_.process_new_state_(true);
  counter_.process_new_state_(true);
  counter_.process_new_state_(true);
  EXPECT_FLOAT_EQ(total_count_sensor_.state, 3.0f);
}

TEST_F(TotalCountTest, NullSensorSafe) {
  TestableTotalCount bare;
  bare.set_restore(false);
  bare.set_initial_value(0);
  bare.set_step(1);
  EXPECT_NO_FATAL_FAILURE(bare.publish_state_and_save(5));
}

}  // namespace esphome::total_count::testing
