# Generated by Django 4.2.5 on 2023-11-27 02:37

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('app_cad_usuarios', '0010_alter_funcionario_endereco_venda'),
    ]

    operations = [
        migrations.AlterField(
            model_name='venda',
            name='preco_venda',
            field=models.DecimalField(decimal_places=2, default=0.0, max_digits=10),
        ),
    ]
