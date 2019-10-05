#!/usr/bin/env ./libs/bats-core/bin/bats
load './utils'

# test -------------------------------------------------------------------------
@test "should print the home path" {

expected="
/Users/adpusel/code/42/minishell:
$> echo ~
/Users/adpusel
"
test_command "echo ~$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print with /n" {
expected="
/Users/adpusel/code/42/minishell:
$> echo 'tata' \" titi \" man
'tata' \" titi \" man
"
test_command "echo 'tata' \" titi \" man$n" "$expected"
}

@test "should print witouh \n" {
expected="
/Users/adpusel/code/42/minishell:
$> echo -n 'tata' \" titi \" man
'tata' \" titi \" man"
test_command "echo -n 'tata' \" titi \" man$n" "$expected"
}
