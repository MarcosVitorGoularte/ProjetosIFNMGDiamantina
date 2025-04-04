# Generated by Django 4.2.5 on 2023-11-27 20:46

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    dependencies = [
        ('app_cad_usuarios', '0015_remove_venda_endereco_entrega_cliente_and_more'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='venda',
            name='produtos_comprados',
        ),
        migrations.AddField(
            model_name='venda',
            name='produtos_comprados',
            field=models.ForeignKey(null=True, on_delete=django.db.models.deletion.CASCADE, to='app_cad_usuarios.produto'),
        ),
    ]
