#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

#include "../src/data-link-layer.h"

TEST_GROUP(datalinklayer)
{
};


TEST(datalinklayer, spdu1){
    SPDU_directive_set_control_parameters dir = SPDU_directive_set_control_parameters();
    dir.duplex(3);
    CHECK_EQUAL(3, dir.duplex());
}

TEST(datalinklayer, spdu2){
    type_1_spdu_data_field spdu = type_1_spdu_data_field();
    spdu.data_field = 0;
    CHECK_EQUAL(0, spdu.data_field);
    CHECK_EQUAL(0, spdu.directive_type());
    spdu.directive_type(0b001);
    CHECK_EQUAL(1, spdu.directive_type());
}


int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
