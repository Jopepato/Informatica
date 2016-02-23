# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('web', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='comment',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('text', models.TextField(max_length=140)),
                ('date', models.DateTimeField(auto_now=True)),
                ('receiver', models.ForeignKey(related_name=b'receiver', to='web.User')),
                ('sender', models.ForeignKey(related_name=b'sender', to='web.User')),
            ],
            options={
            },
            bases=(models.Model,),
        ),
        migrations.RemoveField(
            model_name='user',
            name='board',
        ),
        migrations.DeleteModel(
            name='Board',
        ),
    ]
