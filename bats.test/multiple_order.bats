#!/usr/bin/env ./libs/bats-core/bin/bats
load './utils'

# test -------------------------------------------------------------------------
@test "should echo ; cd ; cd -" {
expected="
/Users/adpusel/code/42/minishell_new:
$> echo 'toto' ; cd ; cd -
'toto'
/Users/adpusel/code/42/minishell_new
"

test_command "echo 'toto' ; cd ; cd -$n" "$expected"
}

# test -------------------------------------------------------------------------
@test "should do a lot of stuff with a lot of pb" {
expected="
/Users/adpusel/code/42/minishell_new:
$> setenv PATH=toto ;echo \$PATH; unsetenv HOME; ls; cd ~; cd -; setenv HOME=/; setenv PATH=/bin; ls null
toto
minishell: command not found: ls
minishell: line 39: cd: HOME not set
minishell: line 39: cd: OLDPATH not set
ls: null: No such file or directory
"

test_command "setenv PATH=toto ;echo \$PATH; unsetenv HOME; ls; cd ~; cd -; setenv HOME=/; setenv PATH=/bin; ls null$n" "$expected"
}

@test "should do a lot of stuff with no pb" {
expected="
/Users/adpusel/code/42/minishell_new:
$> cd -; cd ; cd - ; mkdir toto; touch toto/f1; ls -a toto; setenv minh=jolie; setenv minh tresjolie; echo \$minh; unsetenv minh ; \$minh
minishell: line 39: cd: OLDPATH not set
/Users/adpusel/code/42/minishell_new
.
..
f1
tresjolie

"

test_command "cd -; cd ; cd - ; mkdir toto; touch toto/f1; ls -a toto; setenv minh=jolie; setenv minh tresjolie; echo \$minh; unsetenv minh ; \$minh$n" "$expected"
}


@test "same test but with no ;" {
expected="
/Users/adpusel/code/42/minishell_new:
$> cd - $n cd  $n cd -  $n mkdir toto $n touch toto/f1 $n ls -a toto $n setenv minh=jolie $n setenv minh tresjolie $n echo \$minh $n unsetenv minh  $n \$minh


"

test_command "cd - $n cd  $n cd -  $n mkdir toto $n touch toto/f1 $n ls -a toto $n setenv minh=jolie $n setenv minh tresjolie $n echo \$minh $n unsetenv minh  $n \$minh$n" "$expected"
}