# Generated by Django 4.2.5 on 2023-11-27 20:25

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('app_cad_usuarios', '0013_endereco_remove_venda_endereco_entrega_cliente_and_more'),
    ]

    operations = [
        migrations.AlterField(
            model_name='funcionario',
            name='endereco',
            field=models.TextField(blank=True, max_length=255, null=True),
        ),
        migrations.AlterField(
            model_name='usuario',
            name='endereco',
            field=models.TextField(blank=True, max_length=255, null=True),
        ),
        migrations.DeleteModel(
            name='Endereco',
        ),
    ]
