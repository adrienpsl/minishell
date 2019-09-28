load 'libs/bats-support/load'
load 'libs/bats-assert/load'

# data 
# ------------------------------------------------------------------------------
n=$'\n'
print_prompt=$'\n'"/Users/adpusel/code/42/minishell_new:"$'\n'"$> ";

function test_command() {
data=$1
data+="exit"

end=$2
end+="$print_prompt""exit"

run ./cmake-build-debug/minishell_e2e << EFO
$data
EFO

assert_output "$end"
}

function run_command() {
data=$1
data+="exit"

end=$2
end+="$print_prompt""exit"

run ./cmake-build-debug/minishell_e2e << EFO
$data
EFO

}

