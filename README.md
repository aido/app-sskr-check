<p align="center"><img src="icons/seed_tool.png" alt="Seed Tool" style="width:10%;height:10%"/></p>

# Seed Tool: A Ledger application that provides some useful seed management utilities

[![Release](https://img.shields.io/github/release/aido/app-seed-tool)](https://github.com/aido/app-seed-tool/releases)
[![License](https://img.shields.io/github/license/aido/app-seed-tool)](https://github.com/aido/app-seed-tool/blob/develop/LICENSE)

![nanos](https://img.shields.io/badge/nanos-working-green?logo=data:image/svg%2bxml;base64,PHN2ZyB3aWR0aD0iMTQ3IiBoZWlnaHQ9IjEyOCIgdmlld0JveD0iMCAwIDE0NyAxMjgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+PHBhdGggZD0iTTAgOTEuNjU0OFYxMjhINTUuMjkzVjExOS45NEg4LjA1NjMxVjkxLjY1NDhIMFpNMTM4Ljk0NCA5MS42NTQ4VjExOS45NEg5MS43MDdWMTI3Ljk5OEgxNDdWOTEuNjU0OEgxMzguOTQ0Wk01NS4zNzMzIDM2LjM0NTJWOTEuNjUyOUg5MS43MDdWODQuMzg0Mkg2My40Mjk2VjM2LjM0NTJINTUuMzczM1pNMCAwVjM2LjM0NTJIOC4wNTYzMVY4LjA1ODQ0SDU1LjI5M1YwSDBaTTkxLjcwNyAwVjguMDU4NDRIMTM4Ljk0NFYzNi4zNDUySDE0N1YwSDkxLjcwN1oiIGZpbGw9IndoaXRlIi8+PC9zdmc+)
![nanosp](https://img.shields.io/badge/nanosp-working-green?logo=data:image/svg%2bxml;base64,PHN2ZyB3aWR0aD0iMTQ3IiBoZWlnaHQ9IjEyOCIgdmlld0JveD0iMCAwIDE0NyAxMjgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+PHBhdGggZD0iTTAgOTEuNjU0OFYxMjhINTUuMjkzVjExOS45NEg4LjA1NjMxVjkxLjY1NDhIMFpNMTM4Ljk0NCA5MS42NTQ4VjExOS45NEg5MS43MDdWMTI3Ljk5OEgxNDdWOTEuNjU0OEgxMzguOTQ0Wk01NS4zNzMzIDM2LjM0NTJWOTEuNjUyOUg5MS43MDdWODQuMzg0Mkg2My40Mjk2VjM2LjM0NTJINTUuMzczM1pNMCAwVjM2LjM0NTJIOC4wNTYzMVY4LjA1ODQ0SDU1LjI5M1YwSDBaTTkxLjcwNyAwVjguMDU4NDRIMTM4Ljk0NFYzNi4zNDUySDE0N1YwSDkxLjcwN1oiIGZpbGw9IndoaXRlIi8+PC9zdmc+)
![nanox](https://img.shields.io/badge/nanox-working-green?logo=data:image/svg%2bxml;base64,PHN2ZyB3aWR0aD0iMTQ3IiBoZWlnaHQ9IjEyOCIgdmlld0JveD0iMCAwIDE0NyAxMjgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+PHBhdGggZD0iTTAgOTEuNjU0OFYxMjhINTUuMjkzVjExOS45NEg4LjA1NjMxVjkxLjY1NDhIMFpNMTM4Ljk0NCA5MS42NTQ4VjExOS45NEg5MS43MDdWMTI3Ljk5OEgxNDdWOTEuNjU0OEgxMzguOTQ0Wk01NS4zNzMzIDM2LjM0NTJWOTEuNjUyOUg5MS43MDdWODQuMzg0Mkg2My40Mjk2VjM2LjM0NTJINTUuMzczM1pNMCAwVjM2LjM0NTJIOC4wNTYzMVY4LjA1ODQ0SDU1LjI5M1YwSDBaTTkxLjcwNyAwVjguMDU4NDRIMTM4Ljk0NFYzNi4zNDUySDE0N1YwSDkxLjcwN1oiIGZpbGw9IndoaXRlIi8+PC9zdmc+)
![stax](https://img.shields.io/badge/stax-in_progress-orange?logo=data:image/svg%2bxml;base64,PHN2ZyB3aWR0aD0iMTQ3IiBoZWlnaHQ9IjEyOCIgdmlld0JveD0iMCAwIDE0NyAxMjgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+PHBhdGggZD0iTTAgOTEuNjU0OFYxMjhINTUuMjkzVjExOS45NEg4LjA1NjMxVjkxLjY1NDhIMFpNMTM4Ljk0NCA5MS42NTQ4VjExOS45NEg5MS43MDdWMTI3Ljk5OEgxNDdWOTEuNjU0OEgxMzguOTQ0Wk01NS4zNzMzIDM2LjM0NTJWOTEuNjUyOUg5MS43MDdWODQuMzg0Mkg2My40Mjk2VjM2LjM0NTJINTUuMzczM1pNMCAwVjM2LjM0NTJIOC4wNTYzMVY4LjA1ODQ0SDU1LjI5M1YwSDBaTTkxLjcwNyAwVjguMDU4NDRIMTM4Ljk0NFYzNi4zNDUySDE0N1YwSDkxLjcwN1oiIGZpbGw9IndoaXRlIi8+PC9zdmc+)
![flex](https://img.shields.io/badge/flex-in_progress-orange?logo=data:image/svg%2bxml;base64,PHN2ZyB3aWR0aD0iMTQ3IiBoZWlnaHQ9IjEyOCIgdmlld0JveD0iMCAwIDE0NyAxMjgiIGZpbGw9Im5vbmUiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyI+PHBhdGggZD0iTTAgOTEuNjU0OFYxMjhINTUuMjkzVjExOS45NEg4LjA1NjMxVjkxLjY1NDhIMFpNMTM4Ljk0NCA5MS42NTQ4VjExOS45NEg5MS43MDdWMTI3Ljk5OEgxNDdWOTEuNjU0OEgxMzguOTQ0Wk01NS4zNzMzIDM2LjM0NTJWOTEuNjUyOUg5MS43MDdWODQuMzg0Mkg2My40Mjk2VjM2LjM0NTJINTUuMzczM1pNMCAwVjM2LjM0NTJIOC4wNTYzMVY4LjA1ODQ0SDU1LjI5M1YwSDBaTTkxLjcwNyAwVjguMDU4NDRIMTM4Ljk0NFYzNi4zNDUySDE0N1YwSDkxLjcwN1oiIGZpbGw9IndoaXRlIi8+PC9zdmc+)

[![Build app-seed-tool](https://github.com/aido/app-seed-tool/actions/workflows/ci-workflow.yml/badge.svg)](https://github.com/aido/app-seed-tool/actions/workflows/ci-workflow.yml)
[![CodeQL](https://github.com/aido/app-seed-tool/actions/workflows/codeql-workflow.yml/badge.svg)](https://github.com/aido/app-seed-tool/actions/workflows/codeql-workflow.yml)
[![Code style check](https://github.com/aido/app-seed-tool/actions/workflows/lint-workflow.yml/badge.svg)](https://github.com/aido/app-seed-tool/actions/workflows/lint-workflow.yml)
[![Ledger rule enforcer](https://github.com/aido/app-seed-tool/actions/workflows/ledger-rule-enforcer.yml/badge.svg)](https://github.com/aido/app-seed-tool/actions/workflows/ledger-rule-enforcer.yml)
[![codecov](https://codecov.io/gh/aido/app-seed-tool/branch/develop/graph/badge.svg?token=uCkGEbhGl3)](https://codecov.io/gh/aido/app-seed-tool/tree/develop)

---

Use the utilities provided by this Ledger application to check a backed up BIP-39 seed, generate [Shamir's Secret Sharing (SSS)](https://en.wikipedia.org/wiki/Shamir%27s_secret_sharing) for a seed or recover a BIP-39 phrase from a Shamir's Secret Sharing backup.

Not all Ledger devices are equal. The older, less capable devices do not have the capacity to provide a full range of seed utilities. The following table lists the seed utilities provided by each devices type:
<div align="center">

||Nano S|Nano S+|Nano X|Stax|Flex|
| :--- | :---: | :---: | :---: | :---: | :---: |
|[Check BIP39](#check-bip39)|$${\color{green}✓}$$|$${\color{green}✓}$$|$${\color{green}✓}$$|$${\color{green}✓}$$|$${\color{orange}✓}$$|
|[Check Shamir's secret shares](#check-shamirs-secret-shares)|$${\color{green}✓}$$|$${\color{green}✓}$$|$${\color{green}✓}$$|$${\color{green}✓}$$|$${\color{orange}✓}$$|
|[Generate Shamir's secret sharing](#generate-shamirs-secret-sharing)|$${\color{green}✓}$$|$${\color{green}✓}$$|$${\color{green}✓}$$|$${\color{green}✓}$$|$${\color{orange}✓}$$|
|[Recover BIP39](#recover-bip39)|$${\color{green}✓}$$|$${\color{green}✓}$$|$${\color{green}✓}$$|$${\color{green}✓}$$|$${\color{orange}✓}$$|
|[Generate BIP85](#generate-bip85)|$${\color{red}✗}$$|$${\color{orange}✓}$$|$${\color{orange}✓}$$|$${\color{orange}✓}$$|$${\color{orange}✓}$$|
</div>

## Application menu flow
```mermaid
---
title: Seed Tool menu flow
---
flowchart LR
    1 --- 2 --- 3 --- 4
    subgraph 1[BIP39]
        direction TB
        1.1[Check BIP39]
        1.1 --> 1.2.1[Enter 12 Words] --> 1.3{Validate BIP39 Phrases}
        1.1 --> 1.2.2[Enter 18 Words] --> 1.3
        1.1 --> 1.2.3[Enter 24 Words] --> 1.3
        1.3 --> |Matching BIP39| 1.4
        1.3 --> |Invalid BIP39| 1.3.1[Quit]
        subgraph 1.4[Generate SSKR Shares]
            direction TB
            1.4.1[Select number of shares] --> 1.4.2[Select threshold] --> 1.4.3[Generate SSKR Shares] --> 1.4.4[Display SSKR Shares] --> 1.4.5[Quit]
        end
    end
    subgraph 2[SSKR]
        direction TB
        2.1[Check SSKR] --> 2.2[Enter SSKR Shares] --> 2.3{Validate SSKR Shares}
        2.3 --> |Valid SSKR| 2.4
        2.3 --> |Invalid SSKR| 2.3.1[Quit]
        subgraph 2.4[Recover BIP39 Phrases]
            direction TB
            2.4.1[Recover BIP39 Phrases] --> 2.4.2[Display BIP39 Phrases] --> 2.4.3[Quit]
        end
    end
    subgraph 3[Version]
        direction TB
        3.1[Version]
        end
    subgraph 4[Quit]
        direction TB
        4.1[Quit]
    end
```
> [!TIP]
> Demo videos of some of the menu flows on different hardware devices are available [here](demos/README.md).
> 
> Alternatively, animations of some of the menu flows on different hardware devices are available [here](tests/functional/screenshots/README.md).

## Check BIP39
The application invites the user to type a [BIP-39](https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki) mnemonic on their Ledger device. The BIP-39 mnemonic is compared to the onboarded seed and the application notifies the user whether both seeds match or not.

## Generate Shamir's secret sharing
If the user provided seed is valid and matches the onboarded seed, the user can create [Shamir's secret sharing (SSS)](https://en.wikipedia.org/wiki/Shamir%27s_secret_sharing) from their BIP-39 phrase.
The application uses [Sharded Secret Key Reconstruction (SSKR)](https://github.com/BlockchainCommons/Research/blob/master/papers/bcr-2020-011-sskr.md), an interoperable implementation of [Shamir's Secret Sharing (SSS)](https://en.wikipedia.org/wiki/Shamir%27s_secret_sharing). This provides a way for you to divide or 'shard' the master seed underlying a Bitcoin HD wallet into 'shares', which you can then distribute to friends, family, or fiduciaries. If you lose your seed, you can reconstruct it by collecting a sufficient number of your shares (the 'threshold'). Knowledge of fewer than the required number of parts ensures that information about the master secret is not leaked.

* SSKR is round-trip compatible with BIP-39.
* SSKR is based on SLIP-39, developed by SatoshiLabs. It is an improvement on, but is incompatible with, SLIP-39.
* SSKR phrases use a dictionary of exactly 256 English words with a uniform word size of 4 letters.
* SSKR encodes a [CBOR] structure tagged with the data type [URTYPES], and is therefore self-describing.
* Phrases generated by SSKR can be up to 46 words in length i.e. 184 characters.
* Only two letters of each word (the first and last) are required to uniquely identify each byte value, making a minimal [ByteWords](https://github.com/BlockchainCommons/Research/blob/master/papers/bcr-2020-012-bytewords.md) encoding as efficient as hexadecimal (2 characters per byte) and yet less error prone.
* Additionally, words can be uniquely identified by their first three letters or last three letters.
* Minimizing the number of letters for each word simplifies transfer to permanent media such as stamped metal.

For more information about SSKR, see [SSKR for Users](https://github.com/BlockchainCommons/crypto-commons/blob/master/Docs/sskr-users.md).

> [!NOTE]
> SSKR is non-deterministic. There is a random factor introduced when the shares are created, which means that every time you generate shares they will be different. This is an expected and correct result.

> [!TIP]
> Generated Shamir's Secret Shares may be cheaply and safely backed up to a steel wallet using the methods described [here](https://blockmit.com/english/guides/diy/make-cold-wallet-washers/) or [here](https://github.com/BlockchainCommons/crypto-commons/blob/master/Docs/sskr-cold-storage.md). This will keep your backup safe in event of fire, flood or natural disaster.

## Check Shamir's secret shares
The Ledger application also provides an option to confirm the onboarded seed against SSKR shares.

## Recover BIP39
When the Shamir's secret shares have been validated the user can recover the BIP39 phrase derived from those shares. This option takes advantage of SSKR's ability to perform a BIP39 <-> SSKR round trip. If a user has lost or damaged their original Ledger device they may need to recover their BIP39 phrase on another secure device. A BIP39 phrase may still be recovered even if the SSKR phrases do not match the onboarded seed of a device but are still valid SSKR shares.

## Generate [BIP85](https://github.com/bitcoin/bips/blob/master/bip-0085.mediawiki)
**Coming soon!!!!**

BIP85 allows you to do crazy stuff like this:
```mermaid
---
title: One Seed to rule them all - Multi wallet
---
flowchart TB
    1.1 --> |Backup| 1.2
    1 --> |BIP85 Child 0| 2.1.1
    1 --> |BIP85 Child 1| 2.1.2
    1 --> |BIP85 Child 2| 2.2.1
    1 --> |BIP85 Child 3| 2.2.2
    1 --> |BIP85 Child 4| 2.3.1
    1 --> |BIP85 Child 5| 2.3.2
    1 --> |BIP85 Child 6| 2.4.1
    1 --> |BIP85 Child 7| 2.4.2
    subgraph 1[Parent]
        direction TB
        1.1[Root Seed]
        subgraph 1.2[2-of-3 Shamir's Secret Shares]
            direction BT
            1.2.1[Share 1]
            1.2.2[Share 2]
            1.2.3[Share 3]
        end
    end
    subgraph 2[Children]
        direction TB
        subgraph 2.1[Cold Wallet]
            direction LR
            2.1.1[BIP39 #1]
            2.1.2[Password #1]
            end
            subgraph 2.2[Hardware Wallet]
            direction LR
            2.2.1[BIP39 #2]
            2.2.2[Password #2]
            end
            subgraph 2.3[Lightning Wallet]
            direction LR
            2.3.1[BIP39 #3]
            2.3.2[Password #3]
            end
            subgraph 2.4[Phone Wallet]
            direction LR
            2.4.1[BIP39 #4]
            2.4.2[Password #4]
            end
    end
```
```mermaid
---
title: One Seed to rule them all - MultiSig
---
flowchart TB
    1.1 --> |Backup| 1.2
    1 --> |BIP85 Child 0| 2.1.1
    1 --> |BIP85 Child 1| 2.1.2
    1 --> |BIP85 Child 2| 2.2.1
    1 --> |BIP85 Child 3| 2.2.2
    1 --> |BIP85 Child 4| 2.3.1
    1 --> |BIP85 Child 5| 2.3.2
    2.1 --> 3.1
    2.2 --> 3.2
    2.3 --> 3.3
    subgraph 1[Parent]
        direction TB
        1.1[Root Seed]
        subgraph 1.2[2-of-3 Shamir's Secret Shares]
            direction BT
            1.2.1[Share 1]
            1.2.2[Share 2]
            1.2.3[Share 3]
        end
    end
    subgraph 2[Children]
        direction TB
        subgraph 2.1[Wallet #1]
            direction LR
            2.1.1[BIP39 #1]
            2.1.2[Password #1]
            end
            subgraph 2.2[Wallet #2]
            direction LR
            2.2.1[BIP39 #2]
            2.2.2[Password #2]
            end
            subgraph 2.3[Wallet #3]
            direction LR
            2.3.1[BIP39 #3]
            2.3.2[Password #3]
            end
    end
    subgraph 3[2-of-3 MultiSig Wallet]
        direction LR
        3.1[Signer 1]
        3.2[Signer 2]
        3.3[Signer 3]
    end
```
