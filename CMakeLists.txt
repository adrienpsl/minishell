cmake_minimum_required(VERSION 3.14)

project(minishell C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "-Weverything")
set(CMAKE_C_FLAGS "-Wextra -Werror -Wall")

add_subdirectory(libft)
include_directories(includes)

# ------------------------------------------------------------------------------
#    lib module
# ------------------------------------------------------------------------------
add_library(${PROJECT_NAME}_lib
        src/ft_ms.env.utils.c
        src/ft_ms.utils.c
        src/ft_ms.env.parse.c
        src/ft_ms.env.add.c
        src/ft_ms.parse_str.c
        src/ft_ms.parser.get_line.c
        src/ft_ms.utils.find_binary.c)

target_link_libraries(${PROJECT_NAME}_lib libft)

# ------------------------------------------------------------------------------
#    main module
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

# ------------------------------------------------------------------------------
#    test module
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME}_test
        test/main.test.c

        test/env.test.c
        test/main.test.c
        test/ms.parser.test.c test/ft_ms.utils.find_binary.test.c)
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib)

