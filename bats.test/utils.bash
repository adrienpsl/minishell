load 'libs/bats-support/load'
load 'libs/bats-assert/load'

# data 
# ------------------------------------------------------------------------------
n=$'\n'
print_prompt=$'\n'"/Users/adpusel/code/42/minishell:"$'\n'"$> ";
result=""


function test_command() {
data=$1
data+="exit"

end=$2
end+="$print_prompt""exit"
unset _

run ./cmake-build-debug/minishell_e2e << EFO
$data
EFO

valgrind --log-fd=1 ./cmake-build-debug/minishell_e2e << EFO | grep "definitely lost" >> filetest
$data
EFO

assert_output "$end"
}

function run_command() {
data=$1
data+="exit"

end+="$print_prompt""exit"

result="$( ./cmake-build-debug/minishell_e2e << EFO
$data
EFO
)"

echo "$2" >> filetest
valgrind --log-fd=1 ./cmake-build-debug/minishell_e2e << EFO | grep "definitely lost" >> filetest
$data
EFO

run echo "$result"
}

function print_name()
{
  echo -n;
}