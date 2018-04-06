#include <iostream>
#include <stdint.h>

// class Transfer_frame_v3 {
// private:
// 	/* data */
//
// public:
// 	Transfer_frame_v3 (arguments);
// 	virtual ~Transfer_frame_v3 ();
// };
//
//


/* data link layed setcion B2 implementation
SPDU TYPE 1: Directive/report/PLCW SPDU data field
*/


class type_1_spdu_data_field {
private:
public:
	uint16_t data_field;
	uint8_t directive_type(void) {return (0b0000000000000111 & data_field) >> 0;};
	void directive_type(uint8_t val) {data_field |= (val << 0);};
};

/// subclasses by directive_type

class SPDU_directive_set_transmitter_parameters: public type_1_spdu_data_field {
public:
	/* Use the constructor to make sure all fields are explicilty set? */
	// SPDU_set_transmitter_parameters_directive (
	// 	uintt8_t mode,
	// 	uintt8_t data_rate,
	// 	uintt8_t modulation,
	// 	uintt8_t data_encoding,
	// 	uintt8_t frequency
	// );

	// accessor functions
	uint8_t mode(void)           {return (0b1110000000000000 & data_field) >> 13;};
	uint8_t data_rate(void)      {return (0b0001111000000000 & data_field) >> 9;};
	uint8_t modulation(void)     {return (0b0000000100000000 & data_field) >> 8;};
	uint8_t data_encoding(void)  {return (0b0000000011000000 & data_field) >> 6;};
	uint8_t frequency(void)      {return (0b0000000000111000 & data_field) >> 3;};

	// mutator functions
	void mode(uint8_t val)           { data_field |= (val << 13);};
	void data_rate(uint8_t val)      { data_field |= (val << 9);};
	void modulation(uint8_t val)     { data_field |= (val << 8);};
	void data_encoding(uint8_t val)  { data_field |= (val << 6);};
	void frequency(uint8_t val)      { data_field |= (val << 3);};
};


class SPDU_directive_set_control_parameters: public type_1_spdu_data_field {
public:
	// accessor functions
	uint8_t time_sample(void)          {return (0b1111110000000000 & data_field) >> 10;};
	uint8_t duplex(void)               {return (0b0000001110000000 & data_field) >> 7;};
	uint8_t reserved(void)             {return (0b0000000001100000 & data_field) >> 5;};
	uint8_t remote_no_more_data(void)  {return (0b0000000000010000 & data_field) >> 4;};
	uint8_t token(void)                {return (0b0000000000001000 & data_field) >> 3;};

	// mutator functions
	void time_sample(uint8_t val)          { data_field |= (val << 10);};
	void duplex(uint8_t val)               { data_field |= (val << 7);};
	void reserved(uint8_t val)             { data_field |= (val << 5);};
	void remote_no_more_data(uint8_t val)  { data_field |= (val << 4);};
	void token(uint8_t val)                { data_field |= (val << 1);};
};


class SPDU_directive_set_control_parameters_2: {
private:
	const uint8_t time_sample;
	const uint8_t duplex;
	const uint8_t reserved;
	const uint8_t remote_no_more_data;
	const uint8_t token;
public:

	/* constructor*/
	SPDU_directive_set_control_parameters(
		uint8_t time_sample,
		uint8_t duplex,
		uint8_t reserved,
		uint8_t remote_no_more_data,
		uint8_t token
	):
		time_sample(time_sample),
		duplex(duplex),
		reserved(reserved),
		remote_no_more_data(remote_no_more_data),
		token(token)
		{};

	uint16_t as_buffer16(){
		(time_sample           << 10) |
		(duplex                << 7) |
		(reserved              << 5) |
		(remote_no_more_data   << 4) |
		(token                 << 1)
	}

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
