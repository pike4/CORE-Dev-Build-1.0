def genCompClassDef(className, sourcePath):
    headerFile = open(sourcePath + ".h", "w+")
    headerFile.write("#pragma once\n")
    headerFile.write("#include \"Component.h\"\n\n")
    headerFile.write("class " + className + " : public Component\n")
    headerFile.write("{\n")
    headerFile.write("public:\n")
    headerFile.write("\t" + className + "();\n\n")
    headerFile.write("\tvirtual void handle(Event e);\n");
    headerFile.write("\tvirtual void get_data(DataSource* source);\n");
    headerFile.write("\tvirtual void getText(Node* def);\n");
    headerFile.write("};\n")
    headerFile.close()
