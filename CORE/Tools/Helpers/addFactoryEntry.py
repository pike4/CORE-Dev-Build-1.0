#Add an entry to the constructComponent method to map the class name to the
#class constructor
def addFactory(className, sourcePath):
    otherLines = []
    factoryPath = sourcePath + "\\Subsystems\\CORE_Factory.cpp"
    with open(factoryPath, "r") as factoryFile:
        lines = factoryFile.readlines()

    for a in lines:    
        otherLines.append(a)
        if a.find("//Place user defined components here:") != -1:
            otherLines.append("\t\telse if (name == \"" + className + "\")\n")
            otherLines.append("\t\t\tret = new " + className + "();\n\n")
    factoryFile.close()

    factoryFile = open(factoryPath, "w")

    for a in otherLines:
        factoryFile.write(a)

    factoryFile.close()
