def genCompImpl(className, sourcePath):
    sourceFile = open(sourcePath + ".cpp", "w+")
    sourceFile.write("#include \"" + className + ".h\"\n\n")
    sourceFile.write(className + "::" + className + "()\n")
    sourceFile.write("{\n\n}\n");
    sourceFile.write("void " + className + "::handle(Event e)\n")
    sourceFile.write("{\n\n}\n")
    sourceFile.write("void " + className + "::getText(Node* def)\n")
    sourceFile.write("{\n\n}\n")
    sourceFile.write("void " + className + "::get_data(DataSource* source)\n")
    sourceFile.write("{\n\n}\n")
    sourceFile.close()
