CPPFLAGS= -c -g -ansi -Wall
OBJECTS= main.o graph_matrix.o entrada_salida.o funciones.o
INCLUDES= edge.hpp vertex.hpp graph_matrix.hpp entrada_salida.hpp funciones.hpp

main: $(INCLUDES) $(OBJECTS)
	g++ $(OBJECTS) -g -o main

main.o: main.cpp $(INCLUDES)
	g++ $(CPPFLAGS) main.cpp

entrada_salida.o: entrada_salida.cpp $(INCLUDES)
	g++ $(CPPFLAGS) entrada_salida.cpp

graph_matrix.o: graph_matrix.cpp $(INCLUDES)
	g++ $(CPPFLAGS) graph_matrix.cpp

funciones.o: funciones.cpp $(INCLUDES)
	g++ $(CPPFLAGS) funciones.cpp

clean:
	rm *.o