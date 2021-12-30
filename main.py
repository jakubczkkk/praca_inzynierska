import sys
import os
from PyQt5.QtWidgets import QMainWindow, QApplication, QWidget, QPushButton, QAction, QLineEdit, QMessageBox, QLabel, QRadioButton, QGridLayout
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import pyqtSlot
from plot import *

class App(QMainWindow):

    def __init__(self):

        super().__init__()
        self.title = 'PyQt5 textbox - pythonspot.com'
        self.left = 10
        self.top = 10
        self.width = 450
        self.height = 600
        self.initUI()
    
    def initUI(self):

        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        # layout = QGridLayout()
        # self.setLayout(layout)

        self.nFotLabel = QLabel("NFot", self)
        self.nFotLabel.move(20, 20)
        self.nFot = QLineEdit("1000000", self)
        self.nFot.move(50, 20)

        self.n1Label = QLabel("n1", self)
        self.n1Label.move(20, 60)
        self.n1 = QLineEdit("1.3", self)
        self.n1.move(50, 60)
        self.n2Label = QLabel("n2", self)
        self.n2Label.move(220, 60)
        self.n2 = QLineEdit("1.6", self)
        self.n2.move(250, 60)

        self.g1Label = QLabel("g1", self)
        self.g1Label.move(20, 100)
        self.g1 = QLineEdit("0.05", self)
        self.g1.move(50, 100)
        self.g2Label = QLabel("g2", self)
        self.g2Label.move(220, 100)
        self.g2 = QLineEdit("0.8", self)
        self.g2.move(250, 100)
        
        self.mis1Label = QLabel("mis1", self)
        self.mis1Label.move(20, 140)
        self.mis1 = QLineEdit("500", self)
        self.mis1.move(50, 140)
        self.mis2Label = QLabel("mis2", self)
        self.mis2Label.move(220, 140)
        self.mis2 = QLineEdit("500", self)
        self.mis2.move(250, 140)
        
        self.mia1Label = QLabel("mia1", self)
        self.mia1Label.move(20, 180)
        self.mia1 = QLineEdit("5", self)
        self.mia1.move(50, 180)
        self.mia2Label = QLabel("mia2", self)
        self.mia2Label.move(220, 180)
        self.mia2 = QLineEdit("25", self)
        self.mia2.move(250, 180)

        self.xLabel = QLabel("x", self)
        self.xLabel.move(20, 220)
        self.x = QLineEdit("0", self)
        self.x.resize(70, 30)
        self.x.move(40, 220)

        self.yLabel = QLabel("y", self)
        self.yLabel.move(120, 220)
        self.y = QLineEdit("0", self)
        self.y.move(140, 220)
        self.y.resize(70, 30)

        self.zLabel = QLabel("z", self)
        self.zLabel.move(220, 220)
        self.z = QLineEdit("0.03", self)
        self.z.move(240, 220)
        self.z.resize(70, 30)
        
        self.rLabel = QLabel("r", self)
        self.rLabel.move(320, 220)
        self.r = QLineEdit("0.02", self)
        self.r.move(340, 220)
        self.r.resize(70, 30)

        self.button_absorbtion = QPushButton('Rozmieszczenie absorbcji', self)
        self.button_absorbtion.move(20, 490)
        self.button_absorbtion.clicked.connect(lambda: self.on_click(0))

        self.button_scattering = QPushButton('Położenie fotonu', self)
        self.button_scattering.move(220, 490)
        self.button_scattering.clicked.connect(lambda: self.on_click(1))

        self.button_absorbtion = QPushButton('Silne absorbowanie', self)
        self.button_absorbtion.move(20, 540)
        self.button_absorbtion.clicked.connect(lambda: self.on_click(2))

        self.button_scattering = QPushButton('Silne rozpraszanie', self)
        self.button_scattering.move(220, 540)
        self.button_scattering.clicked.connect(lambda: self.on_click(3))

        self.show()
    
    @pyqtSlot()
    def on_click(self, mode):

        nFot = float(self.nFot.text())
        n1 = float(self.n1.text())
        n2 = float(self.n2.text())
        g1 = float(self.g1.text())
        g2 = float(self.g2.text())
        mis1 = float(self.mis1.text())
        mis2 = float(self.mis2.text())
        mia1 = float(self.mia1.text())
        mia2 = float(self.mia2.text())
        x = float(self.x.text())
        y = float(self.y.text())
        z = float(self.z.text())
        r = float(self.r.text())

        if mode == 1:
            nFot = 1

        os.system("g++ main.cpp photon.cpp tools.cpp")
        simultion_exec = f"./a.out {mode} {nFot} {n1} {n2} {g1} {g2} {mis1} {mis2} {mia1} {mia2} {x} {y} {z} {r}"
        os.system(simultion_exec)

        if mode == 1:
            photon_path()
        else:
            absorbtion_plot()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())
