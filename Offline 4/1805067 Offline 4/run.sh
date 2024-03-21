flex 1805067.l
bison -d 1805067.y
g++ lex.yy.c 1805067.tab.c -w
./a.out input.c