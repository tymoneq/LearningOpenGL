
all: main.cpp render.o indexBuffer.o vertexBuffer.o vertexArray.o
	g++ main.cpp render.o indexBuffer.o vertexBuffer.o vertexArray.o -o my_app -lglfw -lGL -lm -lGLEW

render.o: src/render.cpp
	g++ -c src/render.cpp -o render.o

indexBuffer.o: src/indexBuffer.cpp 
	g++ -c src/indexBuffer.cpp -o indexBuffer.o

vertexBuffer.o: src/vertexBuffer.cpp
	g++ -c src/vertexBuffer.cpp -o vertexBuffer.o

vertexArray.o: src/vertexArray.cpp
	g++ -c src/vertexArray.cpp -o vertexArray.o


clean:
	rm -f *.o my_app