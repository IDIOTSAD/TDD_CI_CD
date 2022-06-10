# Test sources
set(MODULE2_TEST_SRCS
        sample2
        )

# Include
include_directories(
        ${MODULE2_INCLUDE_PATH}
)

# Targets
add_executable(unit_tests2
        main.cpp
        ${MODULE2_TEST_SRCS}.cpp
        )

target_link_libraries(unit_tests2
        ${GTEST_LIBS}
        module2
        stdc++fs
        )

add_test(NAME UnitTest COMMAND
        ${CMAKE_CURRENT_BINARY_DIR}/unit_tests2)

set(matchString "/")
set(replaceWith "_")

foreach(test ${MODULE2_TEST_SRCS})
    string(REPLACE ${matchString} ${replaceWith} test_name ${test})
    set(test_name ${test_name})

    add_executable(${test_name}
            main.cpp
            ${test}.cpp)
    target_link_libraries(${test_name}
            ${GTEST_LIBS}
            module1
            stdc++fs
            )
    add_test(${test_name}
            ${test_name}
            --gtest_color=yes
            )
endforeach()