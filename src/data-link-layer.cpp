#include <iostream>
#include <stdint.h>
struct transfer_frame_header {
	uint8_t version_num : 2;
	uint8_t qos_indicator: 1;
	uint8_t pdu_type: 1;
	uint8_t dfcid: 2;
	uint16_t space_craft_id: 10;
	uint8_t pysical_channel_id: 1;
	uint8_t port_id: 3;
	uint8_t src_dest_id: 1;
	uint16_t frame_length: 11;
	uint8_t frame_seq_number: 8;
};

#pragma pack(push, 1)
struct transfer_frame_header_packed {
	uint8_t version_num : 2;
	uint8_t qos_indicator: 1;
	uint8_t pdu_type: 1;
	uint8_t dfcid: 2;
	uint16_t space_craft_id: 10;
	uint8_t pysical_channel_id: 1;
	uint8_t port_id: 3;
	uint8_t src_dest_id: 1;
	uint16_t frame_length: 11;
	uint8_t frame_seq_number: 8;
};
#pragma pack(pop)

int main(int argc, char const *argv[]) {
	transfer_frame_header header = {
		0b01, 0b1, 0b1,0b00, 0b1111101111,
		0b1,0b111,0b1,0b01100000110,0b11111111
	};
	std::cout << sizeof(header) << "\n";
	std::cout << (int)header.space_craft_id << "\n";
	transfer_frame_header_packed packed_header = {
		0b01, 0b1, 0b1,0b00, 0b1111101111,
		0b1,0b111,0b1,0b01100000110,0b11111111
	};
	std::cout << sizeof(packed_header) << "\n";
	std::cout << (int)packed_header.space_craft_id << "\n";
	return 0;
}
