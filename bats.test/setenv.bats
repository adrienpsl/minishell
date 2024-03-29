#!/usr/bin/env ./libs/bats-core/bin/bats
load './utils'

# test -------------------------------------------------------------------------
@test "setenv: should add in env toto=super" {
command="setenv toto=super
env$n"

expected="${print_prompt}setenv toto=super
${print_prompt}env" 

run_command "$command" "setenv: should add in env toto=super"
assert_line "toto=super" 
}

# test -------------------------------------------------------------------------
@test "setenv: should add in env PATH=toto;super, and delete previous one" {
# shellcheck disable=SC2116
lastPath=$(echo "$PATH")

expected="${print_prompt}setenv PATH=toto:super
${print_prompt}env" 

run_command "setenv PATH=toto:super
env$n" "setenv: should add in env PATH=toto;super, and delete previous one"

assert_line "PATH=toto:super" 
refute_line "$lastPath"
}

# test -------------------------------------------------------------------------
@test "setenv: should add in env 'toto super'" {
command="setenv toto=super
env$n"
expected="${print_prompt}setenv toto super
${print_prompt}env" 

run_command "$command" "setenv: should add in env 'toto super'"
assert_line "toto=super"
}

# test -------------------------------------------------------------------------
@test "setenv: should add in env 'PATH toto;super', and delete previous one" {
# shellcheck disable=SC2116
lastPath=$(echo "$PATH")

expected="${print_prompt}setenv PATH toto:super
${print_prompt}env" 

run_command "setenv PATH toto:super
env$n" "setenv: should add in env 'PATH toto;super', and delete previous one"

assert_line "PATH=toto:super"
refute_line "$lastPath"
}

# test -------------------------------------------------------------------------
@test "setenv : should print error if no argument" {

expected="${print_prompt}setenv
minishell: setenv: wrong arguments number$n" 

test_command "setenv$n" "$expected" "setenv : should print error if no argument"
}

# test -------------------------------------------------------------------------
@test "setenv: should print error if too much arguments" {
expected="${print_prompt}setenv a1 a2 a3
minishell: setenv: wrong arguments number$n" 

test_command "setenv a1 a2 a3$n" "$expected" "setenv: should print error if too much arguments"
}

# test -------------------------------------------------------------------------
@test "setenv: should print error if no = and one argument" {
expected="${print_prompt}setenv totosuper
minishell: setenv: if one argv, must contain =$n" 
test_command "setenv totosuper$n" "$expected" "setenv: should print error if no = and one argument"
}