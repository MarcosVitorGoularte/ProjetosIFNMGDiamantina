# -*- coding: utf-8 -*-
"""plotgraficos.ipynb

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/1Hqr-hC19nP-shKl7o2brUWDjiTHzq0Q0
"""

import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('/content/precos-semestrais-ca-2022-01.csv', delimiter=';')
df['Valor de Venda'] = df['Valor de Venda'].str.replace(',','.').astype(float)
df

"""1) As médias dos preços de gasolinas de todos os estados brasileiros;"""

a = df[df['Produto'] == 'GASOLINA']
x = a.groupby('Estado - Sigla')['Valor de Venda'].mean()
plt.figure(figsize=(20, 8))
plt.xlabel('Estados')
plt.ylabel('Média de Preços - Gasolina')
plt.plot(x, marker = 'o')

"""2) As 10 maiores médias dos preços de Gasolina dos municípios de Minas Gerais;"""

a = df[(df['Estado - Sigla']=='MG') & (df['Produto'] == 'GASOLINA')]
b = a.groupby('Municipio')['Valor de Venda'].mean().sort_values(ascending = False).head(10)
plt.figure(figsize=(20, 8))
plt.xlabel('Municipios')
plt.ylabel('Média de Preços - Gasolina')
plt.plot(b, marker = 'o')

"""3) As 10 menores médias dos preços de Etanol dos municípios de Minas Gerais."""

a = df[(df['Estado - Sigla']=='MG') & (df['Produto'] == 'ETANOL')]
b = a.groupby('Municipio')['Valor de Venda'].mean().sort_values(ascending = True).head(10)
plt.figure(figsize=(20, 8))
plt.xlabel('Municipios')
plt.ylabel('Média de Preços - Etanol')
plt.plot(b, marker = 'o')