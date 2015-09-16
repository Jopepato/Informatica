CPPFLAGS= -c -g -ansi -Wall
OBJECTS= main.o clave.o generarpersona.o persona.o
INCLUDES= clave.hpp edi_BinaryTree.hpp edi_LinkedBinaryTreeNode.hpp edi_LinkedOrderedBinaryTree.hpp edi_OrderedBinaryTree.hpp edi_exports.hpp generarpersona.hpp persona.hpp


main: $(OBJECTS) $(INCLUDES)
	g++ $(OBJECTS) -o main

main.o: main.cpp $(INCLUDES)
	g++ $(CPPFLAGS) main.cpp

persona.o: persona.cpp $(INCLUDES)
	g++ $(CPPFLAGS) persona.cpp

generarpersona.o: generarpersona.cpp $(INCLUDES)
	g++ $(CPPFLAGS) generarpersona.cpp

clave.o: clave.cpp $(INCLUDES)
	g++ $(CPPFLAGS) clave.cpp

clean: 
	rm *.o main