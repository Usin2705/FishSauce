def readFile():
	try:
		f = open("isFollow.txt")
		line = f.readline()		
		print(line)
		f.close()
		return line
	except Exception as error:
		print("error reading file")
		print(error)
		
if __name__ == "__main__":
	isFollow = (readFile())
	print (str(isFollow))
	if (isFollow):
		print ("This is True")
	else :
		print ("This is false")