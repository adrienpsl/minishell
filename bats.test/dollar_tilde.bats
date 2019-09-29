#!/usr/bin/env ./libs/bats-core/bin/bats
load './utils'

# test -------------------------------------------------------------------------
@test "should print nothing" {

expected="$print_prompt$n" 
test_command "$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print only the command" {

expected="${print_prompt}toto
minishell: command not found: toto$n" 
test_command "toto$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print only the command $" {

expected="${print_prompt}$
minishell: command not found: "'$'"$n"
test_command "$""$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print only the command toto$" {

expected="${print_prompt}toto$
minishell: command not found: "'toto$'"$n"
test_command "toto$""$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print only the command toto$/" {

expected="${print_prompt}toto$/
minishell: command not found: "'toto$/'"$n"
test_command "toto$/""$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print only the command toto$/\$toto" {
export toto=titi;

expected="${print_prompt}toto$/\$toto
minishell: command not found: "'toto$/titi'"$n"
test_command "toto$/\$toto""$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print only the command toto$/\$toto~\$a" {
export toto=\$t;
export a=op;

expected="${print_prompt}toto$/\$toto~\$a
minishell: command not found: toto$/\$t/Users/adpuselop$n"
test_command "toto$/\$toto~\$a""$n" "$expected"
}

