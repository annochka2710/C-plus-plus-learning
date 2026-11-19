foreach(standard IN ITEMS 98 11 14 17 20 23)
    add_executable(cpp${standard}_using_examples examples.cpp)
    set_target_properties(cpp${standard}_using_examples PROPERTIES
        CXX_STANDARD ${standard}
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )
    target_compile_options(cpp${standard}_using_examples PRIVATE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion
    )
endforeach()
