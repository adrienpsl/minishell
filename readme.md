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
