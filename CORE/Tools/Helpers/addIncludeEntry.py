#Add the new header file to the list of includes for the factory
def addInclude(className, sourcePath):
    otherLines = [];
    includesPath = sourcePath + "\\Main\\ComponentTypes.h"
    with open(includesPath, "r") as includesFile:
        lines = includesFile.readlines()

    for a in lines:    
        otherLines.append(a)
        if a.find("Place use defined components here") != -1:
            otherLines.append("#include \"" + className + ".h\"\n")
    includesFile.close()

    includesFile = open(includesPath, "w")

    for a in otherLines:
        includesFile.write(a)

    includesFile.close()
