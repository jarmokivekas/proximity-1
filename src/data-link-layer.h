#include <iostream>
#include <stdint.h>



uint8_t version_num ;
uint8_t qos_indicator;
uint8_t pdu_type;
uint8_t dfcid;
uint16_t space_craft_id;
uint8_t pysical_channel_id;
uint8_t port_id;
uint8_t src_dest_id;
uint16_t frame_length;
uint8_t frame_seq_number;







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
