from django.contrib import admin
from web.models import User, Hobby, Event, Comment
# Register your models here.


admin.site.register(User)
admin.site.register(Hobby)
admin.site.register(Event)
admin.site.register(Comment)