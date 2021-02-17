import csv
import sys
from shutil import copyfile
import os
cwd = os.getcwd()


# soihelper is called (by sysobs program) with only two things, soi.csv file, and all RTL files (no cpp file)
print( "Number of arguments:", len(sys.argv), "arguments." )
argc = len(sys.argv)

metacommentExample = "/*<--SOI-->*/"

# If file extension == .sv or .v, create copy titled old[filename].sv or old[filename].v (for backup)
for x in range(argc):
    inpFile = str(sys.argv[x])
    print(inpFile)
    fileCopy = "old_" + inpFile
    # The following code can be reused
    if (inpFile.lower()).endswith(('.sv', '.v')):
        copyfile(cwd + "/" + inpFile, cwd + "/" + fileCopy)
        print(fileCopy)

"""

with open('soi.csv') as csvfile:
    csvReader = csv.reader(x, delimiter=',')
    line_count = 0
    for row in csvReader:
        if line_count == 0:
            print(f'Column names are {", ".join(row)}')
            line_count += 1
        else:
            print(f'\t{row[0]} works in the {row[1]} department, and was born in {row[2]}.')
            line_count += 1
    print(f'Processed {line_count} lines.')



# Opens file called '[modulename].v/.sv, scans for every instance of signalname, inserts metacomment before semicolon
def readcsv(moduleName, signalName):


# Same as other readcsv function, but does so only for the specified line. 
def readcsv(moduleName, signalName, line):


"""

