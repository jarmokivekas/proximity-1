#include <iostream>
#include <stdint.h>


class LDCP_encoder {
private:
    uint8_t lfsr_generator_state;
    uin64_t 0347 76C7 2728 95B0
public:
    LDCP_encoder (arguments);
    virtual ~LDCP_encoder ();

};
LDCP_encoder::LDCP_encoder() {
    this->lfsr_generator_state = 0xff;
}

LDCP_encoder::next_random_bit() {
    uint8_t newbit;
    uint8_t outbit;
    uint8_t x = this->x;
    for (size_t i = 0; i < 40; i++) {
        outbit = x & 0x01;
        newbit = (
                     x ^
                     (x >> 1) ^
                     (x >> 2) ^
                     (x >> 3) ^
                     (x >> 4) ^
                     (x >> 6)
                 ) & 1;
        this->x = (x >> 1) | (newbit << 7);
    }
    return this->x
}
