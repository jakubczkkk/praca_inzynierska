import matplotlib.pyplot as plt
import numpy as np

data = []
with open("photon.dat", "r") as f:
    data = np.loadtxt(f, delimiter=" ").transpose()
    

plt.imshow(np.log(data + 1e-6), cmap="binary")
plt.savefig("A.png")