import matplotlib.pyplot as plt
import numpy as np

data = []
with open("photon.dat", "r") as f:
    data = np.loadtxt(f, delimiter=" ").transpose()

# print(data)

# plt.imshow(data, interpolation='none')

# plt.gca().invert_yaxis()
plt.plot(data[0], data[2])
plt.axis([-0.4, 0.4, 0.2, 0])
plt.savefig("A.png")