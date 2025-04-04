from django.urls import path
from app_cad_usuarios import views

urlpatterns = [
    # página inicial
    path('',views.home, name='home'),

    # links de listagem = adicionar dados e mostrar tabela
    # links de mostrar = mostrar tabela
    path('usuarios/',views.usuarios, name='listagem_usuarios'),
    path('mostrar_usuarios/',views.mostrar_usuarios, name='mostrar_usuarios'),

    # links de listagem = adicionar dados e mostrar tabela
    # links de mostrar = mostrar tabela
    path('produtos/',views.produtos, name='listagem_produtos'),
    path('mostrar_produtos/',views.mostrar_produtos, name='mostrar_produtos'),

    # links de listagem = adicionar dados e mostrar tabela
    # links de mostrar = mostrar tabela
    path('funcionarios/',views.funcionarios, name='listagem_funcionarios'),

    # links de listagem = adicionar dados e mostrar tabela
    # links de mostrar = mostrar tabela
    path('vendas/',views.vendas, name='listagem_vendas'),
    path('mostrar_vendas/',views.mostrar_vendas, name='mostrar_vendas'),

    # escolher_cadastro
    path('escolher_cadastro/', views.escolher_cadastro, name='escolher_cadastro'),
    path('cadastrar_usuario/', views.cadastrar_usuario, name='cadastrar_usuario'),
    path('cadastrar_funcionario/', views.cadastrar_funcionario, name='cadastrar_funcionario'),

    # altera_excluir - mostra a página com as tabelas e os botões de alterar e excluir
    path('excluir_alterar/', views.excluir_alterar, name='excluir_alterar'),

    # alterar_excluir funcionário
    path('editar_funcionario/<int:id_funcionario>/', views.editar_funcionario, name='editar_funcionario'),
    path('excluir_funcionario/<int:id_funcionario>/', views.excluir_funcionario, name='excluir_funcionario'),
    path('atualizar_funcionario/<int:id_funcionario>/', views.atualizar_funcionario, name='atualizar_funcionario'),

    # alterar_excluir usuário
    path('editar_usuario/<int:id_usuario>/', views.editar_usuario, name='editar_usuario'),
    path('excluir_usuario/<int:id_usuario>/', views.excluir_usuario, name='excluir_usuario'),
    path('atualizar_usuario/<int:id_usuario>/', views.atualizar_usuario, name='atualizar_usuario'),

    # alterar_excluir produto
    path('editar_produto/<int:id_produto>/', views.editar_produto, name='editar_produto'),
    path('excluir_produto/<int:id_produto>/', views.excluir_produto, name='excluir_produto'),
    path('atualizar_produto/<int:id_produto>/', views.atualizar_produto, name='atualizar_produto'),

    # mostrar formulário onde coloca o cpf do usuário e seus dados correspondentes são mostrados
    path('confirmar_usuario/', views.confirmar_usuario, name='confirmar_usuario'),

    # carrinho.html - verifica o cpf do usuário e pega os dados correspondentes  
    path('carrinho/', views.carrinho, name='carrinho'),
]
