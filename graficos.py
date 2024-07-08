import matplotlib.pyplot as plt  # Para plotear
import pandas as pd  # Para leer archivo .csv
import numpy as np

# Generar tablas en latex
exper = pd.read_csv('experimentacion.csv')
latex_exper = exper.to_latex(index=False, escape=False)
#print(latex_exper)

# Tamaño del input

n = exper['n'].values 
m = exper['m'].values

t_rec = exper['Rec[us]'].values
t_mem = exper['Mem[us]'].values
t_dp = exper['DP[us]'].values

e_rec = exper['E.Rec[bytes]'].values
e_mem = exper['E.Mem[bytes]'].values
e_dp = exper['E.DP[bytes]'].values

# Pares ordenados
labels = []
for n_i, m_i in zip(n, m):
    labels.append(f'({n_i},{m_i})')
x = np.arange(len(labels))  

# Gráfico del tiempo promedio
fig = plt.figure()
ax = fig.add_subplot(111)
width = 0.3
#bar1 = ax.bar(x - width, t_rec, width, label='Recursivo')
bar2 = ax.bar(x - width, t_mem/1e3, width, label='Memoización')
bar3 = ax.bar(x, t_dp/1e3, width, label='Prog. Dinámica')

# Titulos, etiquetas y mostrar gráfico
ax.set_title('Tiempo Promedio')
ax.set_xlabel('Pares Ordenados (n,m)')
#ax.set_ylabel('Tiempo ($\mu$s)')
ax.set_ylabel('Tiempo (ms)')
ax.set_xticks(x)
ax.set_xticklabels(labels, rotation=45, ha='right')
ax.legend()
plt.tight_layout()
plt.show()

# Gráfico del espacio ocupado
fig = plt.figure()
ax = fig.add_subplot(111)
width = 0.3
#bar1 = ax.bar(x - width, e_rec, width, label='Recursivo')
bar2 = ax.bar(x-width, e_mem, width, label='Memoización')
bar3 = ax.bar(x, e_dp, width, label='Prog. Dinámica')

# Título, etiquetas y mostrar gráfico
ax.set_title('Espacio Ocupado')
ax.set_xlabel('Pares Ordenados (n,m)')
ax.set_ylabel('Espacio [bytes]')
ax.set_xticks(x)
ax.set_xticklabels(labels, rotation=45, ha='right')
ax.legend()
plt.tight_layout()

plt.show()