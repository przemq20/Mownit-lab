from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
f = open("euler2.txt", "r")
x = []
y = []
z = []
num_lines = sum(1 for line in open('euler2.txt'))

for i in range(int(num_lines / 3)):
    x.append(float(f.readline()))
    y.append(float(f.readline()))
    z.append(float(np.e**(-2*np.cos(x[i]))-2*np.cos(x[i])+1))

plot = plt.plot(x,y,x,z)
plt.title("Dokładność metody Eulera dla 5 kroków")
# plt.title("Dokładność metody Rungego-Kutta dla 5 kroków")
# plt.legend(["Metoda Rungego-Kutta","Dokładny wynik"])
plt.legend(["Metoda Eulera","Dokładny wynik"])
plt.show()
