# Change log

## [1.2.1] - 2023-04-08
### Added
-  Added some manual tests

### Changed
-

### Fixed
-

## [1.1.1] - 2023-04-06
### Added
-

### Changed
-

### Fixed
-  Fix issue with using 'cx_crc32_hw()' function in 'onboarding_seed_sskr.c' when testing with Speculos
-  Some CodeQL suggested tidy ups

## [1.1.0] - 2023-04-04
### Added
- Generate BIP39 mnemonic phrases from SSKR shares
   - Add 'SSKR Check' menu option
   - Add flow to the 'SSKR Check' menu
   - Write SSKR to BIP39 functionality
   - Test with 29-word SSKR shares
   - Test with 46-word SSKR shares
   - Test on nanos
   - Test on nanosp
   - Test on nanox

### Changed
-

### Fixed
-

## [1.0.1] - 2023-03-21

### Added
-  Clone app-recovery-check and rename to app-sskr-check
-  Add SSKR (bc-sskr and bc-shamir) to app-sskr-check
-  Generate SSKR shares from BIP39 mnemonic phrase
    -  Write BIP39 to SSKR functionality
    -  Add SSKR flow to the Check BIP39 menu
    -  Test with 12-word BIP39 phrases
    -  Test with 18-word BIP39 phrases
    -  Test with 24-word BIP39 phrases
    -  Test on nanos
    -  Test on nanosp
    -  Test on nano

### Changed
-

### Fixed
-
