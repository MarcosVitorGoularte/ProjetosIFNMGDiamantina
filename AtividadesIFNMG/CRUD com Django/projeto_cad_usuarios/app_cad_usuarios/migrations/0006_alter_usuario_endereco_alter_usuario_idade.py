# Generated by Django 4.2.7 on 2023-11-22 10:17

import app_cad_usuarios.models
import django.core.validators
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('app_cad_usuarios', '0005_alter_usuario_idade'),
    ]

    operations = [
        migrations.AlterField(
            model_name='usuario',
            name='endereco',
            field=models.TextField(blank=True, max_length=255, null=True),
        ),
        migrations.AlterField(
            model_name='usuario',
            name='idade',
            field=models.PositiveIntegerField(blank=True, default=app_cad_usuarios.models.nao_informado, null=True, validators=[django.core.validators.MaxValueValidator(150), django.core.validators.MinValueValidator(18)]),
        ),
    ]
