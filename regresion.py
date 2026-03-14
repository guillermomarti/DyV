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
df['logn'] = np.log2(df['Longitud'])

slope_mejor, intercept_mejor, r_mejor, p_mejor, _ = stats.linregress(df['logn'], df['MejorCaso'])
slope_peor, intercept_peor, r_peor, p_peor, _ = stats.linregress(df['n'], df['PeorCaso'])

print("   Regresión MejorCaso ~ log n")
print(f"  Pendiente: {slope_mejor:.6f}")
print(f"  R²: {r_mejor**2:.4f}")
print(f"  p-valor: {p_mejor:.4e}\n")

print("   Regresión PeorCaso ~ n")
print(f"  Pendiente: {slope_peor:.6f}")
print(f"  R²: {r_peor**2:.4f}")
print(f"  p-valor: {p_peor:.4e}")

# 1. COMPARATIVA MEJOR Y PEOR JUNTO (Escala Lineal)
plt.figure()
plt.plot(df['n'], df['MejorCaso'], 'o', label='MejorCaso')
plt.plot(df['n'], df['PeorCaso'], 'x', label='PeorCaso')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title('Comparativa Mejor y Peor Caso (Escala Lineal)')
plt.legend()
plt.grid(True)
plt.savefig('comparativa_lineal.pdf')

# 2. COMPARATIVA MEJOR Y PEOR JUNTO (Escala Logarítmica)
plt.figure()
plt.plot(df['n'], df['MejorCaso'], 'o', label='MejorCaso')
plt.plot(df['n'], df['PeorCaso'], 'x', label='PeorCaso')
plt.xscale('log', base=2)
plt.yscale('log', base=10) # Log en Y ayuda a ver ambos cuando hay mucha diferencia
plt.xlabel('n (log2)')
plt.ylabel('Tiempo ms (log10)')
plt.title('Comparativa Mejor y Peor Caso (Escala Logarítmica)')
plt.legend()
plt.grid(True, which="both", ls="-")
plt.savefig('comparativa_logaritmica.pdf')

# 3. AJUSTE MEJOR CASO (Escala Logarítmica - Se ve como una recta)
plt.figure()
plt.plot(df['n'], df['MejorCaso'], 'o', label='Datos Reales')
plt.plot(df['n'], slope_mejor * df['logn'] + intercept_mejor, label=r'Ajuste $\Theta(\log n)$')
plt.xscale('log', base=2)
plt.xlabel('n (log2)')
plt.ylabel('Tiempo (ms)')
plt.title(r'Ajuste Mejor Caso $\Theta(\log n)$ en Escala Logarítmica')
plt.legend()
plt.grid(True, which="both", ls="-")
plt.savefig('ajuste_mejor_log.pdf')

# 4. AJUSTE PEOR CASO (Escala Lineal - Se ve como una recta)
plt.figure()
plt.plot(df['n'], df['PeorCaso'], 'x', label='Datos Reales', color='orange')
plt.plot(df['n'], slope_peor * df['n'] + intercept_peor, label=r'Ajuste $\Theta(n)$', color='red')
plt.xlabel('n')
plt.ylabel('Tiempo (ms)')
plt.title(r'Ajuste Peor Caso $\Theta(n)$ en Escala Lineal')
plt.legend()
plt.grid(True)
plt.savefig('ajuste_peor_lineal.pdf')