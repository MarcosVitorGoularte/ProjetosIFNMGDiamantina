# Generated by Django 4.2.5 on 2023-11-27 21:20

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('app_cad_usuarios', '0017_venda_cpf_cliente_and_more'),
    ]

    operations = [
        migrations.AddField(
            model_name='venda',
            name='nome_cliente',
            field=models.TextField(blank=True, max_length=255, null=True),
        ),
        migrations.AddField(
            model_name='venda',
            name='nome_lojista',
            field=models.TextField(blank=True, max_length=255, null=True),
        ),
    ]
