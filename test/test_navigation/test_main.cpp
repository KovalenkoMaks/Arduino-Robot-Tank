#include <unity.h>

#include "drive.h"
#include "light_steering.h"
#include "obstacle_planner.h"
#include "serial_command.h"

namespace {

constexpr DriveSpeeds SPEEDS = {200, 150, 120};
constexpr int THRESHOLD = 500;
constexpr long DEAD_END_CM = 10;

void assertDrive(Drive expected, Drive actual) {
  TEST_ASSERT_EQUAL_UINT8(static_cast<uint8_t>(expected), static_cast<uint8_t>(actual));
}

void assertTracks(int16_t left, int16_t right, Drive direction) {
  const TrackSpeeds tracks = trackSpeeds(direction, SPEEDS);
  TEST_ASSERT_EQUAL_INT16(left, tracks.left);
  TEST_ASSERT_EQUAL_INT16(right, tracks.right);
}

void test_tracks_run_together_when_driving_straight() {
  assertTracks(200, 200, Drive::Forward);
  assertTracks(-150, -150, Drive::Backward);
}

void test_tracks_run_opposite_when_turning() {
  assertTracks(-120, 120, Drive::Left);
  assertTracks(120, -120, Drive::Right);
}

void test_tracks_stop() {
  assertTracks(0, 0, Drive::Stop);
}

void test_light_ahead_drives_forward() {
  assertDrive(Drive::Forward, steerToLight(800, 700, THRESHOLD));
}

void test_light_on_one_side_turns_to_it() {
  assertDrive(Drive::Left, steerToLight(800, 100, THRESHOLD));
  assertDrive(Drive::Right, steerToLight(100, 800, THRESHOLD));
}

void test_no_light_stops() {
  assertDrive(Drive::Stop, steerToLight(100, 200, THRESHOLD));
}

void test_reading_equal_to_threshold_is_not_lit() {
  assertDrive(Drive::Stop, steerToLight(THRESHOLD, THRESHOLD, THRESHOLD));
}

void test_serial_commands() {
  Drive direction = Drive::Stop;

  TEST_ASSERT_TRUE(parseDriveCommand('U', direction));
  assertDrive(Drive::Forward, direction);
  TEST_ASSERT_TRUE(parseDriveCommand('D', direction));
  assertDrive(Drive::Backward, direction);
  TEST_ASSERT_TRUE(parseDriveCommand('L', direction));
  assertDrive(Drive::Left, direction);
  TEST_ASSERT_TRUE(parseDriveCommand('R', direction));
  assertDrive(Drive::Right, direction);
  TEST_ASSERT_TRUE(parseDriveCommand('S', direction));
  assertDrive(Drive::Stop, direction);
}

void test_serial_commands_ignore_case() {
  Drive direction = Drive::Stop;

  TEST_ASSERT_TRUE(parseDriveCommand('u', direction));
  assertDrive(Drive::Forward, direction);
}

void test_unknown_serial_command_changes_nothing() {
  Drive direction = Drive::Left;

  TEST_ASSERT_FALSE(parseDriveCommand('x', direction));
  TEST_ASSERT_FALSE(parseDriveCommand('\n', direction));
  assertDrive(Drive::Left, direction);
}

void test_maneuver_turns_to_the_freer_side() {
  assertDrive(Drive::Left, planManeuver(80, 30, DEAD_END_CM).second.move);
  assertDrive(Drive::Right, planManeuver(30, 80, DEAD_END_CM).second.move);
}

void test_maneuver_backs_up_first() {
  assertDrive(Drive::Backward, planManeuver(80, 30, DEAD_END_CM).first.move);
  assertDrive(Drive::Backward, planManeuver(5, 5, DEAD_END_CM).first.move);
}

void test_maneuver_is_longer_in_a_dead_end() {
  const Maneuver open = planManeuver(80, 30, DEAD_END_CM);
  const Maneuver deadEnd = planManeuver(5, 7, DEAD_END_CM);

  TEST_ASSERT_GREATER_THAN_UINT16(open.first.durationMs, deadEnd.first.durationMs);
  TEST_ASSERT_GREATER_THAN_UINT16(open.second.durationMs, deadEnd.second.durationMs);
}

void test_one_blocked_side_is_not_a_dead_end() {
  const Maneuver open = planManeuver(80, 30, DEAD_END_CM);
  const Maneuver oneSide = planManeuver(5, 40, DEAD_END_CM);

  assertDrive(Drive::Right, oneSide.second.move);
  TEST_ASSERT_EQUAL_UINT16(open.first.durationMs, oneSide.first.durationMs);
}

}  // namespace

void setUp() {}

void tearDown() {}

int main() {
  UNITY_BEGIN();
  RUN_TEST(test_tracks_run_together_when_driving_straight);
  RUN_TEST(test_tracks_run_opposite_when_turning);
  RUN_TEST(test_tracks_stop);
  RUN_TEST(test_light_ahead_drives_forward);
  RUN_TEST(test_light_on_one_side_turns_to_it);
  RUN_TEST(test_no_light_stops);
  RUN_TEST(test_reading_equal_to_threshold_is_not_lit);
  RUN_TEST(test_serial_commands);
  RUN_TEST(test_serial_commands_ignore_case);
  RUN_TEST(test_unknown_serial_command_changes_nothing);
  RUN_TEST(test_maneuver_turns_to_the_freer_side);
  RUN_TEST(test_maneuver_backs_up_first);
  RUN_TEST(test_maneuver_is_longer_in_a_dead_end);
  RUN_TEST(test_one_blocked_side_is_not_a_dead_end);
  return UNITY_END();
}
