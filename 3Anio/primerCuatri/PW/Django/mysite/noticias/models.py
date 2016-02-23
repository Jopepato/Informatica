from django.db import models
from django.contrib import admin
# Create your models here.

class Autor(models.Model):
	name = models.CharField(max_length=100)
	age = models.IntegerField()

	def __unicode__(self):
		return self.name


class Seccion(models.Model):
	name = models.CharField(max_length=100)

	def __unicode__(self):
		return self.name

class Noticia(models.Model):
	name = models.CharField(max_length=100)
	subtitle = models.CharField(max_length=100)
	autor = models.ForeignKey(Autor)
	seccion = models.ForeignKey(Seccion)

	def __unicode__(self):
		return self.name


admin.site.register(Autor)
admin.site.register(Seccion)
admin.site.register(Noticia)
