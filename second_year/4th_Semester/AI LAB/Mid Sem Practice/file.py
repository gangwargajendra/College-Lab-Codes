file_object = open("file_data.txt", 'r')
if(file_object):
    print("file opened successfully.")
else:
    print("file does not open successfully")

# this will read the data once and stores it into str
#str = file_object.read()
#print(str)

line = file_object.readline()
i = 0
while line:
    print(i, line.strip())
    line = file_object.readline()
    i = i+1

file_object.close()

