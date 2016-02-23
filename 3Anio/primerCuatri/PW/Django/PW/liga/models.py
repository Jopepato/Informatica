from django.db import models
from django.contrib import admin

# Create your models here.

class Team(models.Model):
	name = models.CharField(max_length=50, null=False)
	city = models.CharField(max_length=50)
	birth_date = models.DateField(auto_now=False, null=True)
	trainer_name = models.CharField(max_length=100, null=False)
	description = models.CharField(max_length=300)
	def __unicode__(self):
		return self.name

class Player(models.Model):
	name = models.CharField(max_length=50, null=False)
	age = models.IntegerField(null=False)
	birth = models.DateField(auto_now=False)
	birth_place = models.CharField(max_length=100)
	team = models.ForeignKey(Team, blank=True, null=False)# 0 a 1
	position = models.CharField(max_length=100, null=False)
	description = models.CharField(max_length=200)
	old_teams = models.ManyToManyField(Team, blank=True, related_name='old_teams', null=True) # 0 a n
	def __unicode__(self):
		return self.name

admin.site.register(Team)
admin.site.register(Player)
