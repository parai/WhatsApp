__copy_right__ ='''/**
 * WhatsApp - the open source AUTOSAR platform https://github.com/parai
 *
 * Copyright (C) 2014  WhatsApp <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */\n'''
import xml.etree.ElementTree as ET
import re,os,sys
import uuid
import codecs

__all__ = ['arXML']



__namespace__ = None
 
def arxml_short_name(element):
    return element.find('{%s}SHORT-NAME'%(__namespace__)).text

def arxml_desc(element):
    desc = element.find('{%s}DESC'%(__namespace__))
    if(desc==None):return None
    desc = desc.find('{%s}L-2'%(__namespace__))
    if(desc==None):return None
    return desc.text

def arxml_introduction(element):
    desc = element.find('{%s}INTRODUCTION'%(__namespace__))
    if(desc==None):return None
    desc = desc.find('{%s}P'%(__namespace__))
    if(desc==None):return None
    desc = desc.find('{%s}L-1'%(__namespace__))
    return desc.text
def arxml_containers(element):
    return element.find('{%s}CONTAINERS'%(__namespace__))

def arxml_container_def_list(element):
    reslut_list = element.findall('{%s}ECUC-PARAM-CONF-CONTAINER-DEF'%(__namespace__))
    if(reslut_list==None):reslut_list = []
    return reslut_list

def arxml_sub_containers_def_list(element):
    reslut_list = element.findall('{%s}SUB-CONTAINERS'%(__namespace__))
    if(reslut_list==None):reslut_list = []
    return reslut_list

def arxml_parameter_list(element):
    reslut_list = element.find('{%s}PARAMETERS'%(__namespace__))
    if(reslut_list==None):reslut_list = []
    return reslut_list
def arxml_LITERALS(element):
    return element.find('{%s}LITERALS'%(__namespace__))

class arXML():
    reNameSpace  = re.compile(r'{(.*)}')
    def __init__(self,arxml_file):
        global __namespace__
        self.__arxml__ =  ET.parse(arxml_file).getroot()
        __namespace__ = self.__namespace__ = self.reNameSpace.match(self.__arxml__.tag).groups()[0]
        self.generate_basic_type_header_files()
    def comment_str(self,commet):
        if(commet != None):
            result = commet.replace(r'\\s{5,1000}','') 
            if(len(result) > 98):
                comment = '/* '
                start = 0
                for i in range(len(result)):
                    if(result[i]=='\n'):
                        comment += result[start:i] + '\n * '
                        start = i + 1
                    if((i-start>90) and (i > 0) and (result[i]==' ')):
                        comment += result[start:i] + '\n * '
                        start = i
                if(start != i):
                    comment += result[start:i]
                comment += '\n */\n'
                result = comment
            else:
                result = '/* %s */\n'%(result)
        else:
            result = ''
        return result
    def type_name(self,module_name,name):
        result =  '%s_%sType'%(module_name,name[len(module_name):])  
        return result
    ''' Is it possible to Generate the basic types for each module,
        Let me have a try..
    ''' 
    def is_type_there(self,type,module_name):
        try:
            which_module = self.__type_marker[self.type_name(module_name, type)]
            is_it_there = True
        except KeyError:
            self.__type_marker[self.type_name(module_name, type)] = module_name
            is_it_there = False # generate it
        return is_it_there
    
    def generater_parameter_type(self,fp,module_name,parameter):
        name = arxml_short_name(parameter)
        parameter_type = self.comment_str(arxml_desc(parameter))
        if(parameter.tag == '{%s}ECUC-ENUMERATION-PARAM-DEF'%(__namespace__)):
            LITERALS = arxml_LITERALS(parameter)
            parameter_type2 = 'typedef enum\n{\n'
            bHasLiter = False
            for lit in LITERALS:
                bHasLiter = True
                liter_name = arxml_short_name(lit)
                if(liter_name.upper().find(module_name.upper())>0):
                    parameter_type2 += ('\t%s,\n'%(liter_name)).upper()
                else:
                    parameter_type2 += ('\t%s_%s_%s,\n'%(module_name,name[len(module_name):],liter_name)).upper()
            if(bHasLiter==False):parameter_type2 +='\tTODO: maybe specific to vendor as no LITERALS in arxml.\n'
            parameter_type2 += '} %s ;\n\n'%(self.type_name(module_name, name))
            if(bHasLiter):
                parameter_type += parameter_type2
            else:
                parameter_type += self.comment_str(parameter_type2)
        elif(parameter.tag == '{%s}ECUC-BOOLEAN-PARAM-DEF'%(__namespace__)):
            parameter_type += 'typedef boolean %s ;\n\n'%(self.type_name(module_name, name))
        elif(parameter.tag == '{%s}ECUC-INTEGER-PARAM-DEF'%(__namespace__)):
            parameter_type += 'typedef int %s ;\n\n'%(self.type_name(module_name, name))   
        elif(parameter.tag == '{%s}ECUC-FLOAT-PARAM-DEF'%(__namespace__)):
            parameter_type += 'typedef float %s ;\n\n'%(self.type_name(module_name, name))  
        elif(parameter.tag == '{%s}ECUC-LINKER-SYMBOL-DEF'%(__namespace__)):
            parameter_type += 'typedef linker %s ;\n\n'%(self.type_name(module_name, name))     
        elif(parameter.tag == '{%s}ECUC-FUNCTION-NAME-DEF'%(__namespace__)):
            parameter_type += 'typedef void* %s ;\n\n'%(self.type_name(module_name, name))   
        elif(parameter.tag == '{%s}ECUC-STRING-PARAM-DEF'%(__namespace__)):
            parameter_type += 'typedef char* %s ;\n\n'%(self.type_name(module_name, name))     
        elif(parameter.tag == '{%s}ECUC-MULTILINE-STRING-PARAM-DEF'%(__namespace__)):
            parameter_type += 'typedef char** %s ;\n\n'%(self.type_name(module_name, name))                                                         
        else:
            print(parameter.tag) 
        if(self.is_type_there(name, module_name)):
            return '' # already generated
        else: 
            return parameter_type

    def generate_contariner_types(self,fp,module_name,container): 
        assert(container.tag == '{%s}ECUC-PARAM-CONF-CONTAINER-DEF'%(__namespace__) or  \
               container.tag == '{%s}ECUC-CHOICE-CONTAINER-DEF'%(__namespace__)) 
        name = arxml_short_name(container)
        container_type = self.comment_str(arxml_desc(container))
        container_type += 'typedef struct\n{\n'
        for sub_containters in arxml_sub_containers_def_list(container):
            for sub_containter in sub_containters:
                sub_container_type = self.generate_contariner_types(fp,module_name,sub_containter)
                fp.write(sub_container_type)
                container_type += self.comment_str(arxml_introduction(sub_containter))
                sub_container_name = arxml_short_name(sub_containter)
                container_type += '\t%s* %s ;\n'%(self.type_name(module_name, sub_container_name),sub_container_name)
        for parameter in arxml_parameter_list(container):
            parameter_type = self.generater_parameter_type(fp, module_name, parameter)
            fp.write(parameter_type)
            container_type += self.comment_str(arxml_introduction(parameter))
            parameter_name = arxml_short_name(parameter)
            container_type += '\t%s %s ;\n'%(self.type_name(module_name, parameter_name),parameter_name)
        container_type += '} %s ;\n\n'%(self.type_name(module_name, name))
        if(self.is_type_there(name, module_name)):
            return '' # already generated
        else:
            return  container_type
    def generate_basic_type_header_files(self,directory='./types'):
        if(False == os.path.exists(directory)):
            os.mkdir(directory)
        self.__type_marker = {}
        for module_def in self.get_module_def_list():
            module_name = arxml_short_name(module_def)
            fp = codecs.open('%s/%s_Types.h'%(directory,module_name),'w','utf-16')
            fp.write(__copy_right__)
            fp.write('#ifndef %s_TYPES_H\n#define %s_TYPES_H\n\n'%(module_name.upper(),module_name.upper()))
            fp.write('#ifdef __cplusplus\n')
            fp.write('namespace autosar {\n')
            fp.write('extern "C" {\n')
            fp.write('#endif\n')
            fp.write('/* ============================ [ INCLUDES  ] ====================================================== */\n')
            fp.write('#include "Std_Types.h"\n')
            fp.write('/* ============================ [ MACROS    ] ====================================================== */\n')
            fp.write('/* ============================ [ TYPES     ] ====================================================== */\n')
            container_types = ''
            for container in arxml_containers(module_def):
                container_types += self.generate_contariner_types(fp,module_name,container)
            fp.write(container_types)
            fp.write('/* ============================ [ DATAS     ] ====================================================== */\n')
            fp.write('/* ============================ [ DECLARES  ] ====================================================== */\n')
            fp.write('/* ============================ [ LOCALS    ] ====================================================== */\n')
            fp.write('/* ============================ [ FUNCTIONS ] ====================================================== */\n')
            fp.write('#ifdef __cplusplus\n')
            fp.write('}}  /* name space */\n')
            fp.write('#endif /* %s_TYPES_H */\n\n'%(module_name.upper()))
            fp.close()
        
    def get_module_def_list(self):
        packages = self.__arxml__.find('{%s}AR-PACKAGES'%(self.__namespace__))
        packages = packages.find('{%s}AR-PACKAGE'%(self.__namespace__))
        packages = packages.find('{%s}AR-PACKAGES'%(self.__namespace__))
        packages = packages.find('{%s}AR-PACKAGE'%(self.__namespace__))
        packages = packages.find('{%s}ELEMENTS'%(self.__namespace__))
        packages = packages.findall('{%s}ECUC-MODULE-DEF'%(self.__namespace__))  
        return packages
    
    def get_module_def(self,package_name):
        for package in self.get_module_def_list():
            if(package_name == package.find('{%s}SHORT-NAME'%(self.__namespace__)).text):
                return package
        return None
    
    def get_module_def_name_list(self):
        name = []
        for package in self.get_module_def_list():
            name.append(package.find('{%s}SHORT-NAME'%(self.__namespace__)).text)
        return name
    
    def get_version(self):
        admin_data = self.__arxml__.find('{%s}ADMIN-DATA'%(self.__namespace__))
        doc_revisons = admin_data.find('{%s}DOC-REVISIONS'%(self.__namespace__))
        doc_revison = doc_revisons.find('{%s}DOC-REVISION'%(self.__namespace__))
        version = doc_revison.find('{%s}REVISION-LABEL'%(self.__namespace__)).text
        return ('AUTOSAR %s'%(version))
        
    def get_arxml(self):
        return self.__arxml__
    
    
if __name__ == '__main__':
    arXML('AUTOSAR_MOD_ECUConfigurationParameters.arxml')