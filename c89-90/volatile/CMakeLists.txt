add_executable(c90_volatile_examples examples.c)
add_executable(c90_volatile_signal signal_example.c)

foreach(volatile_target IN ITEMS c90_volatile_examples c90_volatile_signal)
    set_target_properties(${volatile_target} PROPERTIES
        C_STANDARD 90
        C_STANDARD_REQUIRED ON
        C_EXTENSIONS OFF
    )
    target_compile_options(${volatile_target} PRIVATE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wstrict-prototypes
    )
endforeach()
