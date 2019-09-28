#!/usr/bin/env ./libs/bats-core/bin/bats
load './utils'

function setup() {
mkdir -p ls_test
touch ls_test/file_{1..4}
}

function teardown() {
rm -fr ls_test
}


# test -------------------------------------------------------------------------
@test "should print prompt and exit" {
test_command "" ""
}

# ------------------------------------------------------------------------------
@test "should print two pronpt and exit" {
command="$n"

test_command "$command" "$print_prompt""$n"
}

# ------------------------------------------------------------------------------
@test "should find with path 'ls -a ./ls_test' and exit" {
res_ls="$(ls -a ./ls_test)"

test_command  "ls -a ./ls_test$n" \
"$print_prompt"\
"ls -a ./ls_test$n"\
"$res_ls$n"
}

# ------------------------------------------------------------------------------
@test "should no find ls, because of removed PATH" {
command="unsetenv PATH
ls -a ./ls_test$n"

expected="${print_prompt}unsetenv PATH
${print_prompt}ls -a ./ls_test
minishell: command not found: ls$n"

test_command  "$command" "$expected"
}

# ------------------------------------------------------------------------------
@test "should print an error" {

test_command  "ls -a not_exist$n" \
"$print_prompt"\
"ls -a not_exist$n""ls: not_exist: No such file or directory$n"
}

# ------------------------------------------------------------------------------
@test "should find binary with absolute path" {
res_ls="$(ls -a ./ls_test)"

test_command  "/bin/ls -a ./ls_test$n" \
"$print_prompt/bin/ls -a ./ls_test
$res_ls$n"
}

# ------------------------------------------------------------------------------
@test "should find binary with absolute path and no PATH" {
res_ls="$(ls -a ./ls_test)"

command="unsetenv PATH
/bin/ls -a ./ls_test$n"

expected="$print_prompt""unsetenv PATH
$print_prompt/bin/ls -a ./ls_test
$res_ls$n"

test_command  "$command" "$expected"
}

# ------------------------------------------------------------------------------
# todo do that at school !
@test "memory test" {
res_ls="$(ls -a ./ls_test)"

command="unsetenv PATH
/bin/ls -a ./ls_test$n"

expected="$print_prompt""unsetenv PATH
$print_prompt/bin/ls -a ./ls_test
$res_ls$n"

test_command  "$command" "$expected"
}
