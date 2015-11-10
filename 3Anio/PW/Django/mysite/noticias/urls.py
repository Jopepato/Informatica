from django.conf.urls import patterns, include, url

from noticias import views

urlpatterns = patterns('',

		url(r'^$', views.index, name='index'),
		url(r'noticias^$', include('noticias.urls')),
)
