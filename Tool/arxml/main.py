import os,sys
from PyQt4 import QtCore, QtGui
from PyQt4.QtGui import *
from PyQt4.QtCore import *
from arwidget import *

def main():
    qtApp = QtGui.QApplication(sys.argv)
    if(os.name == 'nt'):
        qtApp.setFont(QFont('Consolas')) 
    elif(os.name == 'posix'):
        qtApp.setFont(QFont('Monospace'))
    else:
        print('unKnown platform.')
    qtGui = arMain()
    qtGui.show()
    qtApp.exec_()
    
if __name__ == '__main__':
    main()