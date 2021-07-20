#include <uebml.h>
#include <stdio.h>
#include <assert.h>

const uint8_t element_id_test_data[][8] = {
    { 0b10000000 },
    { 0b01000000, 0x00 },
    { 0b10000001 },
    { 0b01000000, 0x01 },
    { 0b10111111 },
    { 0b01000000, 0b00111111 },
    { 0xFF },
    { 0b01000000, 0b01111111 }
};

const int element_id_expected_return[8] = {
    EBML_E_IDZERO,
    EBML_E_IDZERO,
    EBML_E_OK,
    EBML_E_IDLONG,
    EBML_E_OK,
    EBML_E_IDLONG,
    EBML_E_IDONE,
    EBML_E_OK
};

const uint64_t element_id_value[8] = {
    0,
    0,
    0b00000001,
    0,
    0b00111111,
    0,
    0,
    0b0000000001111111
};

int main () {
    
    for (int i = 0; i < 8; i++) 
    {
        uint64_t VINT_DATA = 0;
        int ret = ebml_read_element_id(element_id_test_data[i], &VINT_DATA, 4);

        assert(ret == element_id_expected_return[i]);
        assert(VINT_DATA == element_id_value[i]);
        printf("[OK] ebml_read_element_id: ret=%d, id=%llu\n", ret, VINT_DATA);
    }

    uint64_t ii = 759;
    uint64_t iii = ii * 11400714819323198549ul;
    uint32_t iiii = iii >> (64 - 8);
    printf("%llu %llu %u\n", ii, iii, iiii);
}