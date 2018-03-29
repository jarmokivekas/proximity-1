#include <stdint.h>

class CnS {
private:
	std::vector<uint8_t> attacher_synch_marker(3);	// 24, bits 0xFAF320
	std::vector<uint8_t> transfer_frame(256);			// max 2048 bits data link layer
	std::vector<uint8_t> cyclic_redundancy_check_32(32); // 32 bits
	bool is_pltu_egress_active;
	bool is_transmission_active; // true between acquisition and tail (inclusive)
public:
	CnS (frame);
	virtual ~CnS ();
	/* ASM is not part of the data checked my CRC */
	add_CRC32(trasfer_frame);
	add_ASM(trasfer_frame);

	/*the MBI parameters define the duration of the acqui and tail seq.
	The sequence is a cyclic Pseudo noise pattern (0x352EF853)*/
	/* NOTE: LDPC is a key term here, something to do with why it is
	important start the noise sequence from the most sinificant bit */
	acquisition_sequence(duration); // before PLTU transmisison
	idle_sequence(duration);  // when no PLTU is available
	tail_sequence(duration);	// before terminating transmission

	/* save the time stamp of the trailing edge of the last
	bit in the ASM of a PTLU. provide it to the MAC on request */
	save_ASM_egress_timestamp(){}
};

CnS::CnS(){
	this.add_ASM()
	this.add_CRC32()
}


main(){

	CnS.acquisition_sequence();
	while(1){
		if (CNS.is_channel_access_request_received()){
			CnS.PLTU_seqence(CNS.read_frame());
		}
		else{
			CnS.idle_sequence();
		}
	}
	CnS.tail_sequence();
}
