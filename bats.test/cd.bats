#!/usr/bin/env ./libs/bats-core/bin/bats
load './utils'

function test_cd() {
run ./cmake-build-debug/minishell_e2e << EFO
$1
exit
EFO

assert_output "$2"
}


# test -------------------------------------------------------------------------
@test "should go home" {
expected="
/Users/adpusel/code/42/minishell:
$> cd

/Users/adpusel:
$> exit"

test_cd "cd" "$expected"
}

# test -------------------------------------------------------------------------
@test "should go previous destination" {
expected="
/Users/adpusel/code/42/minishell:
$> cd

/Users/adpusel:
$> cd -
/Users/adpusel/code/42/minishell

/Users/adpusel/code/42/minishell:
$> exit"

test_cd "cd$n""cd -" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print error if no HOME" {
unset HOME
expected="
/Users/adpusel/code/42/minishell:
$> cd
minishell: line 40: cd: HOME not set

/Users/adpusel/code/42/minishell:
$> cd -
minishell: line 40: cd: OLDPATH not set

/Users/adpusel/code/42/minishell:
$> exit"

test_cd "cd$n""cd -" "$expected"
}

# test -------------------------------------------------------------------------
@test "should find cd with no PATH" {
expected="
/Users/adpusel/code/42/minishell:
$> unsetenv PATH

/Users/adpusel/code/42/minishell:
$> cd

/Users/adpusel:
$> cd -
/Users/adpusel/code/42/minishell

/Users/adpusel/code/42/minishell:
$> exit"

test_cd "unsetenv PATH
cd
cd -" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print path with 2 argument" {
expected="
/Users/adpusel/code/42/minishell:
$> cd minishell ft_ls
/Users/adpusel/code/42/ft_ls

/Users/adpusel/code/42/ft_ls:
$> exit"

test_cd "cd minishell ft_ls" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print too much argument" {
expected="
/Users/adpusel/code/42/minishell:
$> cd minishell ft_ls tto
cd: to much argument

/Users/adpusel/code/42/minishell:
$> exit"

test_cd "cd minishell ft_ls tto" "$expected"
}
