#include "gtest/gtest.h"

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    std::cout << "AED 2023/2024 - CI2 DIST" << std::endl << std::endl;
    int res = RUN_ALL_TESTS();

    return res;
}
