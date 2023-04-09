# app-sskr-check TODO list

### Todo

- [ ] Add Ledger Stax to list of devices app works on
- [ ] Currently hardcoded to use a k-of-n threshold of 2-of-3. Add flow to set threshold values
- [ ] Save memory by setting the SSKR word buffer (G_bolos_ux_context.sskr_words_buffer) to a sensible size. Maybe just store SSKR Bytewords as shorter two letter minimal Bytewords rather than a 4 letter Byteword plus spaace for each share. Convert minimal ByteWords back to four letter Bytewords just prior to display.
- [ ] Add automated tests

### In Progress

- [ ] Currently hardcoded to use a k-of-n threshold of 2-of-3. Add flow to set threshold values
- [ ] Add automated tests

### Done ✓

- [x] Fix issue with using 'cx_crc32_hw()' function in 'onboarding_seed_sskr.c' when testing with Speculos
- [x] Generate BIP39 mnemonic phrases from SSKR shares
  - [x] Add SSKR Check menu option
  - [x] Add flow to the Check SSKR menu
  - [x] Write SSKR to BIP39 functionality
  - [x] Test with 29-word SSKR shares
  - [x] Test with 46-word SSKR shares
  - [x] Test on nanos
  - [x] Test on nanosp
  - [x] Test on nanox
- [x] Clone app-recovery-check and rename to app-sskr-check
- [x] Add SSKR (bc-sskr and bc-shamir) to app-sskr-check
- [x] Generate SSKR shares from BIP39 mnemonic phrase
  - [x] Write BIP39 to SSKR functionality
  - [x] Add SSKR flow to the Check BIP39 menu
  - [x] Test with 12-word BIP39 phrases
  - [x] Test with 18-word BIP39 phrases
  - [x] Test with 24-word BIP39 phrases
  - [x] Test on nanos
  - [x] Test on nanosp
  - [x] Test on nanox
