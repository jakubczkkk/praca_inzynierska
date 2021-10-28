import matplotlib.pyplot as plt
import numpy as np

data = []
with open("test.csv", "r") as f:
    data = np.loadtxt(f, delimiter=",")

plt.imshow(data, interpolation='none')
plt.show()


data2 = []
with open("photon_pos.csv") as f:
    data2 = np.loadtxt(f, delimiter=",")

print(data2)