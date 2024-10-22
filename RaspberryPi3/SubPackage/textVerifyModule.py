def textVerify(text, meanings, callBackTrue = None, targs=(), callBackFalse = None, fargs=()):
    text = text.lower().split()
    for word in text:
        if type(meanings) is str:
            if meanings.lower()==word:
                if callBackTrue:
                    callBackTrue(*targs)
                return True
            
        else:
            for meaning in meanings:
                if meaning.lower()==word:
                    if callBackTrue:
                        callBackTrue(*targs)
                    return True
            
    return False

def test():    
    error = 0
    i = 1
    
    print("Test case {:02} : Hello world : world.".format(i))
    expected = True
    result = textVerify("Hello world", "world")
    if (expected!=result): 
        error=error+1
        print("Error")
    i+=1
    
    print("Test case {:02} : Hello World : world.".format(i))
    expected = True
    result = textVerify("Hello World", "world")
    if (expected!=result): 
        error=error+1
        print("Error")
    i+=1
    
    print("Test case {:02} : HelloWorld : world.".format(i))
    expected = False
    result = textVerify("HelloWorld", "world")
    if (expected!=result): error=error+1
    if (expected!=result): 
        error=error+1
        print("Error")
    i+=1
    
    print("Test case {:02} : Hello world : world.".format(i))
    expected = True
    result = textVerify("Hello world", "World")
    if (expected!=result): 
        error=error+1
        print("Error")
    i+=1
    
    print("Test case {:02} : Says : [Says, Say]".format(i))
    expected = True
    result = textVerify("Says", ["Says", "say"])
    if (expected!=result): 
        error=error+1
        print("Error")
    i+=1
        
    print("Total errors: {}".format(error))

if __name__ == "__main__":
	test()