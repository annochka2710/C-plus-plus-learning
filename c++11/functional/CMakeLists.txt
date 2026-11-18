add_executable(cpp11_functional_examples examples.cpp)
set_target_properties(cpp11_functional_examples PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_compile_options(cpp11_functional_examples PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion
)
