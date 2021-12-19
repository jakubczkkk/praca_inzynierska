import matplotlib.pyplot as plt
import numpy as np

data = []
with open("pos.dat", "r") as f:
    data = np.loadtxt(f, delimiter=" ").transpose()

fig = plt.figure()
ax = plt.axes(projection='3d')

zdata = data[2]
xdata = data[0]
ydata = data[1]

ax.set_xlim3d(-0.1, 0.1)
ax.set_ylim3d(-0.1, 0.1)
ax.set_zlim3d(0.2, 0)
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("z")
ax.scatter3D(xdata, ydata, zdata, c=data[3], cmap='binary')
ax.plot3D(xdata, ydata, zdata, c='black')

plt.show()

# data = []
# with open("photon.dat", "r") as f:
#     data = np.loadtxt(f, delimiter=" ").transpose()
    
# plt.imshow(np.log(data + 1e-6), cmap="binary", extent=[-0.1, 0.1, 0.2, 0] )
# plt.xlabel('x')
# plt.ylabel('z')

# plt.savefig("B.png")
