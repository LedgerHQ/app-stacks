#include "parser.h"

#include <stddef.h>
#include <stdint.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    parser_tx_t txObj;
    parser_context_t ctx;
    parser_error_t rc;

    rc = parser_parse(&ctx, data, size);
    if (rc != parser_ok) {
        return 0;
    }
    return 0;
}

