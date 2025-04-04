from django.shortcuts import render, redirect
from .models import Usuario, Produto, Funcionario, Venda
import random

# renderiza a página com html básico
def base(request):
    return render(request, 'usuarios/base.html')

# renderiza a página inicial
def home(request):
    return render(request, 'usuarios/home.html')



# renderiza a página escolher_cadastro
def escolher_cadastro(request):
    return render(request, 'usuarios/cadastros/escolher_cadastro.html')

# renderiza a página de cadastrar_funcionario
def cadastrar_funcionario(request):
    return render(request, 'usuarios/cadastros/cadastrar_funcionario.html')

# renderiza a página de cadastrar_usuario
def cadastrar_usuario(request):
    return render(request, 'usuarios/cadastros/cadastrar_usuario.html')



# renderiza a página que mostra a tabela usuários
def mostrar_usuarios(request):
    usuarios = {
        'usuarios': Usuario.objects.all()
    }
    return render(request, 'usuarios/mostrar_algo/usuarios.html', usuarios)

# renderiza a página que mostra a tabela produtos
def mostrar_produtos(request):
    produtos = {
        'produtos': Produto.objects.all()
    }
    return render(request, 'usuarios/cadastros/produtos.html', produtos)

# renderiza a página que mostra a tabela vendas
def mostrar_vendas(request):
    vendas = {
        'vendas': Venda.objects.all()
    }
    return render(request, 'usuarios/mostrar_algo/vendas.html', vendas)





# renderiza a página onde coloca o cpf do cliente e seus dados são pegos para a tebela vendas
def confirmar_usuario(request):
    usuarios = {
        'usuarios': Usuario.objects.all()
    }
    return render(request, 'usuarios/mostrar_algo/carrinho.html', usuarios)


# renderiza a página que mostra os dados que vão montar a nova linha da tabela de vendas
def carrinho(request):

    cpf_nao_encontrado = False

    if request.method == 'POST':
        cpf_usuario = request.POST.get('cpf_usuario')
        usuario = Usuario.objects.filter(cpf=cpf_usuario).first()

        if usuario:
            nome_usuario = usuario.nome
            endereco_usuario = usuario.endereco
            cpf_usuario = usuario.cpf

            funcionarios = Funcionario.objects.all()
            funcionario_aleatorio = random.choice(funcionarios)
            cpf_aleatorio = funcionario_aleatorio.cpf
            nome_funcionario = funcionario_aleatorio.nome

            produtos = Produto.objects.all()
            produto_aleatorio = random.choice(produtos)
            nome_produto_aleatorio = produto_aleatorio.nome
            valor_compra = produto_aleatorio.preco

            return render(request, 'usuarios/mostrar_algo/pagina_venda.html', 
                          {'cpf_aleatorio': cpf_aleatorio, 'nome_produto_aleatorio': nome_produto_aleatorio, 
                           'valor_compra': valor_compra, 'nome_usuario': nome_usuario,
                            'endereco_usuario': endereco_usuario, 'cpf_usuario': cpf_usuario,
                            'nome_funcionario': nome_funcionario}
                            )
        else:
            cpf_nao_encontrado = True
    
    return render(request, 'usuarios/mostrar_algo/carrinho.html', {'cpf_nao_encontrado': cpf_nao_encontrado})
        

# botão para pegar os dados da página pagina_venda.html para montar a tabela vendas
def vendas(request):
    if request.method == 'POST':
        nova_venda = Venda()
        nova_venda.preco_venda = request.POST.get('valor_compra')
        nova_venda.nome_cliente = request.POST.get('nome_usuario')
        nova_venda.nome_lojista = request.POST.get('nome_funcionario')
        nova_venda.endereco_entrega_cliente = request.POST.get('endereco_usuario')

        cpf_usuario = request.POST.get('cpf_usuario')
        relacionar_tabela_usuario = Usuario.objects.filter(cpf=cpf_usuario).first()
        nova_venda.cpf_cliente = relacionar_tabela_usuario

        cpf_funcionario_realizou_a_venda = request.POST.get('funcionario_venda')
        relacionar_tabela_funcionario = Funcionario.objects.filter(cpf=cpf_funcionario_realizou_a_venda).first()
        nova_venda.cpf_funcionario_realizou_a_venda = relacionar_tabela_funcionario

        produto_comprado = request.POST.get('nome_produto_aleatorio')
        relacionar_tabela_produto = Produto.objects.filter(nome=produto_comprado).first()
        nova_venda.produtos_comprados = relacionar_tabela_produto

        nova_venda.save()


    vendas = {
        'vendas': Venda.objects.all()
    }
    return render(request, 'usuarios/mostrar_algo/vendas.html', vendas)




# botão para efetuar o cadastro de usuários
def usuarios(request):
    if request.method == 'POST':
        novo_usuario = Usuario()
        novo_usuario.nome = request.POST.get('nome')
        novo_usuario.idade = int(request.POST.get('idade')) if request.POST.get('idade') else None
        novo_usuario.cpf = request.POST.get('cpf')
        novo_usuario.endereco = request.POST.get('endereco')
        novo_usuario.save()

    usuarios = {
        'usuarios': Usuario.objects.all()
    }
    return render(request, 'usuarios/mostrar_algo/usuarios.html', usuarios)



# botão para efetuar o cadastro de produtos
def produtos(request):

    funcionario_nao_encontrado = False

    if request.method == 'POST':
        cpf_funcionario = request.POST.get('cpf_funcionario')
        funcionarios = Funcionario.objects.filter(cpf=cpf_funcionario)

        if funcionarios.exists():
            novo_produto = Produto()
            novo_produto.nome = request.POST.get('nome')
            novo_produto.descricao = request.POST.get('descricao')
            novo_produto.preco = float(request.POST.get('preco')) if request.POST.get('preco') else None
            novo_produto.save()
        else:
            funcionario_nao_encontrado = True

    produtos = {
        'produtos': Produto.objects.all(), 'funcionario_nao_encontrado':funcionario_nao_encontrado
    }
    return render(request, 'usuarios/cadastros/produtos.html', produtos)




# botão para efetuar o cadastro de funcionários
def funcionarios(request):
    if request.method == 'POST':
        novo_funcionario = Funcionario()
        novo_funcionario.nome = request.POST.get('nome')
        novo_funcionario.cpf = request.POST.get('cpf')
        novo_funcionario.endereco = request.POST.get('endereco')
        novo_funcionario.save()

    funcionarios = {
        'funcionarios': Funcionario.objects.all()
    }
    return render(request, 'usuarios/mostrar_algo/funcionarios.html', funcionarios)




# renderiza a página com todas as tabelas com as opções de alterar e exluir
def excluir_alterar(request):
    tabelas = {
        'usuarios': Usuario.objects.all(),
        'funcionarios': Funcionario.objects.all(),
        'produtos': Produto.objects.all(),
        'vendas': Venda.objects.all()
    }
    return render(request, 'usuarios/editar_excluir/excluir_alterar.html', tabelas)




# editar. atualizar e exluir produto
def editar_produto(request, id_produto):
    produto = Produto.objects.get(id_produto=id_produto)
    return render(request, 'usuarios/editar_excluir/editar_produto.html', {'produto': produto})

def atualizar_produto(request, id_produto):
    novo_produto = Produto.objects.get(id_produto=id_produto)
    novo_produto.nome = request.POST.get('nome')
    novo_produto.descricao = request.POST.get('descricao')
    novo_produto.preco = float(request.POST.get('preco')) if request.POST.get('preco') else None
    novo_produto.save()

    return redirect(excluir_alterar)

def excluir_produto(request, id_produto):
    produto = Produto.objects.get(id_produto=id_produto)
    produto.delete()

    return redirect(excluir_alterar)




# editar. atualizar e exluir funcionário
def editar_funcionario(request, id_funcionario):
    funcionario = Funcionario.objects.get(id_funcionario=id_funcionario)
    return render(request, 'usuarios/editar_excluir/editar_funcionario.html', {'funcionario': funcionario})

def atualizar_funcionario(request, id_funcionario):
    novo_funcionario = Funcionario.objects.get(id_funcionario=id_funcionario)
    novo_funcionario.nome = request.POST.get('nome')
    novo_funcionario.endereco = request.POST.get('endereco')
    novo_funcionario.cpf = request.POST.get('cpf')
    novo_funcionario.save()

    return redirect(excluir_alterar)

def excluir_funcionario(request, id_funcionario):
    funcionario = Funcionario.objects.get(id_funcionario=id_funcionario)
    funcionario.delete()

    return redirect(excluir_alterar)




# editar. atualizar e exluir usuário
def editar_usuario(request, id_usuario):
    usuario = Usuario.objects.get(id_usuario=id_usuario)
    return render(request, 'usuarios/editar_excluir/editar_usuario.html', {'usuario': usuario})

def atualizar_usuario(request, id_usuario):
    novo_usuario = Usuario.objects.get(id_usuario=id_usuario)
    novo_usuario.nome = request.POST.get('nome')
    novo_usuario.endereco = request.POST.get('endereco')
    novo_usuario.cpf = request.POST.get('cpf')
    novo_usuario.idade = request.POST.get('idade')
    novo_usuario.save()

    return redirect(excluir_alterar)

def excluir_usuario(request, id_usuario):
    usuario = Usuario.objects.get(id_usuario=id_usuario)
    usuario.delete()

    return redirect(excluir_alterar)
