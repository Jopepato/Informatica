class Publicacion:
	"""Esto es una clase con las cosas de una publicacion"""
	nPublicaciones=0
	def __init__(self, nombre, autor):
		self.a = autor
		self.n = nombre
		Publicacion.nPublicaciones +=1
	def autor(self):
		return self.a
	def nombre(self):
		return self.n
	def publicaciones(self):
		return Publicacion.nPublicaciones

class Libro(Publicacion):
	"""Esto es una clase que contiene las cosas de los libros"""
	nLibros=0
	def __init__(self, nombre, autor):
		self.a = autor
		self.n = nombre
		self.cod = Publicacion.nPublicaciones
		Publicacion.nPublicaciones +=1
		Libro.nLibros +=1
	def libros(self):
		return Libro.nLibros
	def codigo(self):
		return self.cod
	


class Comic(Publicacion):
	"""Esto es una clase que contiene las cosas de los comics"""
	nComics=0
	def __init__(self, nombre, autor):
		self.n = nombre
		self.a = autor
		self.cod = Publicacion.nPublicaciones
		Publicacion.nPublicaciones +=1
		Comic.nComics +=1
	def comics(self):
		return Comic.nComics
	def codigo(self):
		return self.cod


l = Libro("Las puertas de piedra", "Patrick")
c = Comic("Avengers", "Marvel")

print "Nombre del libro " , l.nombre()
print "Autor del libro ", l.autor()
print "Nombre del comic ", c.nombre()
print "Nombre del autor del comic ", c.autor()
print "Hay ", l.libros()
print "Codigo ", c.codigo()
