
#include "../../models/time.h"
#include <limits.h>
#include "gtest/gtest.h"

TEST(Time, InitializeTimeClassWithZero) {
  Time time;
  EXPECT_EQ(0, time.get_hours());
  EXPECT_EQ(0, time.get_minutes());
  EXPECT_EQ(0, time.get_seconds());
  EXPECT_EQ(0, time.get_useconds());
}

TEST(Time, InitializeTimeClassWithNonZero) {
  Time time(1,2,3,4);
  EXPECT_EQ(1, time.get_hours());
  EXPECT_EQ(2, time.get_minutes());
  EXPECT_EQ(3, time.get_seconds());
  EXPECT_EQ(4, time.get_useconds());
}

TEST(Time, SetAllValue) {
  Time time;
  time.set(1,2,3,4);
  EXPECT_EQ(1, time.get_hours());
  EXPECT_EQ(2, time.get_minutes());
  EXPECT_EQ(3, time.get_seconds());
  EXPECT_EQ(4, time.get_useconds());
}

TEST(Time, SetAllHandleBoundary) {
  Time time;
  time.set(23,59,59,1000);
  EXPECT_EQ(0, time.get_hours());
  EXPECT_EQ(0, time.get_minutes());
  EXPECT_EQ(0, time.get_seconds());
  EXPECT_EQ(0, time.get_useconds());
}

TEST(Time, SetAllHandleHugeOverBoundary) {
  Time time;
  time.set(240,600,600,10101);
  EXPECT_EQ(10, time.get_hours());
  EXPECT_EQ(10, time.get_minutes());
  EXPECT_EQ(10, time.get_seconds());
  EXPECT_EQ(101, time.get_useconds());
}

TEST(Time, AddUTimeLessThanOneSecond) {
  Time time;
  time.u_add(500);
  EXPECT_EQ(0, time.get_hours());
  EXPECT_EQ(0, time.get_minutes());
  EXPECT_EQ(0, time.get_seconds());
  EXPECT_EQ(500, time.get_useconds());
}

TEST(Time, AddUTimeMoreThanOneSecond) {
  Time time;
  time.u_add(1255);
  EXPECT_EQ(0, time.get_hours());
  EXPECT_EQ(0, time.get_minutes());
  EXPECT_EQ(1, time.get_seconds());
  EXPECT_EQ(255, time.get_useconds());
}

TEST(Time, AddUTimeMoreThanOneMinute) {
  Time time;
  time.u_add(100+1000*65);
  EXPECT_EQ(0, time.get_hours());
  EXPECT_EQ(1, time.get_minutes());
  EXPECT_EQ(5, time.get_seconds());
  EXPECT_EQ(100, time.get_useconds());
}

TEST(Time, AddUTimeMoreThanOneHour) {
  Time time;
  time.u_add(100+1000*60*65);
  EXPECT_EQ(1, time.get_hours());
  EXPECT_EQ(5, time.get_minutes());
  EXPECT_EQ(0, time.get_seconds());
  EXPECT_EQ(100, time.get_useconds());
}
