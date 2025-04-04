from django.db import models
from django.core.validators import MaxValueValidator, MinValueValidator, MinLengthValidator

def nao_informado():
    return 'texto'

class Usuario(models.Model):
    id_usuario = models.AutoField(primary_key=True)
    cpf = models.CharField(max_length=11, blank=False, null=True, default=None, unique=True, validators=[MinLengthValidator(11)])
    nome = models.TextField(max_length=255, blank=False, null=True)
    idade = models.PositiveIntegerField(null=True, blank=True, default=None, validators=[MaxValueValidator(150), MinValueValidator(18)])
    endereco = models.TextField(max_length=255, blank=True, null=True)

class Produto(models.Model):
    id_produto = models.AutoField(primary_key=True)
    nome = models.TextField(max_length=255, blank=False, null=False)
    descricao = models.TextField(max_length=255, blank=False, null=True, default=None)
    preco = models.FloatField(validators=[MinValueValidator(0.0)])

class Funcionario(models.Model):
    id_funcionario = models.AutoField(primary_key=True)
    nome = models.TextField(max_length=255, blank=False, null=False)
    cpf = models.CharField(max_length=11, blank=False, null=True, default=None, unique=True, validators=[MinLengthValidator(11)])
    endereco = models.TextField(max_length=255, blank=True, null=True)

class Venda(models.Model):
    numero_da_venda_realizada = models.AutoField(primary_key=True)
    preco_venda = models.DecimalField(max_digits=10, decimal_places=2, default=0.0)
    endereco_entrega_cliente = models.TextField(max_length=255, blank=True, null=True)
    nome_cliente = models.TextField(max_length=255, blank=True, null=True)
    nome_lojista = models.TextField(max_length=255, blank=True, null=True)
    cpf_funcionario_realizou_a_venda = models.ForeignKey(Funcionario, on_delete=models.CASCADE, null=True)
    cpf_cliente = models.ForeignKey(Usuario, on_delete=models.CASCADE, null=True)
    produtos_comprados = models.ForeignKey(Produto, on_delete=models.CASCADE, null=True)
