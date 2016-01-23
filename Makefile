INC=-I/home/felix/Entwicklung/userland/userland-master/host_applications/linux/libs/bcm_host/include -I/home/felix/Entwicklung/userland/userland-master -I/home/felix/Entwicklung/userland/userland-master/build/inc/interface/vcos

LIB=-lbcm_host -lEGL -lGLESv2 -lSDL -lm -L/home/felix/Entwicklung/userland/userland-master/build/lib

OBJ=build/main.o build/shader.o build/renderobject.o build/view.o build/matrix.o build/key.o build/bmp_rw.o

test: $(OBJ)
	gcc -o test $(OBJ) $(LIB)

build/main.o: main.c
	gcc -c main.c -o $@ $(INC)

build/shader.o: shader.c
	gcc -c shader.c -o $@ $(INC)

build/renderobject.o: renderobject.c
	gcc -c renderobject.c -o $@ $(INC)

build/view.o: view.c
	gcc -c view.c -o $@ $(INC)

build/matrix.o: matrix.c
	gcc -c matrix.c -o $@ $(INC)

build/key.o: ui/key.c
	gcc -c ui/key.c -o $@ $(INC)

build/bmp_rw.o: file_io/bmp_rw.c
	gcc -c file_io/bmp_rw.c -o $@ $(INC)

