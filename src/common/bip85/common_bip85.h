#pragma once

#include <stdint.h>
#include <stddef.h>

// BIP85 applications
#include "./seed_rom_variables.h"

/**
 * @brief Generates BIP85 BIP39 mnemonic words using a specified BIP32 path.
 *
 * @details This function derives a root key from the device's seed using a BIP32 path of the form:
 *          m / purpose' / app_no' / language' / words' / index'.
 *          It then calculates BIP85 entropy from this root key and converts it to BIP39 mnemonic
 *          words using the specified language and number of words.
 *
 * @param[out] hex_out  Pointer to a buffer where the generated BIP85 BIP39 mnemonic words in
 *                      hexadecimal format will be stored.
 * @param[in]  language Language code for the mnemonic words.
 * @param[in]  words    Number of mnemonic words to generate.
 * @param[in]  index    Index to be used in the BIP32 path.
 */
void bolos_ux_bip85_bip39(uint8_t* hex_out, uint8_t language, uint8_t words, unsigned int index);

/**
 * @brief Generates BIP85 HEX output using a specified BIP32 path.
 *
 * @details This function derives a root key from the device's seed using a BIP32 path of the form:
 *          m / purpose' / app_no' / num_bytes' / index'.
 *          It then calculates BIP85 entropy from this root key and returns the first `num_bytes` as
 *          hexadecimal output.
 *
 * @param[out] hex_out   Pointer to a buffer where the generated BIP85 HEX output will be stored.
 * @param[in]  num_bytes Number of bytes to generate.
 * @param[in]  index     Index to be used in the BIP32 path.
 */
void bolos_ux_bip85_hex(uint8_t* hex_out, uint8_t num_bytes, unsigned int index);

/**
 * @brief Generates BIP85 Base64 password using a specified BIP32 path.
 *
 * @details This function derives a root key from the device's seed using a BIP32 path of the form:
 *          m / purpose' / app_no' / pwd_len' / index'.
 *          It then calculates BIP85 entropy from this root key and encodes it to Base64, truncating
 *          to the specified password length.
 *
 * @param[out] pwd     Pointer to a buffer where the generated BIP85 Base64 password will be stored.
 * @param[in]  pwd_len Length of the password in bytes.
 * @param[in]  index   Index to be used in the BIP32 path.
 */
void bolos_ux_bip85_pwd_base64(char* pwd, uint8_t pwd_len, unsigned int index);

/**
 * @brief Generates BIP85 Base85 password using a specified BIP32 path.
 *
 * @details This function derives a root key from the device's seed using a BIP32 path of the form:
 *          m / purpose' / app_no' / pwd_len' / index'.
 *          It then calculates BIP85 entropy from this root key and encodes it to Base85, truncating
 *          to the specified password length.
 *
 * @param[out] pwd     Pointer to a buffer where the generated BIP85 Base85 password will be stored.
 * @param[in]  pwd_len Length of the password in bytes.
 * @param[in]  index   Index to be used in the BIP32 path.
 */
void bolos_ux_bip85_pwd_base85(char* pwd, uint8_t pwd_len, unsigned int index);

/**
 * @brief Generates a series of random dice rolls using BIP85.
 *
 * @details This function simulates the rolling of dice with the specified number of sides and
 *          rolls. It utilizes the BIP85 standard to ensure cryptographic security and randomness.
 *
 * @param[out] out    Pointer to an array of `uint32_t` to store the generated dice rolls.
 * @param[in]  sides  Number of sides on each die (must be between 2 and UINT32_MAX).
 * @param[in]  rolls  Number of dice rolls to generate (must be between 1 and UINT32_MAX).
 * @param[in]  index  Index to be used in the BIP32 path.
 */
void bolos_ux_bip85_dice(uint32_t* out, uint32_t sides, uint32_t rolls, unsigned int index);
