exec: ./src/*.cpp
	clang++ ./src/*.cpp -o exec -I raylib/src -L raylib/src -lraylib -lpthread

# To build for web run this before inside raylib/src:
# emcc -c rcore.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
# emcc -c rshapes.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
# emcc -c rtextures.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
# emcc -c rtext.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
# emcc -c rmodels.c -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2
# emcc -c utils.c -Os -Wall -DPLATFORM_WEB
# emcc -c raudio.c -Os -Wall -DPLATFORM_WEB
# emar rcs libraylib.a rcore.o rshapes.o rtextures.o rtext.o rmodels.o utils.o raudio.o

montecarlo.html: ./src/*.cpp ./src/shell.html
	emcc ./src/*.cpp -o montecarlo.html ./raylib/src/libraylib.a -I./raylib/src -L./raylib/src -s USE_GLFW=3 -s ASYNCIFY \
	--shell-file ./src/shell.html