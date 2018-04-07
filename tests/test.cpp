#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"
#include <stdint.h>
#include "../src/data-link-layer.h"

TEST_GROUP(datalinklayer)
{
};




TEST(datalinklayer, SPDU_directive_set_control_parameters1){
    uint8_t data_field[2] = {0b00000100, 0b10111001};
    // initialize as from receive buffer
    SPDU_directive_set_control_parameters spdu = SPDU_directive_set_control_parameters(data_field);
    // make sure all values are correct
    CHECK_EQUAL(1, spdu.time_sample());
    CHECK_EQUAL(1, spdu.duplex());
    CHECK_EQUAL(1, spdu.reserved());
    CHECK_EQUAL(1, spdu.remote_no_more_data());
    CHECK_EQUAL(1, spdu.token());
    CHECK_EQUAL(1, spdu.directive_type());
}
TEST(datalinklayer, SPDU_directive_set_control_parameters2){
    // initialize as from receive buffer
    SPDU_directive_set_control_parameters spdu = SPDU_directive_set_control_parameters(1,1,1,1,1,1);
    // make sure all values are correct
    CHECK_EQUAL(1, spdu.time_sample());
    CHECK_EQUAL(1, spdu.duplex());
    CHECK_EQUAL(1, spdu.reserved());
    CHECK_EQUAL(1, spdu.remote_no_more_data());
    CHECK_EQUAL(1, spdu.token());
    CHECK_EQUAL(1, spdu.directive_type());
    // uint8_t data_field[2] = {0b00000100, 0b10111001};
}


int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
