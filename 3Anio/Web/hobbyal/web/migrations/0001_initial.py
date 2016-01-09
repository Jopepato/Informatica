# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Board',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('comment', models.TextField()),
            ],
            options={
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Event',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('name', models.CharField(max_length=75)),
                ('date', models.DateField()),
            ],
            options={
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='Hobby',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('name', models.CharField(max_length=75)),
                ('description', models.TextField(blank=True)),
                ('image', models.ImageField(upload_to=b'', blank=True)),
            ],
            options={
            },
            bases=(models.Model,),
        ),
        migrations.CreateModel(
            name='User',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('email', models.EmailField(max_length=75)),
                ('password', models.TextField(max_length=15)),
                ('name', models.CharField(max_length=100)),
                ('lastname', models.CharField(max_length=100)),
                ('description', models.TextField(blank=True)),
                ('birthday', models.DateField()),
                ('gender', models.CharField(max_length=1, choices=[(b'Hombre', b'Hombre'), (b'Mujer', b'Mujer'), (b'Otro', b'Otro')])),
                ('photo', models.ImageField(upload_to=b'', blank=True)),
                ('board', models.ForeignKey(to='web.Board')),
                ('events', models.ManyToManyField(to='web.Event')),
                ('friends', models.ManyToManyField(related_name='friends_rel_+', to='web.User')),
                ('hobbies', models.ManyToManyField(to='web.Hobby')),
            ],
            options={
            },
            bases=(models.Model,),
        ),
        migrations.AddField(
            model_name='event',
            name='hobby',
            field=models.ForeignKey(to='web.Hobby'),
            preserve_default=True,
        ),
    ]
