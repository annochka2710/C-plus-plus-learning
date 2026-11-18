add_executable(cpp11_functional_examples examples.cpp)
set_target_properties(cpp11_functional_examples PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_compile_options(cpp11_functional_examples PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion
)

foreach(example IN ITEMS lambda event)
    add_executable(cpp11_${example}_examples ${example}_examples.cpp)
    set_target_properties(cpp11_${example}_examples PROPERTIES
        CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF
    )
    target_compile_options(cpp11_${example}_examples PRIVATE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion
    )
endforeach()

add_executable(cpp11_event_checks event_checks.cpp)
add_executable(cpp11_delegate_example ../../patterns/delegate.cpp)
foreach(target IN ITEMS cpp11_event_checks cpp11_delegate_example)
    set_target_properties(${target} PROPERTIES
        CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF
    )
    target_compile_options(${target} PRIVATE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion
    )
endforeach()
