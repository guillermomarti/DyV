import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

try:
    df = pd.read_csv('tiempos_dyv.csv')
except FileNotFoundError:
    print("Error: No se encuentra 'tiempos_dyv.csv'. Ejecuta primero ./tiempos")
    exit()

df['n'] = df['Longitud']
df['nlogn'] = df['Longitud'] * np.log2(df['Longitud'])

slope_mejor, intercept_mejor, r_mejor, p_mejor, _ = stats.linregress(df['n'], df['MejorCaso'])
slope_peor, intercept_peor, r_peor, p_peor, _ = stats.linregress(df['nlogn'], df['PeorCaso'])

print("   Regresión lineal MejorCaso ~ n")
print(f"  Pendiente: {slope_mejor:.6f}")
print(f"  R²: {r_mejor**2:.4f}")
print(f"  MSE: {np.mean((df['MejorCaso'] - (slope_mejor * df['n'] + intercept_mejor))**2):.4f}")
print(f"  p-valor: {p_mejor:.4e}\n")

print("   Regresión lineal PeorCaso ~ n log n")
print(f"  Pendiente: {slope_peor:.6f}")
print(f"  R²: {r_peor**2:.4f}")
print(f"  MSE: {np.mean((df['PeorCaso'] - (slope_peor * df['nlogn'] + intercept_peor))**2):.4f}")
print(f"  p-valor: {p_peor:.4e}")

plt.figure()
plt.scatter(df['Longitud'], df['MejorCaso'], label='MejorCaso', marker='o')
plt.scatter(df['Longitud'], df['PeorCaso'], label='PeorCaso', marker='x')
plt.xscale('log', base=2)
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title('Mejor y Peor Caso (Escala Logarítmica)')
plt.legend()
plt.grid(True)
plt.savefig('scatter_plot_log.pdf')

plt.figure()
plt.plot(df['Longitud'], df['MejorCaso'], 'o', label='MejorCaso')
plt.plot(df['Longitud'], slope_mejor * df['n'] + intercept_mejor, label=r'Ajuste $\Theta(n)$')
plt.xscale('log', base=2)
plt.xlabel('n')
plt.ylabel('Tiempo')
plt.title(r'Mejor caso $\sim \Theta(n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuste_mejor_log.pdf')

plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.plot(df['Longitud'], slope_peor * df['nlogn'] + intercept_peor, label=r'Ajuste $\Theta(n \log n)$')
plt.xscale('log', base=2)
plt.xlabel('n')
plt.ylabel('Tiempo')
plt.title(r'Peor caso $\sim \Theta(n\log n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuste_peor_log.pdf')

plt.figure()
plt.scatter(df['Longitud'], df['MejorCaso'], label='MejorCaso', marker='o')
plt.scatter(df['Longitud'], df['PeorCaso'], label='PeorCaso', marker='x')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title('Mejor y Peor Caso')
plt.legend()
plt.grid(True)
plt.savefig('scatter_plot.pdf')

plt.figure()
plt.plot(df['Longitud'], df['MejorCaso'], 'o', label='MejorCaso')
plt.plot(df['Longitud'], slope_mejor * df['n'] + intercept_mejor, label=r'Ajuste $\Theta(n)$')
plt.xlabel('n')
plt.ylabel('Tiempo')
plt.title(r'Mejor caso $\sim \Theta(n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuste_mejor.pdf')

plt.figure()
plt.plot(df['Longitud'], df['PeorCaso'], 'x', label='PeorCaso')
plt.plot(df['Longitud'], slope_peor * df['nlogn'] + intercept_peor, label=r'Ajuste $\Theta(n \log n)$')
plt.xlabel('n')
plt.ylabel('Tiempo')
plt.title(r'Peor caso $\sim \Theta(n\log n)$')
plt.legend()
plt.grid(True)
plt.savefig('ajuste_peor.pdf')