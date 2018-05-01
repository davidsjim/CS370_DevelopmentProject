import sys

#DECIPHER THE STREAM ALGORTIHM
def DecipherStream(  input , key):

    text = Xor(input, key)
    return text

#DECIPHER THE BLOCK ALGRORITHM
def DecipherBlock(input , key):

    text = Swap(input, key)
    result = Xor(text, key)
    return result




#XOR  FOR STREAM AND BLOCK
def  Xor(input , key):
    inputs = list(input)
    keyvals = list(key)
    StreamXor = ""
    inputsize = len(input)
    keysize = len(key)
    i =0;
    k= 0;
    while i < inputsize:
        if k < keysize:
            StreamXor = StreamXor + chr(ord(inputs[i]) ^ ord(keyvals[k]))
            k = k +1
            i = i +1
        else:
            k = 0


    return StreamXor

#SWAP THE XORED OUTPUT
def Swap(input ,  key):
    ciphertext = list(input)
    begining = 0
    end = len(input) -1
    print(end)

    startptr = ciphertext[begining]
    endptr = ciphertext[end]

    counter = 0
    keysize = len(key)
    print(keysize)
    i = 0
    while begining < end:
        counter =counter +1
        if i == keysize:
            i =0;
        for i in range(keysize):
            print(ord(key[i]))
            if (ord(key[i])% 2) != 0:
                print(input[begining])
                ciphertext[begining] = endptr
                ciphertext[end] = startptr
                end = end -1
                begining = begining + 1

                if begining >= end:
                    return input

                startptr = ciphertext[begining]
                endptr = ciphertext[end]
                i = i + 1
            else:
                begining = begining + 1

                if begining >= end:
                    return ''.join(ciphertext)
                startptr = ciphertext[begining]

    return ''.join(ciphertext)

if __name__ == "__main__":
###READ THE INCOMING FILE FROM THE OTHER MACHINE
    filename = "output"
    keyfile = "key"
    result = ""
    file = open(filename, 'rb')


    Type = file.read(1)
    CipherText = file.read()
    print(CipherText)
###READ THE KEYFILE
    f = open(keyfile, 'r')
    key = f.read()

    if Type == 'B':
        result = DecipherBlock(CipherText, key)
    else:
        result = DecipherStream(CipherText, key)

    print(result)

