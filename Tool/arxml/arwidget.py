

from PyQt4 import QtCore, QtGui
from PyQt4.QtGui import *
from PyQt4.QtCore import *
from arxml import *

__all__ = ['arMain']

class arMenuAction(QAction):
    def __init__(self,text,parent): 
        super(QAction,self).__init__(text,parent) 
        self.root =  parent
        self.connect(self,SIGNAL('triggered()'),self.on_menu_action)
 
    def on_menu_action(self):
        self.root.on_menu_action(self.text())

class arSelectList(QDialog):
    def __init__(self,select_list,parent=None):
        super(QDialog,self).__init__(parent)
        hbox = QHBoxLayout()
        self.qTree = QTreeWidget()
        self.qTree.setHeaderLabel('Select')
        for select in select_list:
            item = QTreeWidgetItem()
            item.setText(0,select)
            self.qTree.addTopLevelItem(item)
        self.connect(self.qTree, SIGNAL('itemSelectionChanged()'),self.on_qTree_itemSelectionChanged)
        hbox.addWidget(self.qTree)
        qBtnOK = QPushButton('OK')
        self.connect(qBtnOK, SIGNAL('clicked()'),self.on_qBtnOK_clicked)
        hbox.addWidget(qBtnOK)
        qBtnCancel = QPushButton('Cancel')
        self.connect(qBtnCancel, SIGNAL('clicked()'),self.on_qBtnCancel_clicked)        
        hbox.addWidget(qBtnCancel)
        self.setLayout(hbox)
        self.setWindowTitle('Select')
        self.select = select_list[0]
        self.result = None
    def on_qBtnOK_clicked(self):
        self.result = self.select
        self.close()
    def on_qBtnCancel_clicked(self):
        self.result = None
        self.close()
    def on_qTree_itemSelectionChanged(self):
        self.select = self.qTree.currentItem().text(0)
        
class arCmp(QTreeWidgetItem):
    def __init__(self,cmp_name,parent):
        self.arproject = parent
        super(QTreeWidgetItem,self).__init__()
        self.setText(0,cmp_name)

class arProject(QDockWidget):
    def __init__(self,project_name,parent):
        self.armain =  parent;
        super(QDockWidget,self).__init__(project_name,parent)
        
        self.arxml = arXML('AUTOSAR_MOD_ECUConfigurationParameters.arxml')
        
        self.setAllowedAreas(QtCore.Qt.LeftDockWidgetArea|QtCore.Qt.RightDockWidgetArea)
        
        qSplitter = QSplitter(Qt.Horizontal,self)
        
        self.qTree = QTreeWidget()
        self.qTree.setHeaderLabel('Project')
        
        qButtonBox = QWidget()
        vbox = QVBoxLayout()
        qBtnAdd = QPushButton('Add')
        qBtnAdd.setStatusTip('add a AUTOSAR component')
        qBtnRemove = QPushButton('Remove')
        qBtnRemove.setStatusTip('remove a AUTOSAR component')
        qBtnEdit = QPushButton('Edit')
        qBtnEdit.setStatusTip('edit a AUTOSAR component')
        
        self.connect(qBtnAdd, SIGNAL('clicked()'),self.on_qBtnAdd_clicked)
        self.connect(qBtnRemove, SIGNAL('clicked()'),self.on_qBtnRemove_clicked)
        self.connect(qBtnEdit, SIGNAL('clicked()'),self.on_qBtnEditclicked)
        vbox.addWidget(qBtnAdd)
        vbox.addWidget(qBtnRemove)
        vbox.addWidget(qBtnEdit)
        qButtonBox.setLayout(vbox)
        
        qInfo = QWidget()
        vbox = QVBoxLayout()
        self.qPTEInformation = QPlainTextEdit()
        self.qPTEInformation.setReadOnly(True)
        vbox.addWidget(self.qPTEInformation)
        qInfo.setLayout(vbox)
        
        qSplitter.insertWidget(0,self.qTree)
        qSplitter.insertWidget(1,qButtonBox)
        qSplitter.insertWidget(2,qInfo)

        self.setWidget(qSplitter)
    def isNotAdded(self,package_name):
        for i in range(0,self.qTree.topLevelItemCount()):
            item = self.qTree.topLevelItem(i)
            if(str(item.text(0)) == package_name):
                return False
        return True
    
    def on_qBtnAdd_clicked(self):
        package_names = self.arxml.get_package_name_list()
        select_list = []
        for name in package_names:
            if(self.isNotAdded(name)):
                select_list.append(name)
        ar_select = arSelectList(select_list)
        ar_select.exec_()
        if(ar_select.result):
            self.qTree.addTopLevelItem(arCmp(ar_select.result,self))
    def on_qBtnRemove_clicked(self):
        pass
    def on_qBtnEditclicked(self):
        pass
    
class arMain(QMainWindow):
    def __init__(self):
        
        QMainWindow.__init__(self, None)
        self.setWindowTitle('WhatsApp Configuration Studio (parai@foxmail.com ^_^)');
        self.showMaximized()
        self.setMinimumSize(800, 400)
        self.arxml = arXML('AUTOSAR_MOD_ECUConfigurationParameters.arxml')
        
        # Gui init
        self.creStatusBar()
        self.creMenu()
        arproject = arProject('WhatsApp',self)
        self.addDockWidget(QtCore.Qt.RightDockWidgetArea, arproject)
        
    def creMenu(self):
        # File
        tMenu=self.menuBar().addMenu(self.tr('File'))
        ## Open Ctrl+O  
        sItem=QAction(self.tr('Open'),self) 
        sItem.setShortcut('Ctrl+O'); 
        sItem.setStatusTip('Open a WhastsApp configure file.')
        self.connect(sItem,SIGNAL('triggered()'),self.on_menu_action_open)  
        tMenu.addAction(sItem) 
        ## Save Ctrl+S
        sItem=QAction(self.tr('Save'),self) 
        sItem.setShortcut('Ctrl+S'); 
        sItem.setStatusTip('Save the OpenSAR configure file.')
        self.connect(sItem,SIGNAL('triggered()'),self.on_menu_action_save)  
        tMenu.addAction(sItem)  
        ## Save Ctrl+G
        sItem=QAction(self.tr('Generate'),self) 
        sItem.setShortcut('Ctrl+G'); 
        sItem.setStatusTip('Convert the WhatsApp configure file to C Code.')
        self.connect(sItem,SIGNAL('triggered()'),self.on_menu_action_gen)  
        tMenu.addAction(sItem)
        # WahtsApp Module
        tMenu=self.menuBar().addMenu(self.tr('Module'))
        for name in self.arxml.get_module_def_name_list():
            sItem=arMenuAction(self.tr(name),self) 
            sItem.setStatusTip('Open %s Module.'%(name)) 
            tMenu.addAction(sItem)      
    def creStatusBar(self):
        self.statusBar = QStatusBar()
        self.setStatusBar(self.statusBar)
        self.statusBar.showMessage('WhatsApp Configuration Studio',0)
        
    # actions
    def on_menu_action_open(self):
        pass
    def on_menu_action_save(self):
        pass
    def on_menu_action_gen(self):
        pass
    def on_menu_action(self,module_name):
        pass