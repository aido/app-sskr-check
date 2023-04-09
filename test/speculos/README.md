# App testing on Speculos

Below are some manual tests for testing `BIP-39 Check` and `SSKR Check` flows.
There are a couple of ways of running each test. Using curl POST to send data to the Speculos API or using the --automation parameter of the speculos.py command line. 

## BIP-39
### 12 Word Tests
#### API with curl 
```bash
./speculos.py ../app-sskr-check/build/nanos/bin/app.elf --model nanos --seed "fly mule excess resource treat plunge nose soda reflect adult ramp planet"
```
```bash
while read -a LINE
do
    curl -d '{"action":"press-and-release"}' -X ${LINE[0]} http://127.0.0.1:5000${LINE[1]}
done < ./test/speculos/nanos-bip39-12-word.test > /dev/null 2>&1 &
```
#### Speculos automation
```bash
./speculos.py --automation file:../app-sskr-check/test/speculos/nanos-bip39-12-word.json ../app-sskr-check/build/nanos/bin/app.elf --model nanos --seed "fly mule excess resource treat plunge nose soda reflect adult ramp planet"
```
### 18 Word Tests
#### API with curl 
```bash
./speculos.py ../app-sskr-check/build/nanos/bin/app.elf --model nanos --seed "profit result tip galaxy hawk immune hockey series melody grape unusual prize nothing federal dad crew pact sad"
```
```bash
while read -a LINE
do
    curl -d '{"action":"press-and-release"}' -X ${LINE[0]} http://127.0.0.1:5000${LINE[1]}
done < ./test/speculos/nanos-bip39-18-word.test > /dev/null 2>&1 &
```
#### Speculos automation
```bash
./speculos.py --automation file:../app-sskr-check/test/speculos/nanos-bip39-18-word.json ../app-sskr-check/build/nanos/bin/app.elf --model nanos --seed "profit result tip galaxy hawk immune hockey series melody grape unusual prize nothing federal dad crew pact sad"
```
### 24 Word Tests
#### API with curl 
```bash
./speculos.py ../app-sskr-check/build/nanos/bin/app.elf --model nanos --seed "toe priority custom gauge jacket theme arrest bargain gloom wide ill fit eagle prepare capable fish limb cigar reform other priority speak rough imitate"
```
```bash
do
    curl -d '{"action":"press-and-release"}' -X ${LINE[0]} http://127.0.0.1:5000${LINE[1]}
done < ./test/speculos/nanos-bip39-24-word.test > /dev/null 2>&1 &
```
#### Speculos automation
```bash
./speculos.py --automation file:../app-sskr-check/test/speculos/nanos-bip39-24-word.json ../app-sskr-check/build/nanos/bin/app.elf --model nanos --seed "toe priority custom gauge jacket theme arrest bargain gloom wide ill fit eagle prepare capable fish limb cigar reform other priority speak rough imitate"
```
## SSKR
### 128-bit seed
Tests taken from the [SSKR Example & Test Vector]( https://github.com/BlockchainCommons/crypto-commons/blob/master/Docs/sskr-test-vector.md#128-bit-seed) page.

#### API with curl 
```bash
./speculos.py ../app-sskr-check/build/nanos/bin/app.elf --model nanos --seed "fly mule excess resource treat plunge nose soda reflect adult ramp planet"
```
```bash
while read -a LINE
do
    curl -d '{"action":"press-and-release"}' -X ${LINE[0]} http://127.0.0.1:5000${LINE[1]}
done < ./test/speculos/nanos-sskr-128bit.test > /dev/null 2>&1 &
```
#### Speculos automation
```bash
../speculos.py --automation file:../app-sskr-check/test/speculos/nanos-sskr-128bit.json ../app-sskr-check/build/nanos/bin/app.elf --model nanos --seed "fly mule excess resource treat plunge nose soda reflect adult ramp planet"
```
### 256-bit seed
Tests taken from the [SSKR Example & Test Vector]( https://github.com/BlockchainCommons/crypto-commons/blob/master/Docs/sskr-test-vector.md#256-bit-seed) page.
#### API with curl 
```bash
./speculos.py ../app-sskr-check/build/nanos/bin/app.elf --model nanos --seed "toe priority custom gauge jacket theme arrest bargain gloom wide ill fit eagle prepare capable fish limb cigar reform other priority speak rough imitate"
```
```bash
while read -a LINE
do
    curl -d '{"action":"press-and-release"}' -X ${LINE[0]} http://127.0.0.1:5000${LINE[1]}
done < ./test/speculos/nanos-sskr-256bit.test > /dev/null 2>&1 &
```
#### Speculos automation
```bash
/speculos.py --automation file:../app-sskr-check/test/speculos/nanos-sskr-256bit.json ../app-sskr-check/build/nanos/bin/app.elf --model nanos --seed "toe priority custom gauge jacket theme arrest bargain gloom wide ill fit eagle prepare capable fish limb cigar reform other priority speak rough imitate"
```
