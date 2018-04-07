#include <iostream>
#include <stdint.h>
#include <string.h>

const uint16_t MBI_MAXIMUM_FRAME_LENGTH = (5 + 2043);
const uint8_t CRC32_LEN = 4;
const uint8_t ASM_LEN = 3;
const uint8_t CNS_OVERHEAD_LEN = (CRC32_LEN + ASM_LEN);
const uint16_t PLTU_MAX_LEN = CNS_OVERHEAD_LEN + MBI_MAXIMUM_FRAME_LENGTH;
const uint8_t FRAME_START_OFFSET = 3 ; // verison 3 frame strart in PLTU;

const uint8_t TRANFER_FRAME_HEADER_LENGTH = 5;





class v3_transfer_frame_header {
private:
    uint8_t _buffer[TRANFER_FRAME_HEADER_LENGTH];

public:

    v3_transfer_frame_header (
        uint8_t transfer_frame_version_number,
        uint8_t quality_of_service_indicator,
        uint8_t pdu_type_id,
        uint8_t data_field_construction_identifier,
        uint16_t spacecraft_identifier,
        uint8_t pysical_channel_identifier,
        uint8_t port_identifier,
        uint8_t source_destination_identifier,
        uint16_t frame_length,
        uint8_t frame_sequence_number
    ){
        memset(_buffer, 0x00, sizeof(uint8_t) * TRANFER_FRAME_HEADER_LENGTH);
        _buffer[0] |= (transfer_frame_version_number << 6);
        _buffer[0] |= quality_of_service_indicator << 5;
        _buffer[0] |= pdu_type_id << 4;
        _buffer[0] |= data_field_construction_identifier << 2;
        _buffer[0] |= 0xff00 & spacecraft_identifier >> 8;
        _buffer[1] |= 0x00ff & spacecraft_identifier;
        _buffer[2] |= pysical_channel_identifier << 7;
        _buffer[2] |= port_identifier << 4;
        _buffer[2] |= source_destination_identifier << 3;
        _buffer[2] |= frame_length >> 8;
        _buffer[3] |= frame_length;
        _buffer[4] |= frame_sequence_number;
    };

    uint8_t transfer_frame_version_number(void){
        return  (0b11000000 & _buffer[0]) >> 6;
    };
    uint8_t quality_of_service_indicator(void){
        return  (0b00100000 & _buffer[0]) >> 5;
    };
    uint8_t pdu_type_id(void){
        return  (0b00010000 & _buffer[0]) >> 4;
    };
    uint8_t data_field_construction_identifier(void){
        return  (0b00001100 & _buffer[0]) >> 2;
    };
    uint16_t spacecraft_identifier(void){
        return ((0b00000011 & _buffer[0]) << 8) | _buffer[1];
    };
    uint8_t pysical_channel_identifier(void){
        return  (0b10000000 & _buffer[2]) >> 7;
    };
    uint8_t port_identifier(void){
        return  (0b01110000 & _buffer[2]) >> 4;
    };
    uint8_t source_destination_identifier(void){
        return  (0b00001000 & _buffer[2]) >> 3;
    };
    uint16_t frame_length(void){
        return ((0b00000111 & _buffer[2]) << 8) | _buffer[3];
    };
    uint8_t frame_sequence_number(void){
        return  _buffer[4];
    };

    v3_transfer_frame_header(uint8_t transfer_frame_header_buffer[TRANFER_FRAME_HEADER_LENGTH]){
        memcpy(_buffer, transfer_frame_header_buffer, sizeof(uint8_t)*TRANFER_FRAME_HEADER_LENGTH);
    };
};







/* data link layed setcion B2 implementation
SPDU TYPE 1: Directive/report/PLCW SPDU data field
*/


class type_1_spdu_data_field {
protected:
    uint8_t _data_field[2];

    void from_buffer(uint8_t data_field[2]) {
        _data_field[0] = data_field[0];
        _data_field[1] = data_field[1];
    };
public:
    // accessor for directive type field is shared between subclasses
    uint8_t directive_type(void) {
        return 0b00000111 & _data_field[1];
    };
    // use for figuring out the directive type, in order to construct the correct subclass
    uint8_t directive_type(uint8_t *data_field) {
        return 0b00000111 & data_field[1];
    };
};


class SPDU_directive_set_control_parameters: public type_1_spdu_data_field {

public:

    /* constructor for building directive for transmitting */
    SPDU_directive_set_control_parameters(uint8_t time_sample, uint8_t duplex,uint8_t reserved,uint8_t remote_no_more_data,uint8_t token, uint8_t directive_type) {
        _data_field[0] |= (time_sample << 2);
        _data_field[0] |= (duplex >> 1); // field on byte boundary
        _data_field[1] |= (duplex << 7);
        _data_field[1] |= (reserved << 5);
        _data_field[1] |= (remote_no_more_data << 4);
        _data_field[1] |= (token << 3);
        _data_field[1] |= (directive_type << 0);
    };

    /* constructor for initializing directive from received data buffer */
    SPDU_directive_set_control_parameters(uint8_t data_field[2]) {
        from_buffer(data_field);
    };

    // accessor functions
    uint8_t time_sample(void)          {
        return (0b11111100 & _data_field[0]) >> 2;
    };
    uint8_t duplex(void)               {
        return ((0b00000011 & _data_field[0]) << 1) | ((0b10000000 & _data_field[1]) >> 7) ;
    };
    uint8_t reserved(void)             {
        return (0b01100000 & _data_field[1]) >> 5;
    };
    uint8_t remote_no_more_data(void)  {
        return (0b00010000 & _data_field[1]) >> 4;
    };
    uint8_t token(void)                {
        return (0b00001000 & _data_field[1]) >> 3;
    };
    uint8_t *as_buffer() {
        return _data_field;
    };
};




class SPDU_directive_set_transmitter_parameters: public type_1_spdu_data_field {

public:
    /* constructor for building directive for transmitting */
    SPDU_directive_set_transmitter_parameters(uint8_t mode,uint8_t data_rate,uint8_t modulation,uint8_t data_encoding,uint8_t frequency,uint8_t directive_type) {
        _data_field[0] |= (mode << 5);
        _data_field[0] |= (data_rate << 1);
        _data_field[0] |= (modulation);
        _data_field[1] |= (data_encoding << 6);
        _data_field[1] |= (frequency << 3);
        _data_field[1] |= (directive_type);
    };
    /* constructor for initializing directive from received data buffer */
    SPDU_directive_set_transmitter_parameters(uint8_t data_field[2]) {
        from_buffer(data_field);
    };


    // accessor functions
    uint8_t mode(void)          {
        return (0b11100000 & _data_field[0]) >> 5;
    };
    uint8_t data_rate(void)     {
        return (0b00011110 & _data_field[0]) >> 1;
    };
    uint8_t modulation(void)    {
        return (0b00000001 & _data_field[0]) >> 0;
    };
    uint8_t data_encoding(void) {
        return (0b11000000 & _data_field[1]) >> 6;
    };
    uint8_t frequency(void)     {
        return (0b00111000 & _data_field[1]) >> 3;
    };
    uint8_t *as_buffer() {
        return _data_field;
    };
};






// enum directive_type_enum {
/* definitions of field values for `directive type` in spdu data field*/
#define SET_TRANSMITTER_PARAMETERS 0b000
#define SET_CONTROL_PARAMETERS 0b001
#define SET_RECEIVER_PARAMETERS 0b010
#define SET_V 0b011
#define REPORT_REQUEST 0b100
#define SET_PL_EXTENSION 0b110
#define REPORT_SOURCE_SCID 0b111
// };
