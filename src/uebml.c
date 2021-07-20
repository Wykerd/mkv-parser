#include <uebml.h>
#include <strings.h>
#include <arpa/inet.h>

static
int uebml_fls(int mask)
{
    int bit;

    if (mask == 0)
        return (0);
    for (bit = 1; mask != 1; bit++)
        mask = (unsigned int)mask >> 1;
    return (bit);
}

int uebml_read_vint (uint8_t *buf, int *VINT_MARKER, int *VINT_WIDTH, uint64_t *VINT_DATA) 
{
    int i, ss;

    *VINT_MARKER = uebml_fls(buf[0]);
    *VINT_WIDTH = 9 - (*VINT_MARKER);
    if ((*VINT_WIDTH) > 8)
        return EBML_E_VINTINVAL;

    *VINT_DATA = 0;
    ss = sizeof(uint64_t) - (*VINT_WIDTH);
    for (i = 0; i < (*VINT_WIDTH); i++)
        ((uint8_t*)VINT_DATA)[ss + i] = buf[i];
    ((uint8_t*)VINT_DATA)[ss] ^= (1 << ((*VINT_MARKER) - 1));
    *VINT_DATA = ntohll(*VINT_DATA);

    return EBML_E_OK;
}

int uebml_read_vint2 (uint8_t *buf, uint64_t *VINT_DATA)
{
    int VINT_MARKER, VINT_WIDTH;
    return uebml_read_vint(buf, &VINT_MARKER, &VINT_WIDTH, VINT_DATA);
};

int uebml_read_element_id (uint8_t *buf, uint64_t *ElementID, int EBMLMaxIDLength)
{
    static const uint64_t all_bits_table[] = {
        0b01111111ull,
        0b0011111111111111ull,
        0b000111111111111111111111ull,
        0b00001111111111111111111111111111ull,
        0b0000011111111111111111111111111111111111ull,
        0b000000111111111111111111111111111111111111111111ull,
        0b00000001111111111111111111111111111111111111111111111111ull,
        0b0000000011111111111111111111111111111111111111111111111111111111ull
    };

    static const uint8_t usable_bits_table[] = {
        7, 14, 21, 28, 35, 42, 49, 56
    };
    int VINT_MARKER, VINT_WIDTH, ret, max_id;
    uint64_t VINT_DATA;

    max_id = EBMLMaxIDLength > 4 ? EBMLMaxIDLength : 4;

    ret = uebml_read_vint(buf, &VINT_MARKER, &VINT_WIDTH, &VINT_DATA);

    if (ret)
        return ret;

    if (VINT_WIDTH > max_id)
        return EBML_E_IDEXCEEDMAX;

    if (VINT_DATA == 0)
        return EBML_E_IDZERO;

    if (VINT_DATA == all_bits_table[VINT_WIDTH - 1])
        return EBML_E_IDONE;

    int ff = usable_bits_table[VINT_WIDTH - 2];
    int fff = uebml_fls(VINT_DATA); 
    int f = (uebml_fls(VINT_DATA) <= usable_bits_table[VINT_WIDTH - 2]);

    if ((VINT_WIDTH != 1) && (uebml_fls(VINT_DATA) <= usable_bits_table[VINT_WIDTH - 2])&& (VINT_DATA != all_bits_table[VINT_WIDTH - 2]))
        return EBML_E_IDLONG;

    *ElementID = VINT_DATA;

    return EBML_E_OK;
}
