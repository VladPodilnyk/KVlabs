# -*- coding: utf-8 -*-
# Generated by Django 1.10.2 on 2016-12-27 02:43
from __future__ import unicode_literals

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('app', '0003_orderlog'),
    ]

    operations = [
        migrations.RenameField(
            model_name='orderlog',
            old_name='date_time',
            new_name='insert_time',
        ),
        migrations.RenameField(
            model_name='orderlog',
            old_name='order',
            new_name='num_order',
        ),
    ]
