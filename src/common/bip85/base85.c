/* @BANNER@ */

#include <os.h>

#include "./seed_rom_variables.h"

/**
 * @brief Encodes 64 bytes of data into a Base85 string.
 *
 * @param[in]  src Pointer to the input data.
 * @param[out] dst Pointer to the output buffer.
 *
 * @return The number of bytes written to the output buffer.
 */
uint8_t base85_encode_64bytes(const uint8_t *src, char *dst) {
    const uint8_t *src_end = src + BIP85_ENTROPY_LENGTH;  // Mark the end of the source array
    char *dst_start = dst;  // Save the starting address of the destination array
    uint32_t value;

    while (src < src_end) {
        // Load 4 bytes into a 32-bit value
        value = (src[0] << 24) | (src[1] << 16) | (src[2] << 8) | src[3];

        // Convert the value into 5 base85 characters
        for (int8_t i = 4; i >= 0; i--) {
            dst[i] = BASE85_TABLE[value % BASE85_TABLE_LENGTH];  // Select character
            value /= BASE85_TABLE_LENGTH;  // Divide by table length for next digit
        }

        dst += 5;  // Advance destination pointer
        src += 4;  // Advance source pointer
    }

    // Return the total number of characters written
    return dst - dst_start;
}
