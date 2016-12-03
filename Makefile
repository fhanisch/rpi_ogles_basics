INC=-I/home/felix/Entwicklung/userland

LIB=-lbcm_host -lEGL -lGLESv2 -lSDL -lSDL_ttf -lm -L/home/felix/Entwicklung/userland/build/lib

OBJ=build/main.o build/shader.o build/renderobject.o build/view.o build/matrix.o build/key.o build/bmp_rw.o

test: $(OBJ)
	gcc -o test $(OBJ) $(LIB)

build/main.o: src/main.c
	gcc -c src/main.c -o $@ $(INC)

build/shader.o: src/shader.c
	gcc -c src/shader.c -o $@ $(INC)

build/renderobject.o: src/renderobject.c src/renderobject.h
	gcc -c src/renderobject.c -o $@ $(INC)

build/view.o: src/view.c src/view.h
	gcc -c src/view.c -o $@ $(INC)

build/matrix.o: src/matrix.c
	gcc -c src/matrix.c -o $@ $(INC)

build/key.o: src/ui/key.c
	gcc -c src/ui/key.c -o $@ $(INC)

build/bmp_rw.o: src/file_io/bmp_rw.c
	gcc -c src/file_io/bmp_rw.c -o $@ $(INC)

