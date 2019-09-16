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

        #[[ env ]]
        src/env/ft_ms.env
        src/env/ft_ms.env.utils_1.c
        src/env/ft_ms.env.utils_2.c
        src/env/ft_ms.env.unsetenv.c
        src/env/ft_ms.env.setenv.c

        src/ft_ms.utils.c
        src/ft_ms.parse_str.c
        src/ft_ms.parser.get_line.c
        src/ft_ms.utils.find_binary.c
        src/ft_ms.raw_mode.c
        src/ft_ms.raw_mode.c
        src/ms__ftarray_adapter.c

        #[[ builtin ]]
        src/ft_ms.builtin.echo.c

        #[[ cd ]]
        src/cd/ft_ms.cd.c
        src/cd/ft_ms.cd.utils.c
        src/cd/ft_ms.cd.move_to_directory.c
        src/cd/ft_ms.cd.serialize_path.c

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

        test/ft_ms.env.utils.test.c
        test/main.test.c
        test/ms.parser.test.c
        test/ft_ms.utils.find_binary.test.c
        test/ft_ms.get_line.test.c
        test/ft_ms.env.test.c
        test/ft_ms.builtin.echo.test.c

        #[[ cd ]]
        test/ft_ms.cd.serialize_path.test.c
        test/ft_ms.cd.move_directory.test.c
        test/ft_ms.cd.test.c
        )
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME}_lib)

