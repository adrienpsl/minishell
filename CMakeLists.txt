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
        src/ms.binary.handle.c
        src/ms.builtin.env.c
        src/ms.builtin.env.utils.c
        src/ms.parser.c
        src/ms.builtin.cd.c
        src/ms.builtin.echo.c
        src/utils.c src/ms.builtin.setenv.c src/ms.builtin.unsetenv.c src/ms.loop.c src/ms.parser.get_line.c src/ms.builtin.exit.c src/ms.binary.find.c src/ms.parser.h src/ms.test_utils.c src/ms.signal.c)

target_include_directories(minishell_lib PUBLIC includes)

add_executable(
        minishell
        src/main.c
#        test/test_main.c
#        test/test_function.c
        includes/minishell.limit.h includes/minishell.limit.h includes/minishell.error.h test/test.c test/test.h test/test_function.c)



#*------------------------------------*\
#    --  LINKING --
#*------------------------------------*/
target_link_libraries(minishell_lib libft)

target_link_libraries(minishell libft)
target_link_libraries(minishell minishell_lib)
