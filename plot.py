import matplotlib.pyplot as plt
import numpy as np

# data = []
# with open("pos.dat", "r") as f:
#     data = np.loadtxt(f, delimiter=" ").transpose()

# print(data)

# fig = plt.figure()
# ax = plt.axes(projection='3d')

# # Data for a three-dimensional line
# # zline = data[2]
# # xline = data[0]
# # yline = data[1]
# # ax.plot3D(xline, yline, zline, 'gray')

# # Data for three-dimensional scattered points
# zdata = data[2]
# xdata = data[0]
# ydata = data[1]
# ax.scatter3D(xdata, ydata, zdata, c=data[3], cmap='Greens')

# plt.show()

data = []
with open("photon.dat", "r") as f:
    data = np.loadtxt(f, delimiter=" ").transpose()
    
plt.imshow(np.log(data + 1e-6), cmap="binary")
plt.savefig("B.png")
