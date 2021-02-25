main:
	gcc slide.c -o slide -lncurses -Dconst=
test:
	gcc slide.c -g -o slide -lncurses -Dconst=
