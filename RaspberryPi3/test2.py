def writeFile(isFollow):
	try:
		f = open("isFollow.txt", "w")
		f.write(str(isFollow))
		f.close()
		print ("Write file successfully")
	except Exception as error:
		print("error writing file")
		print(error)
if __name__ == "__main__":
	writeFile(False)