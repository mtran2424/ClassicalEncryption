# ClassicalEncryption
A C++ program that allows you to encrypt and decrypt secret messages using classical encryption methods. A combination of the affine, Vigenere, and row transposition cipher methods are employed the encrypt or decrypt a given text.
 
Getting Started:
---------------------------------------------------------------------------------------------------------------------
To run the console app, you must have a C++ compiler installed (Preferably MS Visual Studio for most optimal and compatible). From here, the program files can be placed into a new project and compiled.

Cipher Methods:
---------------------------------------------------------------------------------------------------------------------
The encryption scheme is as follows:

- User inputs a keyword of some length, and a non-zero integer less than 26, with no common factors with 26, greater than 1.

- Using the integer as a numerical key a, plaintext character P, and the corresponding character in the key word b, in the equation C = (aP + b) mod 26, we get ciphertext character C. (Combination of Vigenere -> from key word, and affine -> from equation and a)

- Repeat this for the entire message string.

- Insert ciphertext string into matrix of size n x n, where in is the least square that fits all length of ciphertext elements.

- Prompt user for number combination using integers from 0 - (n - # incomplete rows) in an order of their choosing.

- Rearrange rows, and get new ciphertext from new columns of the rearranged matrix. (variation of row transposition)

Decryption involves inverting those steps above given the correct keys.

Usage:
---------------------------------------------------------------------------------------------------------------------
Once the console app is open, you will be greeted with a screen that looks like the following:



Text Encryption Tool
---------------------------------------------------------------------------------------------------------------------
Description: The following program encrypts and decrypts desired texts using operations commonly used in classical
cryptography (substitution, transposition, product).

Directions: Given the options below, enter a number to perform the corresponding action. Encrypting clears plaintext.
Decrypting clears ciphertext. You MUST remember your key values. The program will NOT remember for you. Save your
ciphertexts if you wish to decrypt them later!
1 - encrypt a plaintext
2 - decrypt a ciphertext
3 - display ciphertext
4 - display plaintext
0 - terminate program
---------------------------------------------------------------------------------------------------------------------
Please a specified code and press enter:



Follow the prompts accordingly with the directions. Upon encryption, the stored plaintext is cleared and the ciphertext screen displays the ciphertext. Upon decryption, the plaintext is displayed from resulting decryption and the ciphertext is cleared.


Conclusion:
---------------------------------------------------------------------------------------------------------------------
This app is by no means secure enough for modern standards of encryption breaking and should not be trusted to any official capacity. It is purely for educational purposes to demonstrate the executing of classical encryption techniques.
