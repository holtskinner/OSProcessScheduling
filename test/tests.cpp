#include <fcntl.h>
#include <gtest/gtest.h>
#include <stdio.h>

#include "dyn_array.h"
#include "processing_scheduling.h"

// Refer to https://github.com/google/googletest/blob/master/googletest/docs/Documentation.md
// for help

TEST(load_process_control_blocks, nullFilePath) {
    dyn_array_t *da = load_process_control_blocks(NULL);
    ASSERT_EQ(da, (dyn_array_t *) NULL);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
