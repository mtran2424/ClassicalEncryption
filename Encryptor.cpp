/*
Author:			My Tran
Filename:		Encryptor.cpp
Description:	This file implements the header file Encryptor.h providing the definitions for the methods of the encryptor class.
*/
#include "Encryptor.h"

const int MIN_KEY_PHRASE_LENGTH = 10;	//minimum length parameter of key phrase
const int UPPER_TO_LOWER_CASE_GAP = 32;	//distance between upper to lower in ascii table
const int ASCII_VAL_LOWER_A = 97;	//ascii value for lowercase a

Encryptor::Encryptor()
{
	//initialize all PDMs
	plaintext = "";
	ciphertext = "";
	keyPhrase = "";
	keyNum = NULL;
}

void Encryptor::getPlaintext()
{
	plaintext = "";

	//read in plaintext from user
	std::cout << "Please input the message you wish to encrypt:\n";

	std::string input = "";
	std::cin.ignore();
	std::getline(std::cin, input);

	//Remove spaces
	for (size_t i = 0; i < input.length(); i++)
	{
		if (isLetter(input[i]) || input[i] == ' ')
		{
			//converting upper case to lower case letters makes encryption simpler
			if (input[i] >= 'A' && input[i] <= 'Z')
			{
				input[i] += UPPER_TO_LOWER_CASE_GAP;
			}

			//removing spaces from the text decreases ability to guess based on word length
			if (input[i] != ' ')
			{
				plaintext += input[i];
			}
		}
		else//only spaces and alphabet symbols are accepted as input for the above reasons
		{
			std::cout << "Invalid character... Please limit your input to letters in the alphabet and spaces.\n";
			
			//user is allowed to retry if their input is invalid is is not allowed to continue until input is valid
			getPlaintext();

			i = input.length();
		}
	}
}

void Encryptor::getCiphertext()
{
	ciphertext = "";

	//read in ciphertext from user
	std::cout << "Please input the message you wish to decrypt:\n";

	std::string input = "";
	std::cin.ignore();
	std::getline(std::cin, input);

	//Remove spaces
	for (size_t index = 0; index < input.length(); index++)
	{
		//encryption only uses lower cases characters
		if (input[index] >= 'A' && input[index] <= 'Z')
		{
			input[index] += UPPER_TO_LOWER_CASE_GAP;
		}

		ciphertext += input[index];
	}
}

void Encryptor::getKeyPhrase()
{
	//read in key phrase or word from user
	std::cout << "Please input a key word or phrase that is at least " << MIN_KEY_PHRASE_LENGTH << " characters long: \n";

	std::string input;
	std::getline(std::cin, input);

	//keeping it ten characters minimum 
	while (input.length() < MIN_KEY_PHRASE_LENGTH)
	{
		std::cout << "Please enter a longer key word or phrase! Your security depends on it!\n";
		std::getline(std::cin, input);
	}

	//Remove spaces to perform encryption algorithm
	for (size_t i = 0; i < input.length(); i++)
	{
		if (isLetter(input[i]) || input[i] == ' ')
		{
			//converting upper case to lower case letters makes encryption simpler
			if (input[i] >= 'A' && input[i] <= 'Z')
			{
				input[i] += UPPER_TO_LOWER_CASE_GAP;
			}

			//removing spaces from the text decreases ability to guess based on word length
			if (input[i] != ' ')
			{
				keyPhrase += input[i];
			}
		}
		else//only spaces and alphabet symbols are accepted as input for the above reasons
		{
			std::cout << "Invalid character... Please limit your input to letters in the alphabet and spaces.\n";
			
			//user is allowed to retry if their input is invalid is is not allowed to continue until input is valid
			getKeyPhrase();
			
			break;
		}
	}
}

void Encryptor::getKeyNum()
{
	//keyNum = a for C = (aP + b)
	//The conditions limit us to 11 valid key options but going over 26 doesn't make sense and there is a 
	//higher chance of the encryption failing when the a key has a common factor with 26 other than 1
	std::cout << "Choose a positive non-zero integer less than 26 that does not share a GCF with 26, greater than 1\n";
	std::cout << "REMEMBER THIS KEY (Reminder: 26 only has the factors 1, 2, 13, 26):\n";

	//Read in number that is part of the cipher key

	std::cin >> keyNum;

	while ((keyNum % 2 == 0) || (keyNum % 13 == 0) || (keyNum % 26 == 0) || (keyNum >= 26) || (keyNum <= 0 || !std::cin))
	{
		std::cout << "This input does not meet the requirements for a key number. Please try again...\n";

		std::cin.clear();
		std::cin.ignore();
		std::cin >> keyNum;
	}
}

void Encryptor::initialize()
{
	//Functions below grab necessary values for encryption
	getPlaintext();

	getKeyPhrase();

	getKeyNum();
}

void Encryptor::decrypt()
{
	if (!ciphertext.empty())
	{
		//Recreate the matrix from the row transposition algorithm before the reordering. Result is stored in transposeMatrix
		reconstructMatrix();

		//Concatenating the rows gives the ciphertext from the affine encryption
		ciphertext = "";

		//From each row, and each element in each row, concatenate the rows from top to bottom
		for (std::vector<char> g : transposeMatrix)
		{
			for (char h : g)
			{
				if (h != '\0')
				{
					ciphertext += h;
				}
			}
		}

		//The correct key number is required for the decryption to work
		std::cout << "Please input the keyNum for this ciphertext:\n";
		try
		{
			std::cin >> keyNum;
		}
		catch (std::exception ex)
		{
			std::cout << "Error: Unexpected input";
			std::exit(0);
		}

		//Undoing the affine results in the unencrypted plaintext.
		invertAffine();

		//Clearing members used in decryption so saved values can't be used unless they are input again
		cipherMatrix.clear();
		transposeMatrix.clear();
		ciphertext.clear();
		keyNum = 0;
	}
	else
	{
		std::cout << "Error: nothing to decrypt.\n";
	}
}

void Encryptor::affine()
{
	//substitution of plaintext to ciphertext uses affine method
	ciphertext = std::string(plaintext.length(), ' ');

	//key phrase acts as part of affine cipher to apply vigenere cipher method
	for (size_t i = 0; i < plaintext.length(); i++)
	{
		//C = (a*P + b)mod 26 where a = keyNum and b = char at keyPhrase[i] 
		int cipher = keyNum * ((int)plaintext[i] - 97);
		cipher += ((int)keyPhrase[i % keyPhrase.length()] - 97);
		cipher %= 26;

		//append encrypted character to cyphertext
		ciphertext[i] = (char) (cipher + 97);
	}
}

void Encryptor::invertAffine()
{
	//phrase that the user inputs must match the one used in encryption for decyption to work
	std::string phraseAttempt = "";
	std::cout << "Please input the key phrase or word for this cipher text:\n";

	//remove spaces from input and make all text lower casse
	std::string formatting;
	std::cin.ignore();
	std::getline(std::cin, formatting);
	phraseAttempt = formatInput(formatting);

	//calculate modular multiplicative inverse of key number
	int keyNumInverse = calcModInverse(keyNum);

	//using the ciphertext, inverse of keyNum, and given word or phrase, undo affine cipher
	plaintext = std::string(ciphertext.length(), ' ');
	for (size_t i = 0; i < ciphertext.length(); i++)
	{
		//C = (a*P + b)mod 26 where a = keyNum and b = char at keyPhrase[i] 
		//P = (a^-1)(C - b)mod 26 where a^-1 = multiplicative inverse and b = char at pos i of key phrase
		//C
		int decipher = (((int)ciphertext[i] - 97));
		//C-b
		decipher -= (((int)phraseAttempt[i % phraseAttempt.length()]) - 97);
		//(a^-1)(C - b)
		decipher *= keyNumInverse;

		//(a^-1)(C - b)mod 26
		//account for negative number modulus
		while (decipher < 0)
		{
			decipher += 26;
		}

		decipher = decipher % 26;

		//append encrypted character to cyphertext
		plaintext[i] = (char)(decipher + 97);
	}
}

void Encryptor::reconstructMatrix()
{
	int matrixSize = getMatrixSize(ciphertext.length());	//least square dimension of matrix given length of cipher text
	int missingElements = ((matrixSize * matrixSize) - ciphertext.length());	//num elements missing from full square
	int occupiedRows = matrixSize - (missingElements / matrixSize);	//Rows that have elements
	int fullColumns = matrixSize - (missingElements % matrixSize);	//columns that aren't missing elements

	//elements don't always fill matrix to bottom row so create matrix with rows that get filled
	cipherMatrix.resize(occupiedRows, std::vector<char>(matrixSize, '\0'));

	//fill matrix by column, accounting for the incomplete columns resulting from populating by row during encryption
	for (int c = 0, i = 0, b = occupiedRows; c < matrixSize; c++)
	{
		if (c >= fullColumns)
		{
			b = occupiedRows - 1;
		}

		for (int r = 0; r < b && i < ciphertext.length(); r++, i++)
		{
			cipherMatrix[r][c] = ciphertext[i];
		}
	}

	//Get order the matrix was rearranged by to get original matrix
	std::cout << "Please enter the " << occupiedRows - 1 << " number key combination for this cipher:\n";

	//Put the rows back in order
	transposeMatrix.resize(occupiedRows, std::vector<char>(matrixSize, '\0'));
	for (int i = 0, f = 0; i < occupiedRows - 1; i++)
	{
		//catch incompatible datatype
		std::cin.clear();
		std::cin >> f;

		//prevent out of bound indices
		if (f >= occupiedRows - 1 || f < 0 || !std::cin)
		{
			std::cout << "Error: invalid input...\n";
			i--;
		}
		else//in the original matrix, the row at f, corresponds to the next row of the cipherMatrix from top to bottom
		{
			transposeMatrix[f] = cipherMatrix[i];
		}
		//get bottom row which may or may not be incomplete
		transposeMatrix[occupiedRows - 1] = cipherMatrix[occupiedRows - 1];
	}
}

void Encryptor::fillMatrix()
{
	int matrixSize = getMatrixSize(ciphertext.length());	//least square dimension of matrix given number of elements
	int missingElements = ((matrixSize * matrixSize) - ciphertext.length());	//num elements missing from full square
	int occupiedRows = matrixSize - (missingElements / matrixSize);		//number of rows in matrix w/ elements

	//size of matrix is n*n such that n^2~ ciphertext length
	transposeMatrix.resize(occupiedRows, std::vector<char> (matrixSize, '\0'));

	//populate the matrix with the encrypted text row by row from left to right
	for (int r = 0, n = 0; r < matrixSize; r++)
	{
		for (int c = 0; n < ciphertext.length() && c < matrixSize; c++, n++)
		{
			transposeMatrix[r][c] = ciphertext[n];
		}
	}
}

void Encryptor::reOrderMatrix()
{
	int matrixSize = getMatrixSize(ciphertext.length());	//least square dimension of matrix given number of elements
	int missingElements = ((matrixSize * matrixSize) - ciphertext.length());	//num elements missing from full square
	int occupiedRows = matrixSize - (missingElements / matrixSize);		//number of rows in matrix w/ elements

	//The order the user enters determines the order the rows are stacked and rearranged
	std::cout << "Please enter the numbers from 0 to " << occupiedRows - 2 << " in any order using each number only once.\n";
	std::cout << "You must remember the order! Enter in a space separated list:\n";

	//vector list tracks input to ensure combination is distinct
	std::vector<bool> picked(matrixSize, false);

	//new matrix is made with row order specified by user
	cipherMatrix.resize(occupiedRows, std::vector<char>(matrixSize, ' '));


	for (int i = 0, j = 0; i < occupiedRows - 1; i++)
	{
		//Read in number that is part of the cipher key
		
		std::cin.clear();
		std::cin >> j;

		//prevent index out of bounds
		if (j >= occupiedRows - 1 || j < 0 || !std::cin)
		{
			std::cout << "Error: invalid input...\n";
			i--;
		}
		else if (picked[j])//prevent duplicate input in reordering of matrix
		{
			std::cout << "Error: duplicate input...\n";
			i--;
		}
		else//the next row of the cipher matrix gets the row of the original at row j
		{
			picked[j] = true;
			cipherMatrix[i] = transposeMatrix[j];
		}
	}
	//fill the last row which may or may not be full
	cipherMatrix[occupiedRows - 1] = transposeMatrix[occupiedRows - 1];

}

void Encryptor::encrypt()
{
	if (!plaintext.empty())
	{
		//first encypt plaintext with affine
		affine();

		//Populate matrix with encrypted string
		fillMatrix();
		
		//Form row swapped matrix
		reOrderMatrix();

		//create ciphertext with columns of matrix in transpose order
		for (size_t c = 0, a = 0; c < cipherMatrix[0].size(); c++)
		{
			for (size_t r = 0; r < cipherMatrix.size() && a < ciphertext.length() && cipherMatrix[r][c] != '\0'; r++, a++)
			{
				ciphertext[a] = cipherMatrix[r][c];
			}
		}

		//clear members used so that they cant be reused
		cipherMatrix.clear();
		transposeMatrix.clear();
		plaintext.clear();
		keyNum = 0;
	}
	else
	{
		std::cout << "Error: nothing to encrypt.\n";
	}
}

bool Encryptor::isLetter(char input)
{
	return ((input >= 'A' && input <= 'Z') || (input >= 'a' && input <= 'z'));
}

int Encryptor::getMatrixSize(int elements)
{
	//finds the closest square dimension a matrix with ciphertext length elements
	int dimension = 1;

	//dimension^2 should be the square that is just big enough to fit all elements
	while (dimension * dimension < elements)
	{
		dimension++;
	}

	return dimension;
}

void Encryptor::displayCiphertext()
{
	std::cout << "Ciphertext:\n" << ciphertext << "\n";
}

void Encryptor::displayPlaintext()
{
	std::cout << "Plaintext:\n" << plaintext << "\n";
}

int Encryptor::calcModInverse(int input)
{
	int inverse = 0;

	//find the number such that number * input mod 26 results in 1
	while (((inverse * input) % 26) != 1)
	{
		inverse++;
	}

	return inverse;
}

std::string Encryptor::formatInput(std::string input)
{
	std::string output = "";
	
	for (size_t i = 0; i < input.length(); i++)
	{
		//make all upper case letters lower case
		if (input[i] >= 'A' && input[i] <= 'Z')
		{
			input[i] += 32;
		}

		//remove spaces
		if (input[i] != ' ')
		{
			output += input[i];
		}
	}

	return output;
}

void Encryptor::reset()
{
	//clear all member data
	ciphertext.clear();
	plaintext.clear();
	keyPhrase.clear();
	keyNum = 0;
	cipherMatrix.clear();
	transposeMatrix.clear();
}

void Encryptor::displayInstructions()
{
	std::cout << "Text Encryption Tool\n";
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
	std::cout << "Description: The following program encrypts and decrypts desired texts using operations commonly used in classical\n";
	std::cout << "cryptography (substitution, transposition, product).\n\n";
	std::cout << "Directions: Given the options below, enter a number to perform the corresponding action. Encrypting clears plaintext.\n";
	std::cout << "Decrypting clears ciphertext. You MUST remember your key values. The program will NOT remember for you. Save your\n";
	std::cout << "ciphertexts if you wish to decrypt them later!\n";
	std::cout << "1 - encrypt a plaintext\n";
	std::cout << "2 - decrypt a ciphertext\n";
	std::cout << "3 - display ciphertext\n";
	std::cout << "4 - display plaintext\n";
	std::cout << "0 - terminate program\n";
	std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
}

void Encryptor::start()
{
	int action = -1;
	//loop keeps user in the program menu until terminate input is given
	while (action != 0)
	{
		//print the instructions to the screen
		displayInstructions();

		//prompt user to enter the action they wish to take
		std::cout << "Please a specified code and press enter:\n";
		std::cin >> action;

		//validate the input type
		while (!std::cin)
		{
			std::cout << "Error: Unexpected input. Please try again...\n";

			std::cin.clear();
			std::cin.ignore();
			std::cin >> action;
		}

		//provides for the actions given a numerical input
		switch (action)
		{
			//encrypt
		case 1:
			system("CLS");
			std::cout << "Encryption:\n";
			initialize();
			encrypt();
			system("PAUSE");
			system("CLS");
			break;
			//decrypt
		case 2:
			system("CLS");
			std::cout << "Decryption:\n";
			getCiphertext();
			decrypt();
			system("PAUSE");
			system("CLS");
			break;
			//view cipher
		case 3:
			system("CLS");
			displayCiphertext();
			system("PAUSE");
			system("CLS");
			break;
			//view plaintext
		case 4:
			system("CLS");
			displayPlaintext();
			system("PAUSE");
			system("CLS");
			break;
			//terminate
		case 0:
			system("CLS");
			std::cout << "Terminating program...\n";
			break;
		default:
			std::cout << "Error: No such action. Please try again...";
			break;
		}
	}

}