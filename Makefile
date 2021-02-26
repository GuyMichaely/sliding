main:
	gcc slide.c -o slide -lncurses -Dconst=
debug:
	gcc slide.c -g -o slide -lncurses -Dconst=
