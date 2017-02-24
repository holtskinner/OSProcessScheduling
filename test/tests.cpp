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

TEST(load_process_control_blocks, nullFilePath) {
  dyn_array_t *da = load_process_control_blocks(NULL);
  ASSERT_EQ(da, (dyn_array_t *)NULL);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// TEST(block_store_create, create) {
//   block_store_t *bs = NULL;
//   bs = block_store_create();
//   ASSERT_NE(nullptr, bs)
//       << "block_store_create returned NULL when it should not have\n";
//   // The below line will only run if the block store was created
//   successfully.
//   block_store_destroy(bs);

//   score += 10;
// }