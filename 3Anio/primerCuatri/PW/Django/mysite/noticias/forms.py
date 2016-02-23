from django import forms
from .models import Autor, Seccion, Noticia

    class NoticiaForm(forms.ModelForm):

        class Meta:
            model = Noticia
            fields = ('name', 'subtitle',)
