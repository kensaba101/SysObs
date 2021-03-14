import csv
import sys
from shutil import copyfile
import os
import re

cwd = os.getcwd()

# Script functions: Modification of rtl files
# Insert VPI metacomments (as required by verilator)
# 

print( "Number of arguments:", len(sys.argv), "arguments." )
argc = len(sys.argv)

metacomment = "/*<--SOI-->*/"
metacommentVpi = "/*verilator public_flat*/"
metacommentDpi = " "

insertBefore = ";"

# Enable user to use csv files of names other than the default (soi.csv) 
def getCsvName():
    for x in range(argc):
        inpFile = str(sys.argv[x])
        if (inpFile.lower()).endswith(('.csv', '.CSV')):
            return inpFile
    return 'soi.csv'
    

csvFileName = getCsvName()

def soiFirstAppearance(moduleName, soiName): 
    with open(moduleName) as fp: # Open file moduleName
        line = fp.readline() 
        soiLineNum = 0
        
        while line: # Scan (top to EOF) for string match "soiName"
            if(re.search(soiName, line)): # If soiName is found anywhere in line, return current line number
                return soiLineNum
            else: # Else, incrememnt soiLineNum and continue scanning
                line = fp.readline() 
                soiLineNum +=1
        print('No match for SOI name "', soiName, '" in file "', modulename, '"')

def insertMetacomment(moduleName, lineNum, insertBefore, metacomment):
    #readFile  = open(cwd + '/' + moduleName, "r") # Open file with intention to get lines
    readFile  = open(moduleName, "r")
    newFileData = ""
    lineCount = 0
    for line in readFile:
        if (lineCount == lineNum):
            strippedLine = line.strip('\n')
            newLine = strippedLine.replace(";", (metacomment + insertBefore))
            newFileData += newLine + "\n"
            lineCount += 1
        else:
            newFileData += line
            lineCount += 1
    readFile.close()

    #writeFile = open(cwd + '/' + moduleName, "w")
    writeFile = open(moduleName, "w")
    writeFile.write(newFileData)
    writeFile.close() # Close file

# If file extension == .sv or .v, create copy titled old[filename].sv or old[filename].v (for backup)
for x in range(argc):
    inpFile = str(sys.argv[x])
    print(inpFile)
    fileCopy = "old_" + inpFile
    # The following code can be reused
    if (inpFile.lower()).endswith(('.sv', '.v')):
        copyfile(cwd + "/" + inpFile, cwd + "/" + fileCopy)
        print(fileCopy)

# RTL file modification (metacomment insertion)
with open(cwd + '/' + csvFileName) as csvFile:
    csvReader = csv.reader(csvFile, delimiter=',')
    lineCount = 0; 
    for row in csvReader: #while (!EOF), NTS: rows indexed from 0 not 1
        moduleName = row[0]
        print(moduleName)
        soiName = row[1]
        print(soiName)
        if (len(row) != 3): 
            lineNum = soiFirstAppearance(moduleName, soiName) #function might return wrong line (eg if user uses soiname in a comment in RTL file)
            lineCount +=1
        else:
            lineNum = int(row[2])
            print(lineNum)
            lineCount +=1
        insertMetacomment(moduleName, lineNum, insertBefore, metacomment)