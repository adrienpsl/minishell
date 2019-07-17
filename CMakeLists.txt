cmake_minimum_required(VERSION 3.14)

project(minishell C)

set(CMAKE_C_STANDARD 99)
#set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -og -g3")
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g")
#-fsanitize=memory-fsanitize-memory-track-origins=2 -fsanitize=address

#include_directories(PRIVATE includes)
add_subdirectory(libft)

add_library(minishell_lib STATIC
        src/path.c
        src/builtin.env.c
        src/builtin.env.utils.c
        src/parser.c
        src/builtin.cd.c
        src/builtin.echo.c
        src/utils.c src/builtin.setenv.c src/builtin.unsetenv.c src/launch.c)

target_include_directories(minishell_lib PUBLIC includes)

add_executable(
        minishell
        src/main.c
        test/test_main.c
        test/test_function.c
        )



#*------------------------------------*\
#    --  LINKING --
#*------------------------------------*/
target_link_libraries(minishell_lib libft)

target_link_libraries(minishell libft)
target_link_libraries(minishell minishell_lib)
