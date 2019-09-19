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
        )
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib)

