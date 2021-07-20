#ifndef MKV_PARSER_H
#define MKV_PARSER_H

#include <stdint.h>

typedef enum ebml_err {
    EBML_E_OK = 0,
    EBML_E_VINTINVAL, /* invalid vint: VINT_MARKER not in first byte */
    EBML_E_IDZERO, /* Invalid Element ID: VINT_DATA is set to all 0 */
    EBML_E_IDONE, /* Invalid Element ID: VINT_DATA is set to all 1 */
    EBML_E_IDLONG, /* Invalid Element ID: shorter encoding is available */
    EBML_E_IDEXCEEDMAX, /* Invalid Element ID: Exeeds EBMLMaxIDLength */

} ebml_err;

typedef struct ebml_reader_s {
    
} ebml_reader_t;

int uebml_read_vint (uint8_t *buf, int *VINT_MARKER, int *VINT_WIDTH, uint64_t *VINT_DATA);
int uebml_read_vint2 (uint8_t *buf, uint64_t *VINT_DATA);
int uebml_read_element_id (uint8_t *buf, uint64_t *ElementID, int EBMLMaxIDLength);

#endif
