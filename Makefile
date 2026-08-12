
all: main.cpp render.o indexBuffer.o vertexBuffer.o
	g++ main.cpp render.o indexBuffer.o vertexBuffer.o -o my_app -lglfw -lGL -lm -lGLEW

render.o: src/render.cpp
	g++ -c src/render.cpp -o render.o

indexBuffer.o: src/indexBuffer.cpp 
	g++ -c src/indexBuffer.cpp -o indexBuffer.o

vertexBuffer.o: src/vertexBuffer.cpp
	g++ -c src/vertexBuffer.cpp -o vertexBuffer.o
