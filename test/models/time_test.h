#include "../../models/time.h"

Time time;

TEST "Init time"
ASSERT_EQ time.get_hour(), 0
ASSERT_EQ time.get_minute(), 0
ASSERT_EQ time.get_second(), 0
ASSERT_EQ time.get_usecond(), 0

TEST "Adding usecond"
time.u_add(500);
ASSERT_EQ time.get_hour(), 0
ASSERT_EQ time.get_minute(), 0
ASSERT_EQ time.get_second(), 0
ASSERT_EQ time.get_usecond(), 500

TEST "increment second"
time.u_add(501);
ASSERT_EQ time.get_hour(), 0
ASSERT_EQ time.get_minute(), 0
ASSERT_EQ time.get_second(), 1
ASSERT_EQ time.get_usecond(), 1

TEST "increment minute"
time.u_add(60*1000);
ASSERT_EQ time.get_hour(), 0
ASSERT_EQ time.get_minute(), 1
ASSERT_EQ time.get_second(), 1
ASSERT_EQ time.get_usecond(), 1

TEST "increment hour"
time.u_add(60*1000*24);
ASSERT_EQ time.get_hour(), 1
ASSERT_EQ time.get_minute(), 1
ASSERT_EQ time.get_second(), 1
ASSERT_EQ time.get_usecond(), 1

TEST "set time"
time.set(1,2,3,4);
ASSERT_EQ time.get_hour(), 1
ASSERT_EQ time.get_minute(), 2
ASSERT_EQ time.get_second(), 3
ASSERT_EQ time.get_usecond(), 4
