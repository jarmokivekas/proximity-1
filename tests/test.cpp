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
}


TEST(datalinklayer, SPDU_directive_set_transmitter_parameters){
    SPDU_directive_set_transmitter_parameters spdu = SPDU_directive_set_transmitter_parameters(1,1,1,1,1,1);
    CHECK_EQUAL(1, spdu.mode());
    CHECK_EQUAL(1, spdu.data_rate());
    CHECK_EQUAL(1, spdu.modulation());
    CHECK_EQUAL(1, spdu.data_encoding());
    CHECK_EQUAL(1, spdu.frequency());
}
TEST(datalinklayer, SPDU_directive_set_transmitter_parameters_size){
    SPDU_directive_set_transmitter_parameters spdu = SPDU_directive_set_transmitter_parameters(1,1,1,1,1,1);
    CHECK_EQUAL(2, sizeof(spdu));
}


TEST(datalinklayer, transfer_frame_header_interface_init){
    v3_transfer_frame_header header = v3_transfer_frame_header(1,1,1,1,1,1,1,1,1,1);
    CHECK_EQUAL(1, header.transfer_frame_version_number());
    CHECK_EQUAL(1, header.quality_of_service_indicator());
    CHECK_EQUAL(1, header.pdu_type_id());
    CHECK_EQUAL(1, header.data_field_construction_identifier());
    CHECK_EQUAL(1, header.spacecraft_identifier());
    CHECK_EQUAL(1, header.pysical_channel_identifier());
    CHECK_EQUAL(1, header.port_identifier());
    CHECK_EQUAL(1, header.source_destination_identifier());
    CHECK_EQUAL(1, header.frame_length());
    CHECK_EQUAL(1, header.frame_sequence_number());
    CHECK_EQUAL(sizeof(uint8_t)*5 , sizeof(header))
}

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
