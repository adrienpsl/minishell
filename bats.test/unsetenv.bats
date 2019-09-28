#!/usr/bin/env ./libs/bats-core/bin/bats
load './utils'

# test -------------------------------------------------------------------------
@test "should delete in env" {

expected="${print_prompt}unsetenv PATH
${print_prompt}env" 

run_command "unsetenv PATH
env$n"

refute_line -e "^PATH="
}

# test -------------------------------------------------------------------------
@test "should delete inexinsting in env" {

test_command "unsetenv toto$n" "${print_prompt}unsetenv toto$n"
}

# test -------------------------------------------------------------------------
@test "should print error if no argument" {

expected="${print_prompt}unsetenv
minishell: unsetenv: wrong arguments number$n" 

test_command "unsetenv$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print error if too much arguments" {

expected="${print_prompt}unsetenv a1 a2 a3
minishell: unsetenv: wrong arguments number$n" 

test_command "unsetenv a1 a2 a3$n" "$expected"
}
