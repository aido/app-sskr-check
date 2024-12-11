/* @BANNER@ */

#include <lcx_hmac.h>
#include <lcx_sha3.h>

#include "ui.h"
#include "constants.h"
#include "common.h"
#include "./seed_rom_variables.h"

extern uint8_t base64_encode_64bytes(const uint8_t* src, char* dst);
extern uint8_t base85_encode_64bytes(const uint8_t* src, char* dst);

/**
 * @brief Generates BIP85 entropy from a device's seed using a specified BIP32 path.
 *
 * @details This function derives a root key from the device's seed using the provided BIP32
 *          path. It then calculates BIP85 entropy from this root key using a HMAC-SHA512 hash
 *          with a specific key.
 *
 * @param[out] entropy  Pointer to a buffer where the generated BIP85 entropy will be stored.
 * @param[in]  path     Pointer to an array of BIP32 path components.
 * @param[in]  path_len Length of the BIP32 path in components.
 *
 * @return 1 on success, 0 on failure.
 */
bool bolos_ux_bip85_entropy(uint8_t* entropy, const unsigned int* path, unsigned int path_len) {
    // get rootkey from device's seed
    if (os_derive_bip32_no_throw(CX_CURVE_256K1, path, path_len, entropy, entropy + 32) != CX_OK) {
        PRINTF("An error occurred while generating BIP85 entropy\n");
        return 0;
    }
    PRINTF("Root key from device: \n%.*H\n", 32, entropy);

    // Generate BIP85 entropy from root key
    cx_hmac_sha512_t ctx;
    const char key[] = "bip-entropy-from-k";

    LEDGER_ASSERT(cx_hmac_sha512_init_no_throw(&ctx, (const uint8_t*) key, strlen(key)) == CX_OK,
                  "HMAC init failed");
    LEDGER_ASSERT(
        cx_hmac_no_throw((cx_hmac_t*) &ctx, CX_LAST, entropy, 32, entropy, BIP85_ENTROPY_LENGTH) ==
            CX_OK,
        "HMAC failed");
    PRINTF("BIP85 entropy from root key:\n%.*H\n", BIP85_ENTROPY_LENGTH, entropy);

    return 1;
}

/**
 * @brief Generates a random digest using SHAKE-256.
 *
 * @details This function generates a random digest of the specified length using the SHAKE-256
 *          hash function, seeded with the provided seed data.
 *
 * @param[out] digest         Pointer to the buffer to store the generated digest.
 * @param[in]  digest_length  Length of the digest in bytes.
 * @param[in]  seed           Pointer to the seed data.
 * @param[in]  seed_length    Length of the seed data in bytes.
 *
 * @return 1 on success, 0 on failure.
 */
bool bolos_ux_bip85_drng_with_seed(uint8_t* seed,
                                   size_t seed_length,
                                   uint8_t* digest,
                                   size_t digest_length) {
    LEDGER_ASSERT(digest_length <= BIP85_DRNG_MAX_DIGEST_SIZE,
                  "BIP85 DRNG digest length exceeds maximum");
    if (cx_shake256_hash(seed, seed_length, digest, digest_length) != CX_OK) {
        PRINTF("SHAKE256 hash error\n");
        return 0;
    }
    PRINTF("BIP85 DRNG output:\n%.*H\n", digest_length, digest);

    return 1;
}

/**
 * @brief Generates a random digest using BIP85 DRNG.
 *
 * @details This function generates a random digest of the specified length using the BIP85
 *          Deterministic Random Number Generator (DRNG). The DRNG is seeded with entropy
 *          derived from a specific BIP85 derivation path.
 *
 * @param[out] digest         Pointer to the buffer to store the generated digest.
 * @param[in]  digest_length  Length of the digest in bytes.
 * @param[in]  index          Index used to differentiate different random number generations.
 *
 * @return None
 */
void bolos_ux_bip85_drng_test(uint8_t* digest, size_t digest_length, unsigned int index) {
    // m / purpose'   / app_no' / index'
    // m / 83696968'  / 0'      / index'
    const unsigned int path[] = {0x84FD1D48, 0x80000000, 0x80000000 | index};

    uint8_t buffer[BIP85_ENTROPY_LENGTH];

    LEDGER_ASSERT(bolos_ux_bip85_entropy(buffer, path, ARRAYLEN(path)) == 1,
                  "BIP85 entropy failed");

    LEDGER_ASSERT(
        bolos_ux_bip85_drng_with_seed(buffer, BIP85_ENTROPY_LENGTH, digest, digest_length) == 1,
        "BIP85 SHAKE256 hash failed");

    memzero(buffer, BIP85_ENTROPY_LENGTH);
}

void bolos_ux_bip85_bip39(uint8_t* hex_out, uint8_t language, uint8_t words, unsigned int index) {
    LEDGER_ASSERT(
        (words >= BIP39_MNEMONIC_SIZE_12) && (words % 3 == 0) && (words <= BIP39_MNEMONIC_SIZE_24),
        "Invalid value for BIP85 BIP89 words");

    // m / purpose'   / app_no' / language' / words' / index'
    // m / 83696968'  / 39'     / language' / words' / index'
    const unsigned int path[] = {0x84FD1D48,
                                 0x80000027,
                                 0x80000000 | language,
                                 0x80000000 | words,
                                 0x80000000 | index};

    uint8_t buffer[BIP85_ENTROPY_LENGTH];

    LEDGER_ASSERT(bolos_ux_bip85_entropy(buffer, path, ARRAYLEN(path)) == 1,
                  "BIP85 entropy failed");

    memcpy(hex_out, buffer, words * 4 / 3);
    memzero(buffer, BIP85_ENTROPY_LENGTH);

    PRINTF("BIP85 BIP39 hex output:\n%.*H\n", words * 4 / 3, hex_out);
}

void bolos_ux_bip85_hex(uint8_t* hex_out, uint8_t num_bytes, unsigned int index) {
    LEDGER_ASSERT((num_bytes >= 16) && (num_bytes <= BIP85_ENTROPY_LENGTH),
                  "Invalid value for BIP85 HEX length");

    // m / purpose'   / app_no' / num_bytes' / index'
    // m / 83696968'  / 128169' / num_bytes' / index'
    const unsigned int path[] = {0x84FD1D48,
                                 0x8001F4A9,
                                 0x80000000 | num_bytes,
                                 0x80000000 | index};

    uint8_t buffer[BIP85_ENTROPY_LENGTH];

    LEDGER_ASSERT(bolos_ux_bip85_entropy(buffer, path, ARRAYLEN(path)) == 1,
                  "BIP85 entropy failed");

    memcpy(hex_out, buffer, num_bytes);
    memzero(buffer, BIP85_ENTROPY_LENGTH);

    PRINTF("BIP85 HEX output:\n%.*H\n", num_bytes, hex_out);
}

void bolos_ux_bip85_pwd_base64(char* pwd, uint8_t pwd_len, unsigned int index) {
    LEDGER_ASSERT((pwd_len >= 20) && (pwd_len <= BASE64_ENCODE_LENGTH - 2),
                  "Invalid value for BIP85 PWD BASE64 length");

    // m / purpose'   / app_no' / pwd_len' / index'
    // m / 83696968'  / 707764' / pwd_len' / index'
    const unsigned int path[] = {0x84FD1D48, 0x800ACCB4, 0x80000000 | pwd_len, 0x80000000 | index};
    uint8_t buffer_ent[BIP85_ENTROPY_LENGTH];

    LEDGER_ASSERT(bolos_ux_bip85_entropy(buffer_ent, path, ARRAYLEN(path)) == 1,
                  "BIP85 entropy failed");

    char buffer_pwd[BASE64_ENCODE_LENGTH];

    LEDGER_ASSERT(base64_encode_64bytes(buffer_ent, buffer_pwd) == BASE64_ENCODE_LENGTH,
                  "Base64 encoding failed");

    memcpy(pwd, buffer_pwd, pwd_len);
    pwd[pwd_len] = '\0';  // Add string termination character

    memzero(buffer_ent, BIP85_ENTROPY_LENGTH);
    memzero(buffer_pwd, BASE64_ENCODE_LENGTH);

    PRINTF("BIP85 PWD BASE64 output: %s\n", pwd);
}

void bolos_ux_bip85_pwd_base85(char* pwd, uint8_t pwd_len, unsigned int index) {
    LEDGER_ASSERT((pwd_len >= 10) && (pwd_len <= BASE85_ENCODE_LENGTH),
                  "Invalid value for BIP85 PWD BASE85 length");

    // m / purpose'   / app_no' / pwd_len' / index'
    // m / 83696968'  / 707785' / pwd_len' / index'
    const unsigned int path[] = {0x84FD1D48, 0x800ACCC9, 0x80000000 | pwd_len, 0x80000000 | index};
    uint8_t buffer_ent[BIP85_ENTROPY_LENGTH];

    LEDGER_ASSERT(bolos_ux_bip85_entropy(buffer_ent, path, ARRAYLEN(path)) == 1,
                  "BIP85 entropy failed");

    char buffer_pwd[BASE85_ENCODE_LENGTH];

    LEDGER_ASSERT(base85_encode_64bytes(buffer_ent, buffer_pwd) == BASE85_ENCODE_LENGTH,
                  "Base85 encoding failed");

    memcpy(pwd, buffer_pwd, pwd_len);
    pwd[pwd_len] = '\0';  // Add string termination character

    memzero(buffer_ent, BIP85_ENTROPY_LENGTH);
    memzero(buffer_pwd, BASE85_ENCODE_LENGTH);

    PRINTF("BIP85 PWD BASE85 output: %s\n", pwd);
}

void bolos_ux_bip85_dice(uint32_t* out, uint32_t sides, uint32_t rolls, unsigned int index) {
    LEDGER_ASSERT((sides >= 2) && (sides <= UINT32_MAX), "Invalid value for BIP85 DICE sides");
    LEDGER_ASSERT((rolls >= 1) && (rolls <= UINT32_MAX), "Invalid value for BIP85 DICE rolls");

    // m / purpose'   / app_no' / sides' / rolls' / index'
    // m / 83696968'  / 89101' /  sides' / rolls' / index'
    const unsigned int path[] = {0x84FD1D48,
                                 0x80015C0D,
                                 0x80000000 | sides,
                                 0x80000000 | rolls,
                                 0x80000000 | index};

    uint8_t buffer_ent[BIP85_ENTROPY_LENGTH];
    uint8_t buffer_drng[BIP85_DRNG_MAX_DIGEST_SIZE], *buffer_ptr = buffer_drng;

    LEDGER_ASSERT(bolos_ux_bip85_entropy(buffer_ent, path, ARRAYLEN(path)) == 1,
                  "BIP85 entropy failed");
    LEDGER_ASSERT(bolos_ux_bip85_drng_with_seed(buffer_ent,
                                                BIP85_ENTROPY_LENGTH,
                                                buffer_drng,
                                                BIP85_DRNG_MAX_DIGEST_SIZE) == 1,
                  "BIP85 SHAKE256 hash failed");
    memzero(buffer_ent, BIP85_ENTROPY_LENGTH);

    uint8_t bits_per_roll = (sizeof(sides) << 3) - __builtin_clz(sides);
    PRINTF("BIP85 DICE bits per roll : %d\n", bits_per_roll);

    uint8_t bytes_per_roll = (bits_per_roll + 7) >> 3;
    PRINTF("BIP85 DICE bytes per roll : %d\n", bytes_per_roll);

    uint8_t shift_amount = (bytes_per_roll << 3) - bits_per_roll;

    for (uint32_t roll_result = 0, roll_index = 0;
         roll_index < rolls && buffer_ptr - buffer_drng < BIP85_DRNG_MAX_DIGEST_SIZE;
         roll_result = 0) {
        // Construct roll result from bytes_per_roll bytes
        uint8_t* end_ptr = buffer_ptr + bytes_per_roll;
        while (buffer_ptr < end_ptr) {
            roll_result = roll_result << 8 | (uint32_t) *buffer_ptr++;
        }
        // Adjust roll result to keep only bits_per_roll
        roll_result >>= shift_amount;

        // Check if roll result is within valid range
        if (roll_result < sides) {
            out[roll_index++] = roll_result;
            PRINTF("BIP85 DICE roll %d : %d\n", roll_index, roll_result);
        }
    }
    memzero(buffer_drng, BIP85_DRNG_MAX_DIGEST_SIZE);
}
