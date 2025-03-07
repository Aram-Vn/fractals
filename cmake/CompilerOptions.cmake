
set(COMMON_COMPILE_OPTIONS
    -Wall
    -Wextra
    -Wshadow
    -Wswitch
    -pedantic
    -Wformat=2
    -Wnull-dereference
    -Wunused-parameter
    -Wunreachable-code
    -Wimplicit-fallthrough
)

set(COMMON_ERROR_OPTIONS
    -Werror
    -Werror=return-type
    -Werror=uninitialized
    -Werror=unused-result
    -Werror=strict-overflow
)

set(SANITIZER_FLAGS
    -fsanitize=undefined
    -fsanitize=address
    -fno-omit-frame-pointer
)