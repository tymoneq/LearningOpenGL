
all: main.cpp render.o indexBuffer.o vertexBuffer.o vertexArray.o shader.o stb_imagine.o textures.o
	g++ main.cpp render.o indexBuffer.o vertexBuffer.o vertexArray.o shader.o stb_imagine.o textures.o -o my_app -lglfw -lGL -lm -lGLEW

render.o: src/render.cpp
	g++ -c src/render.cpp -o render.o

indexBuffer.o: src/indexBuffer.cpp 
	g++ -c src/indexBuffer.cpp -o indexBuffer.o

vertexBuffer.o: src/vertexBuffer.cpp
	g++ -c src/vertexBuffer.cpp -o vertexBuffer.o

vertexArray.o: src/vertexArray.cpp
	g++ -c src/vertexArray.cpp -o vertexArray.o

shader.o: src/shader.cpp
	g++ -c src/shader.cpp -o shader.o

textures.o: src/textures.cpp
	g++ -c src/textures.cpp -o textures.o

stb_imagine.o: src/vendor/stb_image/stb_image.cpp
	g++ -c src/vendor/stb_image/stb_image.cpp -o stb_imagine.o

clean:
	rm -f *.o my_app