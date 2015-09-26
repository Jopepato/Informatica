import random
import sys
def devPalabras(fichero):
	f= open(fichero, "r")
	lineas = []
	for linea in f:
		lineas.append(linea)
	return lineas

def seleccionaElemento(lista):
	return random.choice(lista)

def introLetra():
	a= raw_input("Introduce una unica letra: ")
	while len(a)!= 1 or a.isdigit():
		a= raw_input("Introduce una unica letra: ")
	return a

def buscaLetra(a, cadena):
	j=0
	lista= []
	for i in cadena:
		if i==a:
			lista.append(j)
		j= j+1
	return lista

fichero = raw_input("Introduce el nombre del fichero: ")

palabras = devPalabras(fichero)
palabra = seleccionaElemento(palabras)
pista =[]
for i in palabra:
	pista.append('-')
pista.pop()

while 1:
	letra=introLetra()
	listaLetra=buscaLetra(letra,palabra)
	for i in listaLetra:
		pista[i]=letra
	print pista
	if "-" not in pista: break
