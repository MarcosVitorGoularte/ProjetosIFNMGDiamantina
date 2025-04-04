# Generated by Django 4.2.7 on 2023-11-22 11:56

import django.core.validators
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('app_cad_usuarios', '0008_alter_usuario_idade'),
    ]

    operations = [
        migrations.AlterField(
            model_name='usuario',
            name='idade',
            field=models.PositiveIntegerField(blank=True, default=None, null=True, validators=[django.core.validators.MaxValueValidator(150), django.core.validators.MinValueValidator(18)]),
        ),
    ]
