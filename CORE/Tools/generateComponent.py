import os
import sys

sys.path.insert(0, "./Helpers")

from addIncludeEntry import addInclude
from addFactoryEntry import addFactory
from generateComponentClassDefinition import genCompClassDef
from generateComponentImplementation import genCompImpl

os.chdir("..")
path = os.getcwd()

print(path)
className = input("Enter the name of the new component: ")
sourcePath = path + "\\Source"
path = path + "\\Source\\Components\\User_Defined\\" + className

path = path.replace("\\", "/")
sourcePath = sourcePath.replace("\\", "/")


#Write a skeleton class definition
genCompClassDef(className, path)

#Write skeleton member function implementations to the source file
genCompImpl(className, path)

#Add an entry to the includes manifest
addInclude(className, sourcePath)

#Add an entry to the factory constructor
addFactory(className, sourcePath)
