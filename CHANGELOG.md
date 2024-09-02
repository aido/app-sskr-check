# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.8.0] - 2024-09-02

### Added

- Add Stax layouts for generating SSKR shares
- Add Stax layouts for checking SSKR shares
- Add Stax layouts for recovering BIP39 phrase
- Add screenshots and animations
- Add demo videos for Stax and Nano S
- Add Stax function tests

## [1.7.4] - 2024-06-20

### Fixed

- Ensure result does not overlap with operands in calls to `cx_bn_gf2_n_mul()`
- Give a warning if a user chooses 1-of-m shares when m > 1
- Use CBOR tag for version 2 `sskr`
- Update restrictions on when a release workflow is triggered

## [1.7.3] - 2024-05-29

### Fixed

- Changed name of 'Generate BIP39' menus to 'Recover BIP39'
- Changed Second Montgomery constant used for `cx_bn_gf2_n_mul()` to a more suitable value
- Improve efficiency of `cx_bn_gf2_n_mul()` for Nano S
- Change cmocka git repo from cryptomilk.org to GitLab

## [1.7.2] - 2024-05-06

### Fixed

- Using Ledger SDK `cx_crc32()` function rather than buggy `cx_crc32_hw()`.
- Fix build with SDK master for Nano S

## [1.7.1] - 2024-04-06

### Changed

- Improve efficiency of SSS `interpolate()` function

## [1.7.0] - 2024-03-03

### Added

- Added detailed documentation for all SSKR and SSS functions

### Changed

- Changed Shamir interpolate function to use `cx_bn_gf2_n_mul()` syscalls
- Changed some function names to be more descriptive
- Reorganised and renamed some of the SSKR and Shamir code

## [1.6.1] - 2024-01-27

### Added

- Added a Release Policy document

### Changed

- Updated version of cmocka used for unit tests
- Updated version of github actions used
- Assert HMAC return values

### Fixed

- Fixed failing Ledger rule enforcer check
- Use `cx_crc32_hw()`
  - Ledger have fixed their buggy implementation of CRC32 so we can start using it again

## [1.6.0] - 2024-01-14

### Added

- Use CX_CHECK macro in `compare_recovery_phrase()`
- Added a `cx_crc32()` function
  - The implementation of `cx_crc32_hw()` on Ledger devices is buggy and produces incorrect CRC32 checks. Ledger are fixing `cx_crc32_hw()` on each device either through SDK or OS updates but until then `cx_crc32()` can be used.

## [1.5.4] - 2023-11-30

### Added

- Added mandatory Ledger embedded application manifest file

### Changed

- Combined BIP39 wordlist and SSKR wordlist unit tests

## [1.5.3] - 2023-11-18

### Added

- Added unit tests for BIP39
- Added unit tests for BIP39 word list and SSKR word list

### Fixed

- Fixed CodeQL warnings about sign check of a bitwise operation
- Fixed issue with restarting input from a previous word on Nano S

## [1.5.2] - 2023-11-15

### Changed

- Save memory by setting the SSKR word buffer to a sensible size
  - There is just enough memory available on Nano S to hold the phrases for 10 shares. Other devices can hold the full 16 shares.
- Tidied up code that sets 'Processing' screen on Nano S devices

### Security

- Changed all Variable Length Arrays to a defined length

### Fixed

- Fix freezing at 'Processing' screen on Nano S devices

## [1.5.1] - 2023-11-09

### Added

- Added unit tests for shamir
- Added unit tests for SSKR
- Added unit tests for BIP39 <-> SSKR roundtrip

### Changed

- Make generic SSKR functionality more Ledger specific

### Removed

- Reduce size of Nano binaries slightly by removing duplicate flows

## [1.5.0] - 2023-10-20

### Added

- Added option to recover BIP39 mnemonics from SSKR shares even if shares do not validate against seed on device
  - A user may have lost or damaged original device and now needs to recover the BIP39 phrase from another secure device

### Fixed

- Fixed build warning about UNUSED macro

## [1.4.1] - 2023-10-13

### Security

- Clear buffers before exiting

## [1.4.0] - 2023-05-14

### Added

- Added BIP39 Check for Ledger Stax

### Fixed

- Fixed warnings about deprecated functions during build

## [1.3.2] - 2023-05-08

### Added

- Added some Ledger specific preprocessor conditionals to bc-sskr and bc-shamir

### Changed

- Changed memset(x, 0, y) to memzero(x, y) macro

## [1.3.1] - 2023-05-03

### Fixed

- Fixed static analyzer warning about zero-length array
- Fixed CodeQL warnings about comparison of narrow type with wide type in loop condition

## [1.3.0] - 2023-04-27

### Changed

- Simplified flow code

### Removed

- Removed duplicated nano code

## [1.2.0] - 2023-04-21

### Added

- Added automated tests
- Added flow to set SSKR threshold values

## [1.1.1] - 2023-04-06

### Fixed

- Fix issue with using 'cx_crc32_hw()' function in 'onboarding_seed_sskr.c' when testing with Speculos
- Some CodeQL suggested tidy ups

## [1.1.0] - 2023-04-04

### Added

- Recover BIP39 mnemonic phrases from SSKR shares
  - Add 'SSKR Check' menu option
  - Add flow to the 'SSKR Check' menu
  - Write SSKR to BIP39 functionality
  - Test with 29-word SSKR shares
  - Test with 46-word SSKR shares
  - Test on nanos
  - Test on nanosp
  - Test on nanox

## [1.0.1] - 2023-03-21

### Added

- Clone app-recovery-check and rename to app-sskr-check
- Add SSKR (bc-sskr and bc-shamir) to app-sskr-check
- Generate SSKR shares from BIP39 mnemonic phrase
  - Write BIP39 to SSKR functionality
  - Add SSKR flow to the Check BIP39 menu
  - Test with 12-word BIP39 phrases
  - Test with 18-word BIP39 phrases
  - Test with 24-word BIP39 phrases
  - Test on nanos
  - Test on nanosp
  - Test on nanox
