add_executable(cpp98_mutable_examples examples.cpp)
set_target_properties(cpp98_mutable_examples PROPERTIES
    CXX_STANDARD 98
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_compile_options(cpp98_mutable_examples PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion
)
