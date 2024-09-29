cmake_minimum_required(VERSION 3.10)

if(${CMAKE_VERSION} VERSION_LESS 3.10)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# project information
project(unit_tests
        VERSION 1.8.0
	      DESCRIPTION "Unit tests for app-seed-tool Ledger Application"
        LANGUAGES C)


# guard against bad build-type strings
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

include(CTest)
ENABLE_TESTING()

# specify C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -pedantic -g -O0 --coverage")

set(GCC_COVERAGE_LINK_FLAGS "--coverage -lgcov")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

# apk install package function
function(install_apk_packages)
  foreach(package ${ARGN})
    execute_process(
      COMMAND bash -c "apk add ${package}"
      RESULT_VARIABLE result
      OUTPUT_VARIABLE output
      ERROR_VARIABLE error
    )

    if(${result} EQUAL 0)
      message(STATUS "Installed ${package} package")
    else()
      message(FATAL_ERROR "Failed to install package: ${package}\n"
                          "Command: ${output}\n"
                          "Error: ${error}")
    endif()
  endforeach()
endfunction()

# Check if linux-headers package is installed
if(NOT EXISTS "/usr/include/linux/version.h")
  install_apk_packages(linux-headers)
else()
  message(STATUS "linux-headers package found")
endif()

include(ExternalProject)
if (PRECOMPILED_DEPENDENCIES_DIR)
  message(STATUS "Using OpenSSL from ${PRECOMPILED_DEPENDENCIES_DIR}")
  set(INSTALL_DIR ${PRECOMPILED_DEPENDENCIES_DIR})
  add_library(openssl STATIC IMPORTED)
else()
  message(STATUS "Building OpenSSL...")
  set(INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/install)

  set(OPENSSL_CFLAGS "${CMAKE_C_FLAGS}")
  get_directory_property(compile_options COMPILE_OPTIONS)
  foreach (opt ${compile_options})
    string(APPEND OPENSSL_CFLAGS " ${opt}")
  endforeach ()
  if (CMAKE_C_COMPILER_TARGET)
    string(APPEND OPENSSL_CFLAGS " --target=${CMAKE_C_COMPILER_TARGET}")
  endif ()
  if (CMAKE_SYSROOT)
    string(APPEND OPENSSL_CFLAGS " -isystem${CMAKE_SYSROOT}/include")
  endif ()
  string(APPEND OPENSSL_CFLAGS " -Wno-unused-parameter -Wno-missing-field-initializers")

  ExternalProject_Add(
    openssl
    URL https://www.openssl.org/source/openssl-3.0.13.tar.gz
    URL_HASH SHA256=88525753f79d3bec27d2fa7c66aa0b92b3aa9498dafd93d7cfa4b3780cdae313
    CONFIGURE_COMMAND ./Configure "CC=${CMAKE_C_COMPILER}" "CFLAGS=${OPENSSL_CFLAGS}" no-afalgeng no-aria no-asan no-asm no-async no-autoalginit no-autoerrinit no-autoload-config no-bf no-buildtest-c++ no-camellia no-capieng no-cast no-chacha no-cmac no-cms no-comp no-crypto-mdebug no-ct no-deprecated no-des no-devcryptoeng no-dgram no-dh no-dsa no-dso no-dtls no-ec2m no-ecdh no-egd no-engine no-err no-external-tests no-filenames no-fuzz-afl no-fuzz-libfuzzer no-gost no-idea no-makedepend no-md2 no-md4 no-mdc2 no-msan no-multiblock no-nextprotoneg no-ocb no-ocsp no-pinshared no-poly1305 no-posix-io no-psk no-rc2 no-rc4 no-rc5 no-rdrand no-rfc3779 no-scrypt no-sctp no-seed no-shared no-siphash no-sm2 no-sm3 no-sm4 no-sock no-srp no-srtp no-sse2 no-ssl no-ssl3-method no-ssl-trace no-stdio no-tests no-threads no-tls no-ts no-ubsan no-ui-console no-unit-test no-whirlpool no-zlib no-zlib-dynamic linux-armv4 --prefix=${INSTALL_DIR}
    BUILD_COMMAND make
    INSTALL_COMMAND make install_sw
    BUILD_IN_SOURCE 1
  )
endif()

# Fetch cmocka
find_package(cmocka QUIET)
include(FetchContent)
FetchContent_Declare(
    cmocka
    GIT_REPOSITORY https://gitlab.com/cmocka/cmocka.git
    GIT_TAG        cmocka-1.1.7
    GIT_SHALLOW    1
)
set(WITH_STATIC_LIB ON CACHE BOOL "CMocka: Build with a static library" FORCE)
set(WITH_CMOCKERY_SUPPORT OFF CACHE BOOL "CMocka: Install a cmockery header" FORCE)
set(WITH_EXAMPLES OFF CACHE BOOL "CMocka: Build examples" FORCE)
set(UNIT_TESTING OFF CACHE BOOL "CMocka: Build with unit testing" FORCE)
set(PICKY_DEVELOPER OFF CACHE BOOL "CMocka: Build with picky developer flags" FORCE)
FetchContent_MakeAvailable(cmocka)

add_compile_definitions(TEST DEBUG=0 SKIP_FOR_CMOCKA)
add_compile_definitions(TARGET_NANOS HAVE_HASH HAVE_HMAC HAVE_SHA224 HAVE_SHA256 HAVE_SHA512 HAVE_PBKDF2 HAVE_ECC HAVE_CRC HAVE_RNG IO_HID_EP_LENGTH=64)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib $ENV{LEDGER_SECURE_SDK}/include $ENV{LEDGER_SECURE_SDK}/lib_cxng/src $ENV{LEDGER_SECURE_SDK}/lib_cxng/include $ENV{LEDGER_SECURE_SDK}/lib_ux/include $ENV{LEDGER_SECURE_SDK}/lib_bagl/include)

# add src
install_apk_packages(linux-headers)
set(ExternalProject_Get_property(openssl INSTALL_DIR))
set(BOLOS_SOURCES ./lib/bolos/cx_bn.c ./lib/bolos/cx_crc.c ./lib/bolos/cx_mpi.c)
set(LIBCXNG_SOURCES $ENV{LEDGER_SECURE_SDK}/lib_cxng/src/cx_ram.c $ENV{LEDGER_SECURE_SDK}/lib_cxng/src/cx_hash.c $ENV{LEDGER_SECURE_SDK}/lib_cxng/src/cx_sha256.c $ENV{LEDGER_SECURE_SDK}/lib_cxng/src/cx_sha512.c $ENV{LEDGER_SECURE_SDK}/lib_cxng/src/cx_pbkdf2.c $ENV{LEDGER_SECURE_SDK}/lib_cxng/src/cx_hmac.c $ENV{LEDGER_SECURE_SDK}/lib_cxng/src/cx_utils.c)
set(TESTLIB_SOURCES ./lib/testutils.c)
add_library(testutils SHARED ${TESTLIB_SOURCES} ${LIBCXNG_SOURCES} ${BOLOS_SOURCES})
target_include_directories(testutils PUBLIC ${INSTALL_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/../../src/common/sskr/sss ${CMAKE_CURRENT_SOURCE_DIR}/../../src/commonsskr)
target_link_directories(testutils PUBLIC ${INSTALL_DIR}/lib)
target_link_libraries(testutils PUBLIC ssl crypto)
add_dependencies(testutils openssl)

add_library(sss SHARED ../../src/common/sskr/sss/sss.c ../../src/common/sskr/sss/interpolate.c)
target_include_directories(sss PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../src/common/sskr/sss)

add_library(sskr SHARED ../../src/common/sskr/sskr.c)
target_include_directories(sskr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../src/common/sskr/sss ${CMAKE_CURRENT_SOURCE_DIR}/../../src/common/sskr)

# add cmocka tests
add_executable(test_sss tests/sss.c)
target_link_libraries(test_sss PUBLIC cmocka gcov testutils sss)

add_executable(test_sskr tests/sskr.c)
target_link_libraries(test_sskr PUBLIC cmocka gcov testutils sskr sss)

add_executable(test_bip39 ./tests/bip39.c ../../src/common/bip39/seed_rom_variables.c  ../../src/common/bip39/seed_bip39.c)
target_include_directories(test_bip39 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../src/common)
target_link_libraries(test_bip39 PUBLIC cmocka gcov testutils)

add_executable(test_roundtrip ./tests/roundtrip.c ../../src/common/bip39/seed_rom_variables.c ../../src/common/bip39/seed_bip39.c ../../src/common/sskr/seed_rom_variables.c ../../src/common/sskr/seed_sskr.c)
target_include_directories(test_roundtrip PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../src ${CMAKE_CURRENT_SOURCE_DIR}/../../src/common)
target_link_libraries(test_roundtrip PUBLIC cmocka gcov testutils sskr sss)

add_executable(test_words ./tests/words.c ../../src/common/bip39/seed_rom_variables.c ../../src/common/bip39/seed_bip39.c ../../src/common/sskr/seed_rom_variables.c ../../src/common/sskr/seed_sskr.c)
target_include_directories(test_words PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../src/common)
target_link_libraries(test_words PUBLIC cmocka gcov testutils sskr sss)

foreach(target test_sss test_sskr test_bip39 test_roundtrip test_words)
    add_test(NAME ${target} COMMAND ${target})
endforeach()
