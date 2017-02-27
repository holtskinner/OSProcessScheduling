#include <fcntl.h>
#include <gtest/gtest.h>
#include <pthread.h>
#include <stdio.h>
#include "../src/process_scheduling.c"
#include "dyn_array.h"
#include "process_scheduling.h"

// Using a C library requires extern "C" to prevent function managling
extern "C" {
#include <dyn_array.h>
}

// Refer to
// https://github.com/google/googletest/blob/master/googletest/docs/Documentation.md
// for help

#define NUM_PCB 30

unsigned int score;
unsigned int total;

class GradeEnvironment : public testing::Environment {
 public:
  virtual void SetUp() {
    score = 0;
#if GRAD_TESTS
    total = 126;
#else
    total = 100;
#endif
  }
  virtual void TearDown() {
    ::testing::Test::RecordProperty("points_given", score);
    ::testing::Test::RecordProperty("points_total", total);
    std::cout << "SCORE: " << score << '/' << total << std::endl;
  }
};

// Load Process Control Block Test Cases

TEST(load_process_control_blocks, nullFilePath) {
  dyn_array_t *array = load_process_control_blocks(NULL);
  ASSERT_EQ(array, (dyn_array_t *)NULL);
}

TEST(load_process_control_blocks, emptyFilePath) {
  dyn_array_t *array = load_process_control_blocks("");
  ASSERT_EQ(array, (dyn_array_t *)NULL);
}

TEST(load_process_control_blocks, goodFile) {
  const char *src_file = "input.txt";
  dyn_array_t *array = load_process_control_blocks(src_file);
  ASSERT_NE(array, (dyn_array_t *)NULL);
  free(array);
}

// First Come First Served Test Cases

TEST(first_come_first_serve, nullQueue) {
  dyn_array_t *ready_queue = NULL;
  ScheduleResult_t *result = new ScheduleResult_t;
  bool output = first_come_first_serve(ready_queue, result);
  ASSERT_EQ(output, false);
}

TEST(first_come_first_serve, nullResult) {
  dyn_array_t *ready_queue =
      dyn_array_create(0, sizeof(ProcessControlBlock_t), NULL);
  ScheduleResult_t *result = NULL;
  bool output = first_come_first_serve(ready_queue, result);
  ASSERT_EQ(output, false);
}

TEST(first_come_first_serve, goodInput) {
  dyn_array_t *ready_queue =
      dyn_array_create(0, sizeof(ProcessControlBlock_t), NULL);
  ScheduleResult_t *result = new ScheduleResult_t;
  // fill with data
  bool output = first_come_first_serve(ready_queue, result);
  ASSERT_EQ(output, true);
}

// Priority Queue Test Cases

TEST(priority, nullQueue) {
  dyn_array_t *ready_queue = NULL;
  ScheduleResult_t *result = new ScheduleResult_t;
  bool output = priority(ready_queue, result);
  ASSERT_EQ(output, false);
}

TEST(priority, nullResult) {
  dyn_array_t *ready_queue =
      dyn_array_create(0, sizeof(ProcessControlBlock_t), NULL);
  ScheduleResult_t *result = NULL;
  bool output = priority(ready_queue, result);
  ASSERT_EQ(output, false);
}

TEST(priority, goodInput) {
  dyn_array_t *ready_queue =
      dyn_array_create(0, sizeof(ProcessControlBlock_t), NULL);
  ScheduleResult_t *result = new ScheduleResult_t;
  // fill with data
  bool output = priority(ready_queue, result);
  ASSERT_EQ(output, true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
