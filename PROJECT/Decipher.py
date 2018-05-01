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
    StreamXor = ""
    inputsize = len(input)
    keysize = len(key)
    i =0;
    k= 0;
    while i < inputsize:
        if k < keysize:
            StreamXor = StreamXor + (input[i] ^ key[k])
            k = k +1
            i = i +1
        else:
            k = 0


    return StreamXor

#SWAP THE XORED OUTPUT
def Swap(input ,  key):
    begining = 0
    end = len(input) -1

    startptr = input[begining]
    endptr = input[end]

    counter = 0
    keysize = len(key)
    i = 0
    while begining < end:
        counter =counter +1
        if i == keysize:
            i =0;
        for i in range(keysize):
            if (key[i] % 2) != 0:
                input[begining] = endptr
                input[end] = startptr
                end = end -1
                begining = begining + 1

                if begining >= end:
                    return input

                startptr = input[begining]
                endptr = input[end]
                i = i + 1
            else:
                begining = begining + 1

                if begining >= end:
                    return input
                startptr = input[begining]

    return input

if __name__ == "__main__":
    filename = sys.argv[1]
    CipherType = sys.argv[2]
    Efile = open(filename, 'r')


