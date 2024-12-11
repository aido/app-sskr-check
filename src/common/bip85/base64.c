/* @BANNER@ */

#include <os.h>

#include "./seed_rom_variables.h"

/**
 * @brief Encodes 64 bytes of data into a Base64 string.
 *
 * @param[in]  src Pointer to the input data.
 * @param[out] dst Pointer to the output buffer.
 *
 * @return The number of bytes written to the output buffer.
 */
uint8_t base64_encode_64bytes(const uint8_t *src, char *dst) {
    const uint8_t *src_end = src + BIP85_ENTROPY_LENGTH;
    char *dst_start = dst;
    uint32_t value;

    // Loop through the input in chunks of 3 bytes
    while (src < src_end) {
        // Combine three input bytes into a 24-bit value
        value = (src[0] << 16) | (src[1] << 8) | src[2];

        // Encode the value into 4 base64 characters
        for (uint8_t i = 0; i < 4; i++) {
            *dst++ = BASE64_TABLE[(value >> (18 - i * 6)) & 0x3F];
        }

        src += 3;  // Advance source pointer by 3 bytes
    }

    // Add the fixed padding (for 64-byte input)
    *(dst - 1) = '=';
    *(dst - 2) = '=';

    return dst - dst_start;  // Return the total number of characters written
}
