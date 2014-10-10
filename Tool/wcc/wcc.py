from wil import wyacc
import sys,os
if __name__ == '__main__':
    if len(sys.argv) == 2:
        fp = open(sys.argv[1],'r')
        data = fp.read()
        fp.close()
        print ' >> WCC %s'%(sys.argv[1])
        wyacc.parse(data)
    else:
        fp = open('../../Entry/system/kernel2/config/example.wil','r')
        data = fp.read()
        fp.close()
        print ' >> WCC ../../Entry/system/kernel2/config/example.wil'
        wyacc.parse(data)
    
