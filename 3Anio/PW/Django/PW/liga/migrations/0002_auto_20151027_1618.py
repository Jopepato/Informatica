# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('liga', '0001_initial'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='player',
            name='equipo',
        ),
        migrations.AddField(
            model_name='player',
            name='old_teams',
            field=models.ManyToManyField(related_name=b'old_teams', null=True, to='liga.Team', blank=True),
            preserve_default=True,
        ),
        migrations.AddField(
            model_name='player',
            name='team',
            field=models.ForeignKey(blank=True, to='liga.Team', null=True),
            preserve_default=True,
        ),
    ]
