import matplotlib.pyplot as plt
import numpy as np

def read_data(filename):
    
    data = []
    with open(filename, "r") as f:
        data = np.loadtxt(f, delimiter=" ").transpose()
    return data

def absorbtion_plot():

    data = read_data("photon.dat")
    plt.title("Profil absorpcji")
    plt.imshow(np.log(data + 1e-6), cmap="inferno", extent=[-0.1, 0.1, 0.2, 0])
    plt.xticks([-0.1, -0.05, 0, 0.05, 0.1])
    plt.yticks([0.2, 0.15, 0.1, 0.05, 0])
    plt.xlabel('x')
    plt.ylabel('z')
    plt.show()

def photon_path():

    data = read_data("pos.dat")
    fig = plt.figure()
    ax = plt.axes(projection='3d')
    zdata = data[2]
    xdata = data[0]
    ydata = data[1]
    ax.set_xlim3d(-0.1, 0.1)
    ax.set_ylim3d(-0.1, 0.1)
    ax.set_zlim3d(0.2, 0)
    ax.set_xticks([-0.1, -0.05, 0, 0.05, 0.1])
    ax.set_yticks([-0.1, -0.05, 0, 0.05, 0.1])
    ax.set_zticks([0.2, 0.15, 0.1, 0.05, 0])
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_zlabel("z")
    ax.scatter3D(xdata, ydata, zdata, c=data[3], cmap='Reds')
    ax.plot3D(xdata, ydata, zdata, c='black')
    plt.show()
