/*
Author:			My Tran
Filename:		Encryptor.h
Description:	Ths file provides the declarations the methods and members of the Encryptor class. Encryption employs
combination of methodologies from the affine cipher method, the vigenere cipher method, and row transposition to create
ciphertext from plaintext.
*/
#include<iostream>
#include<string>
#include<vector>
#include<stdlib.h>

class Encryptor
{
	public:
		/*
		Purpose:		Creates instance of default Encryptor object.
		Pre-condition:	None
		Post-condition:	None
		*/
		Encryptor();	//Default constructor

		/*
		Purpose:		Gets the values needed from the user (plaintext, keyNum, keyPhrase)
		Pre-condition:	None
		Post-condition:	None
		*/
		void initialize();

		/*
		Purpose:		Apply product encryption to plaintext to receive ciphertext.
		Pre-condition:	Plaintext, keyNum, and keyPhrase must have values
		Post-condition:	Plaintext, keyNum, and keyPhrase are cleared, and ciphertext contains result of encryption
		*/
		void encrypt();

		/*
		Purpose:		Prints ciphertext to console.
		Pre-condition:	None
		Post-condition:	ciphertext is displayed on console.
		*/
		void displayCiphertext();

		/*
		Purpose:		Prints plaintext to console.
		Pre-condition:	None
		Post-condition:	ciphertext is displayed on console.		
		*/
		void displayPlaintext();

		/*
		Purpose:		Reverse the row transposition and affine cipher on ciphertext to receive plaintext.
		Pre-condition:	ciphertext is not empty
		Post-condition:	ciphertext, keyNum and keyPhrase are cleared. plaintext contains the result of the decryption
		*/
		void decrypt();

		/*
		Purpose:		Provides interaction menu for the user to utilize the encryption.
		Pre-condition:	None
		Post-condition:	Method has performed actions specified by user.
		*/
		void start();
	private:
		//private data members
		std::string plaintext;	//stores plaintext string to be encrypted or resulting from decryption
		std::string ciphertext;	//stores ciphertext string from encyption or to be decryptedr
		std::string keyPhrase;	//key phrase or word used for vigenere method as part of affine cipher method
		int keyNum;	//numerical key used for affine cipher method
		std::vector<std::vector<char>> transposeMatrix;	//matrix used to store elements in the row by row
		std::vector<std::vector<char>> cipherMatrix;	//row transposition matrix of transpose matrix

		/*
		Purpose:		Determines if a character value is an alphabetical letter character.
		Pre-condition:	Takes a input character argument.
		Post-condition:	Returns true if upper or lower case letter. False otherwise.
		*/
		bool isLetter(char);

		/*
		Purpose:		Calculates the least square dimension of a matrix to fit a given number of elements.
		Pre-condition:	Takes integer argument representing a number of elements to fit in a square
		Post-condition:	Returns integer representing least square dimension of matrix
		*/
		int getMatrixSize(int);

		/*
		Purpose:		Calculates the modular multiplicative inverse of a given number for (mod 26)
		Pre-condition:	Takes integer argument representing the value of which the inverse is being calculated.
		Post-condition:	Returns inverse.
		*/
		int calcModInverse(int);

		/*
		Purpose:		Applies affine cipher encryption on plaintext and stores it in ciphertext.
		Pre-condition:	Plaintext, keyNum, and keyPhrase must have values
		Post-condition:	Result stored in ciphertext.
		*/
		void affine();

		/*
		Purpose:		Fill a square matrix with ciphertext.
		Pre-condition:	ciphertext must have data
		Post-condition:	transposeMatrix is filled with letters of ciphertext.
		*/
		void fillMatrix();

		/*
		Purpose:		Reorder transposeMatrix using user input.
		Pre-condition:	transposeMatrix has input.
		Post-condition:	Reordered transpose matrix is stored in ciphermatrix
		*/
		void reOrderMatrix();

		/*
		Purpose:		Get plaintext input from the user.
		Pre-condition:	None
		Post-condition:	plaintext member contains user input
		*/
		void getPlaintext();

		/*
		Purpose:		Get ciphertext input from the user.
		Pre-condition:	None
		Post-condition:	ciphertext member contains user input
		*/
		void getCiphertext();

		/*
		Purpose:		Get keyPhrase input from the user.
		Pre-condition:	None
		Post-condition:	keyPhrase member contains user input
		*/
		void getKeyPhrase();

		/*
		Purpose:		Get keyNum input from the user.
		Pre-condition:	None
		Post-condition:	keyNum member contains user input
		*/
		void getKeyNum();

		/*
		Purpose:		Applies affine cipher inversion on ciphertext and stores it in plaintext.
		Pre-condition:	ciphertext, keyNum, and keyPhrase must have values
		Post-condition:	Result stored in plaintext.
		*/
		void invertAffine();

		/*
		Purpose:		Given string, remove spaces and convert upper case to lower case
		Pre-condition:	Takes string argument being the string we want to format
		Post-condition:	Returns formatted string.
		*/
		std::string formatInput(std::string);

		/*
		Purpose:		Rebuilds matrix from filling affine ciphertext row by row before reordering.
		Pre-condition:	cipherMatrix is filled
		Post-condition:	Result is stored in transposeMatrix
		*/
		void reconstructMatrix();

		/*
		Purpose:		Reset all member values.
		Pre-condition:	None
		Post-condition:	All members are cleared.
		*/
		void reset();

		/*
		Purpose:		Reset all member values.
		Pre-condition:	None
		Post-condition:	Instructions for start are printed to console
		*/
		void displayInstructions();
		
};