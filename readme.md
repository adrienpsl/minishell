## env intern variable
[x] parse
[x] convert 
[X]  delete 
[X]  add

## get parse entry
[X] parse with ;
[X] parse with " "

# tap test
** built in 
   - all the same prototype
       [X] setenv
       [X] unsetenv
       [X] env 
       [X] echo
       [X] cd
       * exit

- signal - and with get_line
- link all


# test 
test les fuites memoire avec env -u de env -u en recusif
test env -- env -



# pseudo code env 
** le tmp env, une utils return the good one
** 

# note of the day

- la function system n'influt pas sur mon program
-   j'ai une fonction qui attents sont buffer d'une autre, et c'est grave relou 
    car je dois lui donner tout ca tout ca. 
    comme je dois gerer les buffers avec les possibiliter de kill, 
    je vais faire une sorte de garbage collector !
    
