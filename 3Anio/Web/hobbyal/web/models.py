from django.db import models
import datetime
# Create your models here.

class Hobby(models.Model):
	name = models.CharField(max_length=75, blank=False)
	description = models.TextField(blank=True)
	image = models.ImageField(blank=True)


class Event(models.Model):
	name = models.CharField(max_length=75, blank=False)
	date = models.DateField(blank=False)
	hobby = models.ForeignKey('Hobby')

class User(models.Model):
	HOMBRE = 'Hombre'
	MUJER = 'Mujer'
	OTRO = 'Otro'
	CHOICES = (
		(HOMBRE, 'Hombre'),
		(MUJER, 'Mujer'),
		(OTRO, 'Otro')
		)
	email = models.EmailField(max_length=75, blank=False)
	password = models.TextField(max_length=15, blank=False)
	name = models.CharField(max_length=100, blank=False)
	lastname = models.CharField(max_length=100, blank=False)
	description = models.TextField(blank=True)
	birthday = models.DateField(blank=False)
	gender = models.CharField(choices=CHOICES, blank=False, max_length=1)
	friends = models.ManyToManyField('self')
	hobbies = models.ManyToManyField('Hobby', null=False)
	events = models.ManyToManyField('Event')
	photo = models.ImageField(blank=True)


class Comment(models.Model):
	text = models.TextField(max_length=140, blank=False)
	date = models.DateTimeField(blank=False, auto_now=True)
	receiver = models.ForeignKey('User', blank = False, related_name="receiver") #Usuario que recibe el comentario
	sender = models.ForeignKey('User', blank = False, related_name="sender") #Usuario que manda el comentario
