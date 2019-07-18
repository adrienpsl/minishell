# builtin 
-- cd
-- echo
-- setenv
-- unsetenv
-- exit

# builtin env

2 options to implements :  
- i // execute with no env
- u // u remove the env specified var

refractoring de la fonction: 

# fix 
- error fork 
- error execve


# toDo 
- handle multiple argv with split ;
- print where I am in the shell
- refaire bien env qui n'est pas complet.
- errror handling 

- I will do now the big test ? in shell or in c ?

- use a buffer to define the size max argv