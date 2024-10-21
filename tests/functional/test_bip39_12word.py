from pytest import fixture
from pytest import mark
from pytest import skip
from ragger.navigator import NavInsID
from ragger.conftest import configuration

@fixture(scope='session')
def set_seed():
    # Seed taken from https://github.com/BlockchainCommons/crypto-commons/blob/master/Docs/sskr-test-vector.md#128-bit-seed
    configuration.OPTIONAL.CUSTOM_SEED = "fly mule excess resource treat plunge nose soda reflect adult ramp planet"

def nanos_bip39_12word(backend, navigator):
    backend.wait_for_text_on_screen("Check BIP39", 5)
    backend.wait_for_text_on_screen("recovery phras", 1)
    instructions = [
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
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
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
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
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
        NavInsID.RIGHT_CLICK,
        NavInsID.BOTH_CLICK,
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
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
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
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.BOTH_CLICK,
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
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
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
        NavInsID.BOTH_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
        NavInsID.LEFT_CLICK,
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
        NavInsID.BOTH_CLICK,
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
        NavInsID.LEFT_CLICK,
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
        NavInsID.BOTH_CLICK
    ]
    navigator.navigate(instructions, screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("BIP39 Phrase", 5)
    backend.wait_for_text_on_screen("is correct", 1)
    navigator.navigate([NavInsID.RIGHT_CLICK], screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("Quit", 1)
    navigator.navigate([NavInsID.RIGHT_CLICK], screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("Generate", 1)
    backend.wait_for_text_on_screen("SSKR phrases", 1)
    navigator.navigate([NavInsID.BOTH_CLICK], screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("Select number", 1)
    backend.wait_for_text_on_screen("of shares", 1)
    navigator.navigate([NavInsID.RIGHT_CLICK,
                        NavInsID.RIGHT_CLICK,
                        NavInsID.RIGHT_CLICK,
                        NavInsID.BOTH_CLICK],
                        screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("Select", 1)
    backend.wait_for_text_on_screen("threshold", 1)
    navigator.navigate([NavInsID.RIGHT_CLICK,
                        NavInsID.RIGHT_CLICK,
                        NavInsID.BOTH_CLICK],
                        screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("SSKR Share #1", 5)
    backend.wait_for_text_on_screen("tuna next keep gyro", 1)
    navigator.navigate_until_text(NavInsID.RIGHT_CLICK, [], "SSKR Share #2", 20, screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("tuna next keep gyro", 1)
    navigator.navigate_until_text(NavInsID.RIGHT_CLICK, [], "SSKR Share #3", 20, screen_change_before_first_instruction=False)
    backend.wait_for_text_on_screen("tuna next keep gyro", 1)
    navigator.navigate_until_text(NavInsID.RIGHT_CLICK, [], "Quit", 20, screen_change_before_first_instruction=False)

def stax_bip39_12word(backend):
    backend.wait_for_text_on_screen("Seed Tool", 10)
    backend.finger_touch(106, 510, 1)
    backend.wait_for_text_on_screen("BIP39 Check", 5)
    backend.finger_touch(124, 601, 1)
    backend.finger_touch(148, 601, 1)
    backend.wait_for_text_on_screen("Enter word", 5)
    backend.finger_touch(160, 520, 1) # f
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(220, 460, 1) # y
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(260, 580, 1) # m
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(60, 580, 1) # x
    backend.finger_touch(100, 580, 1) # c
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(140, 460, 1) # r
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(80, 520, 1) # s
    backend.finger_touch(340, 460, 1) # o
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(180, 460, 1) # t
    backend.finger_touch(140, 460, 1) # r
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(380, 460, 1) # p
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(220, 580, 1) # n
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(220, 580, 1) # n
    backend.finger_touch(340, 460, 1) # o
    backend.finger_touch(80, 520, 1) # s
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(80, 520, 1) # s
    backend.finger_touch(340, 460, 1) # o
    backend.finger_touch(120, 520, 1) # d
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(140, 460, 1) # r
    backend.finger_touch(100, 460, 1) # e
    backend.finger_touch(160, 520, 1) # f
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(120, 520, 1) # d
    backend.finger_touch(260, 460, 1) # u
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(140, 460, 1) # r
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(260, 580, 1) # m
    backend.finger_touch(380, 460, 1) # p
    backend.finger_touch(100, 280, 1)
    backend.finger_touch(380, 460, 1) # p
    backend.finger_touch(360, 520, 1) # l
    backend.finger_touch(40, 520, 1) # a
    backend.finger_touch(220, 580, 1) # n
    backend.finger_touch(100, 280, 1)
    backend.wait_for_text_on_screen("Valid Secret", 5)
    backend.wait_for_text_on_screen("Recovery Phrase", 1)
    backend.finger_touch(200, 630, 1)
    backend.wait_for_text_on_screen("Generate SSKR", 5)
    backend.finger_touch(200, 550, 1)
    backend.wait_for_text_on_screen("Enter number of SSKR shares", 5)
    backend.finger_touch(340, 300, 1) # 3
    backend.finger_touch(340, 600,1)
    backend.wait_for_text_on_screen("Enter threshold value", 5)
    backend.finger_touch(195, 300, 1) # 2
    backend.finger_touch(340, 600, 1)
    backend.wait_for_text_on_screen("SSKR Share", 5)
    backend.wait_for_text_on_screen("tuna next keep gyro", 1)
    backend.wait_for_text_on_screen("1 of 3", 1)
    backend.finger_touch(360, 630, 1)
    backend.wait_for_text_on_screen("SSKR Share", 5)
    backend.wait_for_text_on_screen("tuna next keep gyro", 1)
    backend.wait_for_text_on_screen("2 of 3", 1)
    backend.finger_touch(360, 630, 1)
    backend.wait_for_text_on_screen("SSKR Share", 5)
    backend.wait_for_text_on_screen("tuna next keep gyro", 1)
    backend.wait_for_text_on_screen("3 of 3", 1)
    backend.finger_touch(80, 630, 1)
    backend.wait_for_text_on_screen("Seed Tool", 5)
    backend.finger_touch(200, 630, 1)

def flex_bip39_12word(backend):
    backend.wait_for_text_on_screen("Seed Tool", 10)
    backend.finger_touch(240, 440, 1)
    backend.wait_for_text_on_screen("BIP39 Check", 5)
    backend.finger_touch(240, 520, 1)
    backend.finger_touch(240, 520, 1)
    backend.wait_for_text_on_screen("Enter word", 5)
    backend.finger_touch(200, 480, 1) # f
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(270, 400, 1) # y
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(320, 560, 1) # m
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(70, 560, 1) # x
    backend.finger_touch(120, 560, 1) # c
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(170, 400, 1) # r
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(100, 480, 1) # s
    backend.finger_touch(420, 400, 1) # o
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(220, 400, 1) # t
    backend.finger_touch(170, 400, 1) # r
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(470, 400, 1) # p
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(270, 560, 1) # n
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(270, 560, 1) # n
    backend.finger_touch(420, 400, 1) # o
    backend.finger_touch(100, 480, 1) # s
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(100, 480, 1) # s
    backend.finger_touch(420, 400, 1) # o
    backend.finger_touch(150, 480, 1) # d
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(170, 400, 1) # r
    backend.finger_touch(120, 400, 1) # e
    backend.finger_touch(200, 480, 1) # f
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(150, 480, 1) # d
    backend.finger_touch(320, 400, 1) # u
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(170, 400, 1) # r
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(320, 560, 1) # m
    backend.finger_touch(470, 400, 1) # p
    backend.finger_touch(130, 300, 1)
    backend.finger_touch(470, 400, 1) # p
    backend.finger_touch(450, 480, 1) # l
    backend.finger_touch(50, 480, 1) # a
    backend.finger_touch(270, 560, 1) # n
    backend.finger_touch(130, 300, 1)
    backend.wait_for_text_on_screen("Valid Secret", 5)
    backend.wait_for_text_on_screen("Recovery Phrase", 1)
    backend.finger_touch(240, 550, 1)
    backend.wait_for_text_on_screen("Generate SSKR", 5)
    backend.finger_touch(240, 460, 1)
    backend.wait_for_text_on_screen("Enter number of SSKR shares", 5)
    backend.finger_touch(400, 290, 1) # 3
    backend.finger_touch(400, 560,1)
    backend.wait_for_text_on_screen("Enter threshold value", 5)
    backend.finger_touch(240, 290, 1) # 2
    backend.finger_touch(400, 560, 1)
    backend.wait_for_text_on_screen("SSKR Share", 5)
    backend.wait_for_text_on_screen("tuna next keep gyro", 1)
    backend.wait_for_text_on_screen("1 of 3", 1)
    backend.finger_touch(440, 550, 1)
    backend.wait_for_text_on_screen("SSKR Share", 5)
    backend.wait_for_text_on_screen("tuna next keep gyro", 1)
    backend.wait_for_text_on_screen("2 of 3", 1)
    backend.finger_touch(440, 550, 1)
    backend.wait_for_text_on_screen("SSKR Share", 5)
    backend.wait_for_text_on_screen("tuna next keep gyro", 1)
    backend.wait_for_text_on_screen("3 of 3", 1)
    backend.finger_touch(100, 550, 1)
    backend.wait_for_text_on_screen("Seed Tool", 5)
    backend.finger_touch(240, 550, 1)

@mark.use_on_backend("speculos")
def test_bip39_12word(firmware, backend, navigator, set_seed):
    if firmware.device == "nanos":
        nanos_bip39_12word(backend, navigator)
    elif firmware.device == "nanosp":
        skip("Skipping test for Nano S+ device")
    elif firmware.device == "nanox":
        skip("Skipping test for Nano X device")
    elif firmware.device == "stax":
        stax_bip39_12word(backend)
    elif firmware.device == "flex":
        flex_bip39_12word(backend)
