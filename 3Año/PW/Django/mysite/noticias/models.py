from django.db import models

# Create your models here.

class Autor(models.Model):
	name = models.CharField(max_length=100)
	age = models.IntegerField()


class Seccion(models.Model):
	name = models.CharField(max_length=100)
	

class Noticia(models.Model):
	name = models.CharField(max_length=100)
	subtitle = models.CharField(max_lenght=100)
	autor = models.ForeignKey(Autor)
	seccion = models.ForeignKey(Seccion)

