cmake_minimum_required(VERSION 3.10)

project(NeoFuzzer VERSION 0.1.9 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,bugprone-*,cert-*,clang-analyzer-*,-cert-err58-cpp,misc-*)

# BOLOS SDK
set(BOLOS_SDK $ENV{BOLOS_SDK})
add_compile_definitions(IO_HID_EP_LENGTH=64)

# Fuzzer target
set(APP_SRC_DIR "../")

add_compile_definitions(HAVE_ECC HAVE_HASH HAVE_SHA256 HAVE_RIPEMD160)
include_directories(.
        ../src/lib
        "${APP_SRC_DIR}/app/glyphs"
        "${BOLOS_SDK}/include"
        "${BOLOS_SDK}/lib_cxng/include"
        "${BOLOS_SDK}/lib_ux/include"
        "${APP_SRC_DIR}/app/deps/BLAKE2/ref/"
)

add_compile_options(-g -ggdb2 -O3)

# Build with code coverage generation
if(CODE_COVERAGE)
    if(CMAKE_C_COMPILER_ID MATCHES "(Apple)?[Cc]lang")
        add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
        add_link_options(-fprofile-instr-generate -fcoverage-mapping)
    elseif(CMAKE_C_COMPILER_ID MATCHES "GNU")
        add_compile_options(-fprofile-arcs -ftest-coverage)
        link_libraries(gcov)
    else()
        message(FATAL_ERROR "Unsupported compiler used with code coverage generation")
    endif()
endif()




set(APP_SOURCES
    ${APP_SRC_DIR}/app/src/parser.c
    #    ${APP_SRC_DIR}/app/src/coin_standard.h
    #    ${APP_SRC_DIR}/deps/ledger-zxlib/src/app_mode.c
    #    ${APP_SRC_DIR}/deps/ledger-zxlib/src/base58.c
    #    ${APP_SRC_DIR}/deps/ledger-zxlib/src/bignum.c
    #    ${APP_SRC_DIR}/deps/ledger-zxlib/include/bignum.h
    #    ${APP_SRC_DIR}/deps/ledger-zxlib/src/hexutils.c
    #    ${APP_SRC_DIR}/deps/ledger-zxlib/src/zxmacros.c
    ${APP_SRC_DIR}/deps/ledger-zxlib/src/zbuffer.c
    ${APP_SRC_DIR}/app/src/c_api/rust.c
    ${APP_SRC_DIR}/app/src/crypto.c
    ${APP_SRC_DIR}/deps/ledger-zxlib/src/app_mode.c
    ${APP_SRC_DIR}/deps/ledger-zxlib/src/zxmacros.c
    ${APP_SRC_DIR}/deps/ledger-zxlib/src/sigutils.c
    #    ${APP_SRC_DIR}/deps/ledger-zxlib/src/zxformat.c
    #
    #    ${APP_SRC_DIR}/app/src/parser.c

)

add_definitions(
    -DLEDGER_MAJOR_VERSION=3
    -DLEDGER_MINOR_VERSION=3
    -DOS_IO_SEPROXYHAL
    -DHAVE_BAGL
    -DHAVE_SPRINTF
    -DHAVE_IO_USB
    -DHAVE_L4_USBLIB
    -DIO_USB_MAX_ENDPOINTS=7
    -DIO_HID_EP_LENGTH=64
    -DHAVE_USB_APDU
    -DUSB_SEGMENT_SIZE=64
    -DHAVE_BOLOS_APP_STACK_CANARY
    -DHAVE_WEBUSB
    -DWEBUSB_URL_SIZE_B=0
    -DWEBUSB_URL=""
    -DHDPATH_LEN_DEFAULT=5
    -DAPP_STANDARD
    -DCX_RIPEMD160_SIZE=20
    -DTARGET_NANOS
    -DIO_SEPROXYHAL_BUFFER_SIZE_B=128
    -DCX_CURVE_256K1=33
)


add_executable(fuzz_message
        fuzz_app_blockstack.c
        os_mocks.c
        ${APP_SOURCES}
)

target_include_directories(fuzz_message PUBLIC
  #${APP_SRC_DIR}/deps/BLAKE2/ref/
  ${APP_SRC_DIR}/deps/ledger-zxlib/include
  ${APP_SRC_DIR}/app/src
  ${APP_SRC_DIR}/app/rust/include/
  ${APP_SRC_DIR}/deps/sha512/
  #${APP_SRC_DIR}/app/src/lib
        $#{APP_SRC_DIR}/app/src/common
        )


add_custom_target(
    rslib
    COMMAND cd ../${APP_SRC_DIR}/app/rust && CARGO_HOME="$(HOME)/rust/.cargo" cargo build --profile dev
)

add_dependencies(fuzz_message rslib)

target_compile_options(fuzz_message PUBLIC -fsanitize=fuzzer,address,undefined)
target_link_options(fuzz_message PUBLIC -lbsd -L${APP_SRC_DIR}/../app/rust/target/debug -lrslib -fsanitize=fuzzer,address,undefined)
target_link_libraries(fuzz_message librslib.a)