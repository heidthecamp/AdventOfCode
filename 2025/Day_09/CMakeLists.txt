add_executable(
    day09
    main.cpp
    common.hpp
    part1.cpp
    part2.cpp
)

target_link_libraries(
    day09
    PUBLIC
        SDL2::SDL2
)

target_include_directories(
    day09
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)