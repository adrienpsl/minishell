#!/usr/bin/env ./libs/bats-core/bin/bats
load './utils'

function set_both_env() {

# set in result the env of minishell
# delete with awk a line that change between this two env.
result=$(./cmake-build-debug/minishell_e2e << EFO
$1
EFO
)
result="$(echo "$result" | awk '!/_=/')"
# do the some with env
real_env=$(env | awk '!/_=/')
}

## test -------------------------------------------------------------------------
#@test "should print env" {
#set_both_env "env"
#
#expected="${print_prompt}env
#$real_env
#$print_prompt" 
#
#assert_equal "$expected" "$result"
#}

# test -------------------------------------------------------------------------
@test "should print env -i" {
expected="${print_prompt}env -i$n"
test_command "env -i$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print env -i tata" {
expected="${print_prompt}env -i tata
minishell: command not found: tata$n"
test_command "env -i tata$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should add to env toto=tata and print it" {
expected="${print_prompt}env -i toto=tata
toto=tata$n"
test_command "env -i toto=tata$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should add to env toto=tata, super=toto and print it" {
expected="${print_prompt}env -i toto=tata super=toto
toto=tata
super=toto$n"
test_command "env -i toto=tata super=toto$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print an error with cd : env -i cd -" {
expected="${print_prompt}env -i cd -
minishell: line 40: cd: OLDPATH not set$n"
test_command "env -i cd -$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should give unexisting path to cd -" {
expected="${print_prompt}env -i OLDPATH=tototiti cd -
cd: no such file or directory: tototiti$n"
test_command "env -i OLDPATH=tototiti cd -$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print error cause binary not exist" {
expected="${print_prompt}env -i OLDPATH=tototiti lss -
minishell: command not found: lss$n"
test_command "env -i OLDPATH=tototiti lss -$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print because no PATH, no command" {
expected="${print_prompt}env -i  ls ~
minishell: command not found: ls$n"
test_command "env -i  ls ~$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should find with PATH the ls binary" {
expected="${print_prompt}env -i PATH=/bin ls toto
f1$n"
test_command "env -i PATH=/bin ls toto$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should delete PATH from env" {
expected="${print_prompt}env -u PATH ls
minishell: command not found: ls$n"
test_command "env -u PATH ls$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should delete PATH from env and OLDPATH" {
expected="${print_prompt}env -u PATH -u OLDPATH cd -
minishell: line 40: cd: OLDPATH not set$n"
test_command "env -u PATH -u OLDPATH cd -$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should print error, no element after -u" {
expected="${print_prompt}env -u PATH -u
env: option requires an argument -- u
usage: env [-i] [name=value ...] [-u name]
          [utility [argument ...]]$n"
test_command "env -u PATH -u$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "hoo fuck man, that's too hard ! n 0" {
expected="${print_prompt}env -i toto=titi env -u toto env cd
minishell: line 40: cd: HOME not set$n"
test_command "env -i toto=titi env -u toto env cd$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "hoo fuck man, that's too hard ! n 1" {
expected="${print_prompt}env -i toto=titi env -u toto env ls
minishell: command not found: ls$n"
test_command "env -i toto=titi env -u toto env ls$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "hoo fuck man, that's too hard ! n 2" {
expected="${print_prompt}env -i toto=titi env -u toto env -i PATH=/bin ls titi
ls: titi: No such file or directory$n"
test_command "env -i toto=titi env -u toto env -i PATH=/bin ls titi$n" "$expected"
}



