import numpy as np


class Tabuleiro:
    def __init__(self):
        self.tabuleiro = np.zeros((3, 3), dtype=int) #Cria uma matriz 3x3 compostas por zeros


    def imprimir(self):
        sinais = np.array(["", "X", "O"]) #Cria um array com os sinas de 'X', 'O' e tabuleiro vazio ''. Onde 0 = '', 1 = 'X' e -1 = 'O'
        tabuleiro = sinais[self.tabuleiro] #Indexamos sinais a tabuleiro. Ou seja, os 0 se tornarão ''.
        print(tabuleiro)




class Jogador:
    def __init__(self, sinal):
        self.sinal = sinal #Sinal do jogador


    def jogar(self, tabuleiro): #Tabuleiro da classe Tabuleiro
        while True: #Loop para marcar um dos sinais
            linha = int(input(f"Digite a linha (0, 1 ou 2) para marcar {self.sinal}: "))
            coluna = int(input(f"Digite a coluna (0, 1 ou 2) para marcar {self.sinal}: "))


            if tabuleiro.tabuleiro[linha][coluna] == 0: #Verifica se a casa está vazia
                if self.sinal == "X": #Se o jogador é 'X':
                    tabuleiro.tabuleiro[linha][coluna] = 1 #Mude no tabuleiro o valor para 1 (que representa 'X')
                else: #Se o jogador é 'O':
                    tabuleiro.tabuleiro[linha][coluna] = -1 #Mude no tabuleiro o valor para -1 (que representa 'O')
                break
            else:
                print("Essa célula já está ocupada. Tente novamente.")


class Jogo:
    def __init__(self):
        self.tabuleiro = Tabuleiro() #Classe Tabuleiro é instanciada
        self.jogador1 = Jogador("X") #Classe Jogador é instanciada
        self.jogador2 = Jogador("O") #Classe Jogador é instanciada
        self.jogador_atual = self.jogador1 #O jogador1 é o primeiro


    def jogar(self):
        while True:
            self.tabuleiro.imprimir()
            self.jogador_atual.jogar(self.tabuleiro)


            if self.verificar_vitoria():
                print(f"O jogador {self.jogador_atual.sinal} ganhou!")
                break
            elif self.verificar_empate():
                print("Empate!")
                break
            else:
                if self.jogador_atual == self.jogador1: #Verifica qual jogador fez a última jogada e passa para o outro
                    self.jogador_atual = self.jogador2
                else:
                    self.jogador_atual = self.jogador1


    def verificar_vitoria(self):
        for i in range(3): #O np.abs verifica o valor absoluto da soma, desconsiderando o sinal. O i passa pelas linhas/colunas 0, 1 e 2
            if np.abs(self.tabuleiro.tabuleiro[i, :].sum()) == 3: #Verifica se algum jogador ganhou nas 3 linhas
                return True
            if np.abs(self.tabuleiro.tabuleiro[:, i].sum()) == 3: #Verifica se algum jogador ganhou nas 3 colunas
                return True
        if np.abs(self.tabuleiro.tabuleiro.diagonal().sum()) == 3: #Verifica se algum jogador ganhou na diagonal
            return True
        if np.abs(np.fliplr(self.tabuleiro.tabuleiro).diagonal().sum()) == 3: #Inverte a diagonal e verifica se algum jogador ganhou
            return True
        return False


    def verificar_empate(self):
        if np.count_nonzero(self.tabuleiro.tabuleiro) == 9: #Se existerem 9 números diferentes de 0, é empate
            return True
        return False






jogo = Jogo()
jogo.jogar()
