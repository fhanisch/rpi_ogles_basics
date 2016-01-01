#kompilieren
cd build
gcc -c ../main.c ../shader.c ../renderobject.c ../view.c ../matrix.c ../ui/key.c -I/home/felix/Entwicklung/userland/userland-master/host_applications/linux/libs/bcm_host/include -I/home/felix/Entwicklung/userland/userland-master -I/home/felix/Entwicklung/userland/userland-master/build/inc/interface/vcos
#linken
gcc -o test main.o shader.o renderobject.o view.o matrix.o key.o -lbcm_host -lEGL -lGLESv2 -L/home/felix/Entwicklung/userland/userland-master/build/lib
cd ..
