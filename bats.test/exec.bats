#!/usr/bin/env ./libs/bats-core/bin/bats
load 'libs/utils'

# data 
# ------------------------------------------------------------------------------
print_prompt="
/Users/adpusel/code/42/minishell_new:
$> "


# test -------------------------------------------------------------------------
@test "only exit is write" {
run ./cmake-build-debug/minishell_e2e << EFO
exit
EFO

assert_output "$print_prompt"
}

## ------------------------------------------------------------------------------
#@test "one enter and exit" {
#
#run ./cmake-build-debug/minishell_new -t  << EFO
#
#exit
#EFO
#
#assert_output "$print_prompt$print_prompt"
#}
#
## ------------------------------------------------------------------------------
#@test "should print ls and exit" {
#mkdir ls_test
#touch ls_test/file_{1..4}
#
## the running 
#run ./cmake-build-debug/minishell_new -t  << EFO
#ls -a ls_test
#exit
#EFO
#
#ls=$(ls -a ls_test)
#rm -fr ls_test
#
#assert_output  "$print_prompt$ls
#$print_prompt"
#}

## ------------------------------------------------------------------------------
#@test "should print ls error" {
# 
#run ./cmake-build-debug/minishell_new -t  << EFO
#ls -a not_exist
#exit
#EFO
#ls_error="$(printf "%s\n" "ls: not_exist: No such file or directory")"
# 
#assert_output "$print_prompt$ls_error$print_prompt"
#}

## ------------------------------------------------------------------------------
#@test "should find ls with absobulte path" {
# 
#run ./cmake-build-debug/minishell_new -t  << EFO
#ls -a 
#exit
#EFO
##ls_error="$()"
# 
#assert_output "$print_prompt$ls_error$print_prompt"
#}
