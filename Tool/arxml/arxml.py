import xml.etree.ElementTree as ET

__all__ = ['arXML']
import re
reNameSpace  = re.compile(r'{(.*)}')

class arXML():
    def __init__(self,arxml_file):
        self.__namespace__ = None
        self.get_arxml(arxml_file)
        
    def get_packages(self):
        packages = self.__arxml__.find('{%s}AR-PACKAGES'%(self.__namespace__))
        packages = packages.find('{%s}AR-PACKAGE'%(self.__namespace__))
        packages = packages.find('{%s}AR-PACKAGES'%(self.__namespace__))
        packages = packages.find('{%s}AR-PACKAGE'%(self.__namespace__))
        packages = packages.find('{%s}ELEMENTS'%(self.__namespace__))
        packages = packages.findall('{%s}ECUC-MODULE-DEF'%(self.__namespace__))  
        return packages
    
    def get_package(self,package_name):
        for package in self.get_packages():
            if(package_name == package.find('{%s}SHORT-NAME'%(self.__namespace__)).text):
                return package
        return None
    
    def get_package_name_list(self):
        name = []
        for package in self.get_packages():
            name.append(package.find('{%s}SHORT-NAME'%(self.__namespace__)).text)
        return name
    
    def get_version(self):
        admin_data = self.__arxml__.find('{%s}ADMIN-DATA'%(self.__namespace__))
        doc_revisons = admin_data.find('{%s}DOC-REVISIONS'%(self.__namespace__))
        doc_revison = doc_revisons.find('{%s}DOC-REVISION'%(self.__namespace__))
        version = doc_revison.find('{%s}REVISION-LABEL'%(self.__namespace__)).text
        return ('AUTOSAR %s'%(version))
        
    def get_arxml(self,arxml_file):
        self.__arxml__ =  ET.parse(arxml_file).getroot()
        self.__namespace__ = reNameSpace.match(self.__arxml__.tag).groups()[0]
        return self.__arxml__