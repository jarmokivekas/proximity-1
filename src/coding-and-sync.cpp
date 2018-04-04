#include <stdint.h>
#include <iostream>


#define TRANSFER_FRAME_MAX_LEN 256
#define CRC32_LEN 4
#define ASM_LEN 3
#define CNS_OVERHEAD_LEN (CRC32_LEN + ASM_LEN)
#define PLTU_MAX_LEN CNS_OVERHEAD_LEN + TRANSFER_FRAME_MAX_LEN
#define FRAME_START_OFFSET 3 // verison 3 frame strart in PLTU

enum encoding {
	CNS_ENCODING_LDPC,
	CNS_ENCODING_CONVOLUTIONAL,
	CNS_ENCODING_BYPASS,
};

class CNS {
private:
	uint8_t attached_synch_marker[3] ={0xFA, 0xF3,0x20};
	uint8_t transfer_frame[256];			// max 2048 bits data link layer
	uint8_t cyclic_redundancy_check_32[4]; // 32 bits
	// bool is_pltu_egress_active;
	// bool is_transmission_active; // true between acquisition and tail (inclusive)
	void add_CRC32(uint8_t *transfer_frame);
	/* ASM is not part of the data checked my CRC */
	void add_ASM(uint8_t *transfer_frame);
public:


	CNS ();
	// virtual ~CNS ();

	uint8_t *encode(uint8_t *transfer_frame, uint16_t frame_length, enum encoding encoding);
	/*the MBI parameters define the duration of the acqui and tail seq.
	The sequence is a cyclic Pseudo noise pattern (0x352EF853)*/
	/* NOTE: LDPC is a key term here, something to do with why it is
	important start the noise sequence from the most sinificant bit */
	void acquisition_sequence(int duration); // before PLTU transmisison
	void idle_sequence(int duration);  // when no PLTU is available
	void tail_sequence(int duration);	// before terminating transmission

	/* save the time stamp of the trailing edge of the last
	bit in the ASM of a PTLU. provide it to the MAC on request */
	void save_ASM_egress_timestamp();
};

CNS::CNS(void){
	return;
}


uint8_t *CNS::encode(uint8_t *transfer_frame, uint16_t frame_length, enum encoding encoding){

}


int main(){
	printf("%i\n", PLTU_MAX_LEN);
	uint8_t pltu_buffer[PLTU_MAX_LEN] = {0x00,0xff,0xca,0xfe};
	uint16_t frame_length = 4;
	CNS cns;
	uint8_t *encoded_frame = cns.encode(frame, frame_length, CNS_ENCODING_BYPASS);
	return 0;
	// CNS.acquisition_sequence();
	// while(1){
	// 	if (CNS.is_channel_access_request_received()){
	// 		CNS.PLTU_seqence(CNS.read_frame());
	// 	}
	// 	else{
	// 		CNS.idle_sequence();
	// 	}
	// }
	// CNS.tail_sequence();
}
