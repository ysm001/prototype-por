#include "gtest/gtest.h"
#include "./action_test.h"

TEST_F(ActionTest, SimulatesTsst) {
  EXPECT_TRUE(get_left_fork1_->Simulates(get_right_fork1_));
  EXPECT_TRUE(get_left_fork2_->Simulates(get_right_fork2_));
}

TEST_F(ActionTest, DisablesTsst) {
  EXPECT_TRUE(get_left_fork1_->Disables(get_right_fork2_));
  EXPECT_TRUE(get_right_fork2_->Disables(get_left_fork1_));
}

TEST_F(ActionTest, InfluencesTest) {
  EXPECT_TRUE(get_left_fork1_->Influences(get_right_fork1_));
  EXPECT_TRUE(get_left_fork2_->Influences(get_right_fork2_));

  EXPECT_TRUE(get_left_fork1_->Influences(get_right_fork2_));
  EXPECT_TRUE(get_right_fork2_->Influences(get_left_fork1_));
}

TEST_F(ActionTest, CalcPrimeCauseTest) {
  Word glf1{get_left_fork1_};
  Word glf1_grf1{get_left_fork1_, get_right_fork1_};

  Word prime_cause;
  get_right_fork1_->CalcPrimeCause(glf1, &prime_cause);

  prime_cause.clear();
  put_left_fork1_->CalcPrimeCause(glf1_grf1, &prime_cause);
}
