cmake_minimum_required(VERSION 3.14)

project(minishell_new C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "-Weverything")
set(CMAKE_C_FLAGS "-Wextra -Werror -Wall")

add_subdirectory(libft)
include_directories(includes)

# ------------------------------------------------------------------------------
#    lib module
# ------------------------------------------------------------------------------
add_library(${PROJECT_NAME}_lib
        #[[ builtin ]]
        src/cd/ft_ms.cd.c
        src/cd/ft_ms.cd.change_dir.c

        #[[ utils ]]
        src/utils.c
        src/ft_ms.env.c
        )

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
        test/ft_ms.cd.test.c
        test/ft_ms.utils.test.c
        test/ft_ms.env.test.c
        )
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib)

# ------------------------------------------------------------------------------
#    test raw mode
# ------------------------------------------------------------------------------
add_executable(${PROJECT_NAME}_raw
        test/main.test.raw_mode.c
        )
target_link_libraries(${PROJECT_NAME}_raw ${PROJECT_NAME}_lib)

