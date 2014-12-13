

from PyQt4 import QtCore, QtGui
from PyQt4.QtGui import *
from PyQt4.QtCore import *
from arxml import *
import re,os

__all__ = ['arMain']

cButtonNumber = 8

class arAction(QAction):
    signal_triggered = pyqtSignal(QString)
    def __init__(self,text,parent=None): 
        super(QAction,self).__init__(text,parent) 
        self.connect(self,SIGNAL('triggered()'),self.on_menu_action)
 
    def on_menu_action(self):
        self.signal_triggered.emit(self.text())

class arButton(QPushButton):
    signal_clicked = pyqtSignal(QString)
    def __init__(self,name,parent=None): 
        super(QPushButton,self).__init__(name,parent) 
        self.connect(self,SIGNAL('clicked()'),self.on_button_clicked)
    def on_button_clicked(self):
        self.signal_clicked.emit(self.text())
        
    def setText2(self,text):
        if(text != ''):
            self.setDisabled(False)
            self.setVisible(True)
        else:
            self.setDisabled(True)
            self.setVisible(False)
        self.setText(text)

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

class arContainerItem(QTreeWidgetItem):
    def __init__(self,url,cfg=None):
        '''url: refer the ECUC-PARAM-CONF-CONTAINER-DEF
           cfg: refer the ECUC-PARAM-CONF-CONTAINER-CFG
        '''
        self.DEF = ARXML().URL(url)
        self.url = url
        assert(self.DEF != None)
        if(cfg == None): 
            self.cfg = ARXML().new_cfg_by_url(url)
        else:
            self.cfg = cfg
        super(QTreeWidgetItem,self).__init__()
        self.setText(0,os.path.basename(url))

    def get_displayer(self): 
        container_def = ARXML().URL(self.url)
        self.qDisplayer = QScrollArea()
        self.grid = QGridLayout()
        self.qDisplayer.setLayout(self.grid)
        return self.qDisplayer

    def get_sub_container_urls(self):
        container_def = ARXML().URL(self.url)
        sub_containers = []
        for sub_container in ARXML().FIND(container_def,'SUB-CONTAINERS'):
            sub_containers.append('%s/%s'%(self.url,ARXML().NAME(sub_container)))
        return sub_containers
    
    def get_url(self):
        return self.url
 
class arPackage(QMainWindow):
    reAdd = re.compile(r'Add\s+(\w+)')
    reRemove = re.compile(r'Remove\s+(\w+)')
    def __init__(self,name):
        super(QMainWindow,self).__init__()
        qSplitter = QSplitter(Qt.Horizontal,self)
        
        self.qTree = QTreeWidget()
        self.qTree.setHeaderLabel(name)
        self.connect(self.qTree, SIGNAL('itemSelectionChanged()'),self.on_qTree_itemSelectionChanged)
        
        qButtonBox = QWidget()
        vbox = QVBoxLayout()
        self.arbuttons = []
        for i in range(cButtonNumber):
            arbutton = arButton('button%s'%(i))
            self.arbuttons.append(arbutton)
            vbox.addWidget(arbutton)
            arbutton.signal_clicked.connect(self.on_button_clicked)
        qButtonBox.setLayout(vbox)

        url = '/AUTOSAR/EcucDefs/%s'%(name)
        module_cfg = ARXML().URL(url)
        
        for container in ARXML().FIND(module_cfg,'CONTAINERS'):
            name = ARXML().NAME(container)
            sub_url = '%s/%s'%(url,name)
            item = arContainerItem(sub_url,ARXML().get_cfg_by_url(sub_url))
            self.qTree.addTopLevelItem(item)

        for i in range(0,cButtonNumber):
            self.arbuttons[i].setText2('')
        self.qDisplayer = QMainWindow()
        
        qSplitter.insertWidget(0,self.qTree)
        qSplitter.insertWidget(1,qButtonBox)
        qSplitter.insertWidget(2,self.qDisplayer)

        self.setCentralWidget(qSplitter)
    def on_button_clicked(self,text):
        text = str(text)
        p_item = self.qTree.currentItem()
        if(self.reAdd.match(text)):
            item = arContainerItem('%s/%s'%(p_item.get_url(),self.reAdd.match(text).groups()[0]))
            p_item.addChild(item)
        elif(self.reRemove.match(text)):
            pass
        else:
            assert(0)     
    def on_qTree_itemSelectionChanged(self): 
        item = self.qTree.currentItem()
        print item
        self.qDisplayer.setCentralWidget(item.get_displayer())
        I = 0
        for sub_container_url in item.get_sub_container_urls():
            self.arbuttons[I].setText2('Add %s'%(os.path.basename(sub_container_url))) 
            I = I + 1
        if(self.qTree.indexOfTopLevelItem(item) == -1):
            self.arbuttons[I].setText2('Remove %s'%(str(item.text(0)))) 
            I = I + 1
        for i in range(I,cButtonNumber):
            self.arbuttons[i].setText2('')
            
        
class arDockWidget(QDockWidget): 
    def __init__(self,name,parent=None):
        QDockWidget.__init__(self,name,parent)
        self.setAllowedAreas(QtCore.Qt.LeftDockWidgetArea|QtCore.Qt.RightDockWidgetArea)  
        #self.setFeatures(QDockWidget.DockWidgetClosable|QDockWidget.DockWidgetMovable)
        self.isClosed = False
    def closeEvent(self,event):
        self.isClosed = True        
        
class arPackageItem(QTreeWidgetItem):
    def __init__(self,cmp_name,module_cfg=None):
        super(QTreeWidgetItem,self).__init__()
        self.setText(0,cmp_name)
        if(module_cfg==None):
            self.module_cfg = ARXML().new_module_cfg(str(cmp_name))
        else:
            self.module_cfg = module_cfg
    
    def remove(self):
        uuid = self.module_cfg.attrib['UUID']
        ARXML().remove(uuid)

class arProject(QDockWidget):
    def __init__(self,project_name,parent):
        global __arxml__
        self.armain =  parent;
        super(QDockWidget,self).__init__(project_name,parent)
        
        try:
            self.arxml = arXML('.config/ecuc_cfg.arxml')
        except:
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
        self.connect(qBtnEdit, SIGNAL('clicked()'),self.on_qBtnEdit_clicked)
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
        
        for module_cfg in ARXML().get_module_cfg_list():
            name = arxml_short_name(module_cfg)
            self.qTree.addTopLevelItem(arPackageItem(name,module_cfg))
    def is_module_not_added(self,package_name):
        for i in range(0,self.qTree.topLevelItemCount()):
            item = self.qTree.topLevelItem(i)
            if(str(item.text(0)) == package_name):
                return False
        return True
    
    def on_qBtnAdd_clicked(self):
        package_names = self.arxml.get_module_def_name_list()
        select_list = []
        for name in package_names:
            if(self.is_module_not_added(name)):
                select_list.append(name)
        ar_select = arSelectList(select_list)
        ar_select.exec_()
        if(ar_select.result):
            self.qTree.addTopLevelItem(arPackageItem(ar_select.result))
    def on_qBtnRemove_clicked(self):
        cmp = self.qTree.currentItem()
        if(cmp != None):
            self.qTree.takeTopLevelItem(self.qTree.indexOfTopLevelItem(cmp))
            cmp.remove()
    def on_qBtnEdit_clicked(self):
        cmp = self.qTree.currentItem()
        if(cmp != None):
            self.armain.show_package(cmp.text(0))
    def closeEvent(self,event):
        event.ignore()

class arMain(QMainWindow):
    def __init__(self):
        
        QMainWindow.__init__(self, None)
        self.setWindowTitle('WhatsApp Configuration Studio (parai@foxmail.com ^_^)');
        self.showMaximized()
        self.setMinimumSize(800, 400)
        
        # Gui init
        self.creStatusBar()
        self.creMenu()
        self.arproject = arProject('WhatsApp',self)
        self.addDockWidget(QtCore.Qt.RightDockWidgetArea, self.arproject)
        
        self.ardocks = {}
        self.arpackages = {}
        
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
    
    def creStatusBar(self):
        self.statusBar = QStatusBar()
        self.setStatusBar(self.statusBar)
        self.statusBar.showMessage('WhatsApp Configuration Studio',0)
        
    def show_package(self,package_name):
        package_name = str(package_name)
        try:
            arpackage = self.arpackages[package_name]
        except:
            self.arpackages[package_name] = arpackage = arPackage(package_name)
        try:
            ardock = self.ardocks[package_name]
            if(ardock.isClosed==True):ardock = None   
        except KeyError:
            ardock = None
        if(ardock==None):
            self.ardocks[package_name] = ardock= arDockWidget(package_name)
            ardock.setWidget(arpackage)
        self.addDockWidget(QtCore.Qt.RightDockWidgetArea, ardock) 
        self.tabifyDockWidget(self.arproject,ardock) 
    # actions
    def on_menu_action_open(self):
        pass
    def on_menu_action_save(self):
        ARXML().save()
        QMessageBox(QMessageBox.Information, 'Info', 'Save WhatsApp Configuration arxml Successfully !').exec_();
    def on_menu_action_gen(self):
        pass