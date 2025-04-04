# -*- coding: utf-8 -*-
"""Cópia de PROVA.ipynb

Automatically generated by Colab.

Original file is located at
    https://colab.research.google.com/drive/12oQrB0STJ00sMm8cS0zu93KguIoVkVrA

https://www.gov.br/inep/pt-br/acesso-a-informacao/dados-abertos/microdados/enem-por-escola

Link do Dataset
"""

import pandas as pd
import matplotlib.pyplot as plt
df = pd.read_excel('/content/MICRODADOS_ENEM_ESCOLA.xltx')
df

x = df.groupby('NU_ANO')['CO_ESCOLA_EDUCACENSO'].count()
plt.figure(figsize=(20, 8))
plt.xlabel('Anos')
plt.ylabel('Quantidade de escolas escritas')
plt.plot(x, marker = 'o')

df.groupby('NU_ANO')['NU_ANO'].count()