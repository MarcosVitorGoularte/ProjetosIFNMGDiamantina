# Generated by Django 4.2.7 on 2023-11-21 13:17

import django.core.validators
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('app_cad_usuarios', '0002_alter_funcionario_cpf_alter_funcionario_endereco_and_more'),
    ]

    operations = [
        migrations.AlterField(
            model_name='usuario',
            name='idade',
            field=models.PositiveIntegerField(default='Não informado', validators=[django.core.validators.MaxValueValidator(150), django.core.validators.MinValueValidator(18)]),
        ),
    ]
