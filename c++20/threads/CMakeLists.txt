set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(cpp11_ref_examples ref_examples.cpp)
add_executable(cpp11_this_thread_examples this_thread_examples.cpp)
add_executable(cpp20_jthread_examples examples.cpp)

foreach(target IN ITEMS cpp11_ref_examples cpp11_this_thread_examples cpp20_jthread_examples)
    set_target_properties(${target} PROPERTIES
        CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF
    )
    target_link_libraries(${target} PRIVATE Threads::Threads)
    target_compile_options(${target} PRIVATE
        -Wall -Wextra -Wpedantic -Wshadow -Wconversion
    )
endforeach()

set_target_properties(cpp20_jthread_examples PROPERTIES CXX_STANDARD 20)
