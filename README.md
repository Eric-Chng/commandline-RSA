RSA encryption program

type "make" to create executable
Must provide 2 sufficiently large primes for program to work
run by typing "./rsa p q" where p and q are said primes

In program, type "EXIT" or an invalid command to quit
DECRYPT [input] [output] Opens the file at [input], reads the contents of the file, decrypts the message, 
and overwrites the contents of the file at [output] with the decrypted message.
ENCRYPT [filename] [n] [message] Creates/overwrites the file at the specified path, writing an encrypted version of [message], 
which is a string of lowercase letters a-z and spaces (but no tabs or newlines). [n] is an integer which will be used in the encryption process.

CONDITIONS
p and q must be large enough such that p*q > 27
p and q must be able to fit inside a long
messages encrypted can only contain spaces and undercase letters 