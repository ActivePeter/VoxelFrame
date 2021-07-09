import _config as conf
import os

if conf.cmakePath=="":
    preMakeCmd='cmake'
else:
    preMakeCmd="\""+conf.cmakePath+"\""

if conf.generator=="":
    generatorCmd=''
else:
    generatorCmd='-G '+conf.generator

if conf.makePath=="":
    makePathCmd=''
else:
    makePathCmd='-DCMAKE_MAKE_PROGRAM='+"\""+conf.makePath+"\""

os.chdir('third')
# os.system('cd ')
print("command is:"+preMakeCmd+' '+generatorCmd+' '+makePathCmd)
os.system(preMakeCmd+' '+generatorCmd+' '+makePathCmd);