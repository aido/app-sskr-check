from pytest import fixture
from pytest import mark
from pytest import skip
from ragger.navigator import NavInsID
from ragger.conftest import configuration

@fixture(scope='session')
def set_seed():
    # Seed taken from https://github.com/BlockchainCommons/crypto-commons/blob/master/Docs/sskr-test-vector.md#128-bit-seed
    configuration.OPTIONAL.CUSTOM_SEED = "fly mule excess resource treat plunge nose soda reflect adult ramp planet"

def nanos_sskr_128bit(backend, navigator):
    backend.wait_for_text_on_screen("Check BIP39", 5)
    backend.wait_for_text_on_screen("recovery phras", 1)
    navigator.navigate([NavInsID.RIGHT_CLICK], screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("Check SSKR", 5)
    backend.wait_for_text_on_screen("recovery phras", 1)
    instructions = [
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.BOTH_CLICK
    ]
    navigator.navigate(instructions, screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("SSKR Phrase", 5)
    backend.wait_for_text_on_screen("is correct", 1)
    navigator.navigate([NavInsID.RIGHT_CLICK], screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("Quit", 1)
    navigator.navigate([NavInsID.RIGHT_CLICK], screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("Recover", 1)
    backend.wait_for_text_on_screen("BIP39 phrase", 1)
    navigator.navigate([NavInsID.BOTH_CLICK], screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("BIP39 Phrase", 1)
    backend.wait_for_text_on_screen("fly mule excess", 1)
    navigator.navigate([NavInsID.RIGHT_CLICK], screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("BIP39 Phrase", 1)
    backend.wait_for_text_on_screen(" resource treat plunge", 1)
    navigator.navigate([NavInsID.RIGHT_CLICK], screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("BIP39 Phrase", 1)
    backend.wait_for_text_on_screen(" nose soda reflect", 1)
    navigator.navigate([NavInsID.RIGHT_CLICK], screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("BIP39 Phrase", 1)
    backend.wait_for_text_on_screen(" adult ramp planet", 1)
    navigator.navigate([NavInsID.RIGHT_CLICK], screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("Quit", 1)

def stax_sskr_128bit(backend):
    backend.wait_for_text_on_screen("Seed Tool", 10)
    backend.finger_touch(106, 510, 1)
    backend.wait_for_text_on_screen("SSKR Check", 5)
    backend.finger_touch(212, 510, 1)
    backend.wait_for_text_on_screen("Enter Share 1 Word 1", 5)
    backend.finger_touch(180, 460, 1) # t
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(220, 580, 1) # n
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(220, 580, 1) # n
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(60, 580, 1) # x
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(320, 520, 1) # k
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(200, 520, 1) # g
    backend.finger_touch(220, 460, 1) # y
    backend.finger_touch(140, 460, 1) # r
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(380, 460, 1) # p
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(100, 580, 1) # c
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(180, 580, 1) # b
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(100, 580, 1) # c
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(180, 580, 1) # b
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(280, 520, 1) # j
    backend.finger_touch(340, 460, 1) # o
    backend.finger_touch(60, 460, 1) # w
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(100, 580, 1) # c
    backend.finger_touch(240, 520, 1) # h
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(120, 520, 1) # d
    backend.finger_touch(140, 460, 1) # r
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(280, 520, 1) # j
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(120, 520, 1) # d
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(380, 460, 1) # p
    backend.finger_touch(340, 460, 1) # o
    backend.finger_touch(340, 460, 1) # o
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(340, 460, 1) # o
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(320, 520, 1) # k
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(120, 520, 1) # d
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(100, 580, 1) # c
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(80, 520, 1) # s
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(100, 580, 1) # c
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(140, 460, 1) # r
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(80, 520, 1) # s
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(160, 520, 1) # f
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(100, 580, 1) # c
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(140, 580, 1) # v
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(180, 460, 1) # t
    backend.finger_touch(60, 460, 1) # w
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(140, 580, 1) # v
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(140, 460, 1) # r
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(380, 460, 1) # p
    backend.finger_touch(340, 460, 1) # o
    backend.finger_touch(80, 520, 1) # s
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(380, 460, 1) # p
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(60, 460, 1) # w
    backend.finger_touch(240, 520, 1) # h
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(280, 520, 1) # j
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(260, 580, 1) # m
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(280, 520, 1) # j
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(140, 460, 1) # r
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(180, 460, 1) # t
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(220, 580, 1) # n
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(220, 580, 1) # n
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(60, 580, 1) # x
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(320, 520, 1) # k
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(200, 520, 1) # g
    backend.finger_touch(220, 460, 1) # y
    backend.finger_touch(140, 460, 1) # r
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(380, 460, 1) # p
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(100, 580, 1) # c
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(180, 580, 1) # b
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(100, 580, 1) # c
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(100, 580, 1) # c
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(200, 520, 1) # g
    backend.finger_touch(140, 460, 1) # r
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(20, 460, 1) # q
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(320, 520, 1) # k
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(60, 460, 1) # w
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(320, 520, 1) # k
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(380, 460, 1) # p
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(120, 520, 1) # d
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(260, 580, 1) # m
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(380, 460, 1) # p
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(140, 460, 1) # r
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(100, 580, 1) # c
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(160, 520, 1) # f
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(120, 520, 1) # d
    backend.finger_touch(300, 460, 1) # i
    backend.finger_touch(100, 580, 1) # c
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(180, 580, 1) # b
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(200, 520, 1) # g
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(260, 580, 1) # m
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(220, 460, 1) # y
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(220, 580, 1) # n
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(160, 520, 1) # f
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(140, 460, 1) # r
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(180, 580, 1) # b
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(200, 520, 1) # g
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(280, 520, 1) # j
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(120, 520, 1) # d
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(220, 580, 1) # n
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(140, 580, 1) # v
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(100, 580, 1) # c
    backend.finger_touch(340, 460, 1) # o
    backend.finger_touch(80, 520, 1) # s
    backend.finger_touch(100, 280, 1)
    backend.wait_for_text_on_screen("Valid Secret", 5)
    backend.wait_for_text_on_screen("Recovery Phrase", 1)
    backend.finger_touch(200, 630, 1)
    backend.wait_for_text_on_screen("Recover BIP39", 5)
    backend.finger_touch(200, 550, 1)
    backend.wait_for_text_on_screen("BIP39 Phrase", 5)
    backend.wait_for_text_on_screen("fly mule excess", 1)
    backend.wait_for_text_on_screen("resource treat plunge", 1)
    backend.wait_for_text_on_screen("nose soda reflect adult",1)
    backend.wait_for_text_on_screen("ramp planet", 1)
    backend.finger_touch(200, 630,1)
    backend.wait_for_text_on_screen("Seed Tool", 5)
    backend.finger_touch(200, 630,1)

def flex_sskr_128bit(backend):
    backend.wait_for_text_on_screen("Seed Tool", 10)
    backend.finger_touch(240, 440, 1)
    backend.wait_for_text_on_screen("SSKR Check", 5)
    backend.finger_touch(240, 420, 1)
    backend.wait_for_text_on_screen("Enter Share 1 Word 1", 5)
    backend.finger_touch(220, 400, 1) # t
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(270, 560, 1) # n
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(270, 560, 1) # n
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(70, 560, 1) # x
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(400, 480, 1) # k
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(250, 480, 1) # g
    backend.finger_touch(270, 400, 1) # y
    backend.finger_touch(170, 400, 1) # r
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(470, 400, 1) # p
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(120, 560, 1) # c
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(220, 560, 1) # b
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(120, 560, 1) # c
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(220, 560, 1) # b
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(350, 480, 1) # j
    backend.finger_touch(420, 400, 1) # o
    backend.finger_touch(70, 400, 1) # w
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(120, 560, 1) # c
    backend.finger_touch(300, 480, 1) # h
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(150, 480, 1) # d
    backend.finger_touch(170, 400, 1) # r
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(350, 480, 1) # j
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(150, 480, 1) # d
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(470, 400, 1) # p
    backend.finger_touch(420, 400, 1) # o
    backend.finger_touch(420, 400, 1) # o
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(420, 400, 1) # o
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(400, 480, 1) # k
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(150, 480, 1) # d
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(120, 560, 1) # c
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(100, 480, 1) # s
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(120, 560, 1) # c
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(170, 400, 1) # r
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(100, 480, 1) # s
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(200, 480, 1) # f
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(120, 560, 1) # c
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(170, 560, 1) # v
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(220, 400, 1) # t
    backend.finger_touch(70, 400, 1) # w
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(170, 560, 1) # v
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(170, 400, 1) # r
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(470, 400, 1) # p
    backend.finger_touch(420, 400, 1) # o
    backend.finger_touch(100, 480, 1) # s
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(470, 400, 1) # p
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(70, 400, 1) # w
    backend.finger_touch(300, 480, 1) # h
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(350, 480, 1) # j
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(320, 560, 1) # m
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(350, 480, 1) # j
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(170, 400, 1) # r
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(220, 400, 1) # t
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(270, 560, 1) # n
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(270, 560, 1) # n
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(70, 560, 1) # x
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(400, 480, 1) # k
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(250, 480, 1) # g
    backend.finger_touch(270, 400, 1) # y
    backend.finger_touch(170, 400, 1) # r
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(470, 400, 1) # p
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(120, 560, 1) # c
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(220, 560, 1) # b
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(120, 560, 1) # c
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(120, 560, 1) # c
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(250, 480, 1) # g
    backend.finger_touch(170, 400, 1) # r
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(20, 400, 1) # q
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(400, 480, 1) # k
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(70, 400, 1) # w
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(400, 480, 1) # k
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(470, 400, 1) # p
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(150, 480, 1) # d
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(320, 560, 1) # m
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(470, 400, 1) # p
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(170, 400, 1) # r
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(120, 560, 1) # c
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(200, 480, 1) # f
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(150, 480, 1) # d
    backend.finger_touch(370, 400, 1) # i
    backend.finger_touch(120, 560, 1) # c
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(220, 560, 1) # b
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(250, 480, 1) # g
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(320, 560, 1) # m
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(270, 400, 1) # y
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(270, 560, 1) # n
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(200, 480, 1) # f
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(170, 400, 1) # r
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(220, 560, 1) # b
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(250, 480, 1) # g
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(350, 480, 1) # j
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(150, 480, 1) # d
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(270, 560, 1) # n
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(170, 560, 1) # v
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(120, 560, 1) # c
    backend.finger_touch(420, 400, 1) # o
    backend.finger_touch(100, 480, 1) # s
    backend.finger_touch(130, 300, 1)
    backend.wait_for_text_on_screen("Valid Secret", 5)
    backend.wait_for_text_on_screen("Recovery Phrase", 1)
    backend.finger_touch(240, 550, 1)
    backend.wait_for_text_on_screen("Recover BIP39", 5)
    backend.finger_touch(240, 460, 1)
    backend.wait_for_text_on_screen("BIP39 Phrase", 5)
    backend.wait_for_text_on_screen("fly mule excess", 1)
    backend.wait_for_text_on_screen("resource treat plunge", 1)
    backend.wait_for_text_on_screen("nose soda reflect adult",1)
    backend.wait_for_text_on_screen("ramp planet", 1)
    backend.finger_touch(240, 550, 1)
    backend.wait_for_text_on_screen("Seed Tool", 5)
    backend.finger_touch(240, 550, 1)

@mark.use_on_backend("speculos")
def test_sskr_128bit(firmware, backend, navigator, set_seed):
    if firmware.device == "nanos":
        nanos_sskr_128bit(backend, navigator)
    elif firmware.device == "nanosp":
        skip("Skipping test for Nano S+ device")
    elif firmware.device == "nanox":
        skip("Skipping test for Nano X device")
    elif firmware.device == "stax":
        stax_sskr_128bit(backend)
    elif firmware.device == "flex":
        flex_sskr_128bit(backend)
