from enum import Enum, unique

class Version:

        
class Semver:
    def __init__(self):
        self.major = -1
        self.minor = -1
        self.patch = -1
        self.build = 0
     
    def setNumbers(self,major,minor,patch):
        self.major = major
        self.minor = minor
        self.patch = patch
        
    def setStage(self,stage):
        self.stage = stage
        
        
    def setBuild(self,build):
        self.build = build
        
    def setName(self,name):
        self.name = name
    
    def set(self,major,minor,patch,stage,build,name):
        self.major = major
        self.minor = minor
        self.patch = patch
        self.stage = stage
        self.build = build
        self.name = name
        
		
def getPakageVersion():
    version = Semver()
    version.setNumbers(3,7,1)
    return version
    
def getPakageName():
    return "toolkit-common"

vers = Semver()
print ("pack: " , getPakageName())
