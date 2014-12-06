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
 * Version: %s
 * Generated by arxml.py
 */\n'''
 
__comment__ = '''
    What is arxml?
    This is a difficult question to me, I do have much knowledge about it, this is just
    a starting journey to know it.
    Oh shit, I don't what to read specification, so this is an eyes-closed wondering.
    I guess:
    ARXML is a ECUC definition and configuration database, it should be operated by UUID
'''

import xml.etree.ElementTree as ET
import re,os,sys
import uuid
import codecs

__all__ = ['arXML','ARXML', \
           'arxml_short_name']


__arxml_global_instance__ = None
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

def arxml_MAX(element):
    max = element.find('{%s}MAX'%(__namespace__)).text
    max = int(max,10)
    return max
def arxml_MIN(element):
    min = element.find('{%s}MIN'%(__namespace__)).text
    min = int(min,10)
    return min

class arXML():
    reNameSpace  = re.compile(r'{(.*)}')
    def __init__(self,arxml_file):
        global __namespace__,__arxml_global_instance__
        self.__arxml__ =  ET.parse(arxml_file).getroot()
        __namespace__ = self.__namespace__ = self.reNameSpace.match(self.__arxml__.tag).groups()[0]
        ET.register_namespace('', __namespace__)
        # if want the type generate, to it
        #self.generate_basic_type_header_files()
        self.init_uuid_map()
        __arxml_global_instance__ = self
    def search_from(self,root,url):
        try:
            if(arxml_short_name(root)==url):
                return root
        except:
            pass
        for sub in root:
            try:
                if(arxml_short_name(sub)==url):
                    return sub
                else:
                    for sub1 in sub:
                        result = self.search_from(sub1,url)
                        if(result != None):return result
            except:
                for sub1 in sub:
                    result = self.search_from(sub1,url)
                    if(result != None):return result
        return None
    def URL(self,url=''):
        ''' Uniform Resource Locator'''
        result = self.__arxml__
        url = url.split('/')
        for url1 in url:
            if(url1==''):continue
            result = self.search_from(result,url1)
            if(result==None):break   
        return result
    def remove(self,uuid,starter = None,parent = None):
        if(starter == None):
            starter = self.URL('/AUTOSAR/EcucCfgs')
        try:
            if(starter.attrib['UUID'] == uuid):
                parent.remove(starter)
        except KeyError:
            pass            
        for sub in starter:
            try:
                if(sub.attrib['UUID'] == uuid):
                    starter.remove(sub)
                    return True
                else:
                    for sub1 in sub:
                        result = self.remove(uuid, sub1,sub)
                        if(result != False):return True
            except KeyError:
                for sub1 in sub:
                    result = self.remove(uuid, sub1,sub)
                    if(result != False):return True
        return False
    def init_uuid_map(self):
        pass
## { ================ [ FOR TYPES START ] =========================================
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
                    comment += result[start:]
                comment += '\n */\n'
                result = comment
            else:
                result = '/* %s */\n'%(result)
        else:
            result = ''
        return result
    def type_name(self,module_name,name):
        if(name.upper().find(module_name.upper()) > -1):
            result =  '%s_%sType'%(module_name,name[len(module_name):]) 
        else:
            result =  '%s_%sType'%(module_name,name) 
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
    def is_type_very_basic(self,type):
        __very_basic_type = ['boolean','uint8','uint16','uint32','uint64','sint8','sint16','sint32','sint64','void*','char*','char**','function_t']
        try:
            existes = __very_basic_type.index(type)
            return True
        except:
            return False
    def range_to_basic_type(self,min,max):
        if(min<max):
            if((min>=0) and (max<=0xFF)):
                return 'uint8'
            elif((min>=0) and (max<=0xFFFF)):
                return 'uint16'
            elif((min>=0) and (max<=0xFFFFFFFF)):
                return 'uint32'
            elif((min>=0) and (max<=0xFFFFFFFFFFFFFFFF)):
                return 'uint64'
            else:
                assert(0)                                   
        else:
            assert(0)
    def generater_parameter_type(self,fp,module_name,parameter):
        name = arxml_short_name(parameter)
        parameter_type = self.comment_str(arxml_desc(parameter))
        basic_type = self.type_name(module_name, name)
        if(parameter.tag == '{%s}ECUC-ENUMERATION-PARAM-DEF'%(__namespace__)):
            LITERALS = arxml_LITERALS(parameter)
            parameter_type2 = 'typedef enum\n{\n'
            bHasLiter = False
            for lit in LITERALS:
                bHasLiter = True
                liter_name = arxml_short_name(lit)
                if(liter_name.upper().find(module_name.upper())>-1):
                    parameter_type2 += ('\t%s,\n'%(liter_name)).upper()
                else:
                    if(name.upper().find(module_name.upper())>-1):
                        parameter_type2 += ('\t%s_%s_%s,\n'%(module_name,name[len(module_name):],liter_name)).upper()
                    else:
                        parameter_type2 += ('\t%s_%s_%s,\n'%(module_name,name,liter_name)).upper()
            if(bHasLiter==False):parameter_type2 +='\tTODO: maybe specific to vendor as no LITERALS in arxml.\n'
            parameter_type2 += '} %s ;\n\n'%(self.type_name(module_name, name))
            if(bHasLiter):
                parameter_type += parameter_type2
            else:
                parameter_type += self.comment_str(parameter_type2)
        elif(parameter.tag == '{%s}ECUC-BOOLEAN-PARAM-DEF'%(__namespace__)):
            basic_type = 'boolean'
        elif(parameter.tag == '{%s}ECUC-INTEGER-PARAM-DEF'%(__namespace__)):
            max = arxml_MAX(parameter)
            min = arxml_MIN(parameter)
            basic_type = self.range_to_basic_type(min, max)  
        elif(parameter.tag == '{%s}ECUC-FLOAT-PARAM-DEF'%(__namespace__)):
            parameter_type += '/* in fact, it should be type <float> according to arxml, but only supported in tool side*/\n'
            basic_type = 'uint64' 
        elif(parameter.tag == '{%s}ECUC-LINKER-SYMBOL-DEF'%(__namespace__)):
            parameter_type += '/* TODO: I don\'t know how to implement it */\n'
            basic_type = 'void*'     
        elif(parameter.tag == '{%s}ECUC-FUNCTION-NAME-DEF'%(__namespace__)):
            parameter_type += '/* TODO: \n'
            parameter_type += ' * typedef void (*%s)(void);\n'%(self.type_name(module_name, name))
            parameter_type += ' */\n\n'
        elif(parameter.tag == '{%s}ECUC-STRING-PARAM-DEF'%(__namespace__)):
            basic_type = 'char*'   
        elif(parameter.tag == '{%s}ECUC-MULTILINE-STRING-PARAM-DEF'%(__namespace__)):
            basic_type = 'char**'                                                       
        else:
            assert(0)
        if(self.is_type_there(name, module_name)):parameter_type = '' # clear it
        return parameter_type,basic_type

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
            parameter_type,basic_type = self.generater_parameter_type(fp, module_name, parameter)
            if(False == self.is_type_very_basic(basic_type)):fp.write(parameter_type)
            container_type += self.comment_str(arxml_introduction(parameter))
            parameter_name = arxml_short_name(parameter)
            if(False == self.is_type_very_basic(basic_type)):
                container_type += '\t%s %s ;\n'%(basic_type,parameter_name)
            else:
                # in this case, parameter_type is a comment
                container_type += '%s\t%s %s ;\n'%(parameter_type,basic_type,parameter_name)
        container_type += '} %s ;\n\n'%(self.type_name(module_name, name))
        if(self.is_type_there(name, module_name)):
            return '' # already generated
        else:
            return  container_type
    def generate_basic_type_header_files(self,directory='../../Entry/include/types'):
        if(False == os.path.exists(directory)):
            os.mkdir(directory)
        self.__type_marker = {}
        for module_def in self.get_module_def_list():
            module_name = arxml_short_name(module_def)
            fp = codecs.open('%s/%s_Types.h'%(directory,module_name),'w','utf-16')
            fp.write(__copy_right__ % (self.get_version()))
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
## } ================ [ FOR TYPES END ] =========================================        
    def get_module_def_list(self):
        elements = self.get_def_elements()
        module_def_list = elements.findall('{%s}ECUC-MODULE-DEF'%(self.__namespace__))  
        return module_def_list
    
    def get_module_def(self,name):
        for module_def in self.get_module_def_list():
            if(name == arxml_short_name(module_def)):
                return module_def
        return None
    
    def get_module_def_name_list(self):
        name = []
        for module_def in self.get_module_def_list():
            name.append(arxml_short_name(module_def))
        return name
    
    def get_version(self):
        admin_data = self.__arxml__.find('{%s}ADMIN-DATA'%(self.__namespace__))
        doc_revisons = admin_data.find('{%s}DOC-REVISIONS'%(self.__namespace__))
        doc_revison = doc_revisons.find('{%s}DOC-REVISION'%(self.__namespace__))
        version = doc_revison.find('{%s}REVISION-LABEL'%(self.__namespace__)).text
        return ('AUTOSAR %s'%(version))
        
    def get_arxml(self):
        return self.__arxml__
    def get_cfg_elements(self):
        cfg_package = self.URL('/AUTOSAR/EcucCfgs')
        if(cfg_package != None):
            return cfg_package.find('{%s}ELEMENTS'%(self.__namespace__))
        else:
            autosar = self.URL('/AUTOSAR').find('{%s}AR-PACKAGES'%(self.__namespace__))
            cfg_package = ET.Element('AR-PACKAGE')
            cfg_package.attrib['UUID'] = 'ECUC:ECUCCFGS'
            short_name = ET.Element('SHORT-NAME')
            short_name.text = 'EcucCfgs'
            cfg_package.append(short_name)
            ELEMENTS = ET.Element('ELEMENTS')
            cfg_package.append(ET.Element('ELEMENTS'))
            autosar.append(cfg_package)
            return ELEMENTS
    def get_def_elements(self):
        def_package = self.URL('/AUTOSAR/EcucDefs')
        return def_package.find('{%s}ELEMENTS'%(self.__namespace__))

    def save(self,directory='.config'):
        if(False == os.path.exists(directory)):
            os.mkdir(directory)
        arxml = '%s/ecuc_cfg.arxml'%(directory)
        tree = ET.ElementTree(self.__arxml__)
        tree.write(arxml, encoding="utf-8", xml_declaration=True)
    def new_module_cfg(self,name):
        UUID = uuid.uuid1()
        module_cfg = ET.Element('ECUC-MODULE-CFG')
        module_cfg.attrib['UUID'] = 'ECUC:%s'%(UUID)
        short_name = ET.Element('SHORT-NAME')
        short_name.text = name
        module_cfg.append(short_name)
        self.get_cfg_elements().append(module_cfg)
        return module_cfg
    def get_module_cfg_list(self):
        elements = self.get_cfg_elements()
        module_cfg_list = elements.findall('{%s}ECUC-MODULE-CFG'%(self.__namespace__))  
        return module_cfg_list 
    
def ARXML():  
    return __arxml_global_instance__ 
    
if __name__ == '__main__':
    arXML('AUTOSAR_MOD_ECUConfigurationParameters.arxml')