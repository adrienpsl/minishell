# refactoring of env :
- env will loop on himself
- no need to the struct g_env
- the struct env, will be use in the loop exc, not before.


the bats commands :

mkdir -p libs

git clone  https://github.com/sstephenson/bats ./libs/bats
git clone https://github.com/ztombol/bats-support ./libs/bats-support
git clone https://github.com/ztombol/bats-assert ./libs/bats-assert

faire plus attention quand je quit, evidaement j'ai eu une fuite memoire, 
je return avant de free ! 

# ma derniere correction : 
c'etait vraiment une super correction :
les command styles : 
- grep -E3 "readdir" src/*.c check that I didn't do bad stuff  E is for the number of line between the match
- nm -u ft_ls pour voir direct les fonctions que j'utilise 
- grep -n ? 
- comment relinker le header ?