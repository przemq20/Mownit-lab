from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt

f = open("rungekutta.txt", "r")
x = []
y = []
z = []
num_lines = sum(1 for line in open('rungekutta.txt'))

for i in range(int(num_lines / 3)):
    x.append(float(f.readline()))
    y.append(float(f.readline()))
    z.append(float(f.readline()))

fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(x, y, z, c='black')
plt.show()
