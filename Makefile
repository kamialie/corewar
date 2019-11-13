SDL = ./sdl

all: $(SDL)

PWD = $(shell pwd)

$(SDL):
	tar -xf SDL2-2.0.10.zip
	mkdir SDL2-2.0.10/build
	CC=$(PWD)/SDL2-2.0.10/build-scripts/gcc-fat.sh
	cd ./SDL2-2.0.10/build; ../configure --prefix=$(PWD)/SDL2-2.0.10/build
	#make
	#make install

test:
	echo $(shell pwd)
