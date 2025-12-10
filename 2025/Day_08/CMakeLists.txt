add_executable(
    day08
    main.cpp
    common.hpp
    part1.cpp
    part2.cpp
)

target_include_directories(
    day08
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)