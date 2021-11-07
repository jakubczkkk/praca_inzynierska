import matplotlib.pyplot as plt
import numpy as np

data = []
with open("A.csv", "r") as f:
    data = np.loadtxt(f, delimiter=",")

plt.imshow(data, interpolation='none')
plt.savefig("A.png")
