#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

void populateCharacterList(vector<char> &passedInVector);
const void printCharacterList (const vector<char> &passedInVector);
bool isOdd(int value);
int decodeCharacter(int privateKey, int public_n_value, int encodedChar);
int convertToChar(int numberDecoded);
void loadRSAEncryptedMessage(vector<int> &RSA_Digits);

int main() {
// p = 11, q = 17 phi = 160 d = 89
	vector<char>listOfCharacters;
	vector<int> encoded_RSA_Digits;
	int decodedNumber = 0;

	populateCharacterList(listOfCharacters);
	//printCharacterList(listOfCharacters);
	
	loadRSAEncryptedMessage(encoded_RSA_Digits);

	for (int i = 0; i < encoded_RSA_Digits.size(); i++) {
		decodedNumber = decodeCharacter(89, 187, encoded_RSA_Digits.at(i));
		cout << listOfCharacters.at(convertToChar(decodedNumber));
	}

	cout << endl << endl;

	for (int i = 0; i < encoded_RSA_Digits.size(); i++) {
		decodedNumber = decodeCharacter(89, 187, encoded_RSA_Digits.at(i));
		
		cout << decodedNumber << " ";

		if ((i+1) % 7 == 0) {
			cout << endl;
		}
	}
//	cout << endl << "Decoded Number: " << decodedNumber << endl;

//	cout << endl << listOfCharacters.at(convertToChar(decodedNumber)) << endl;
 
	

	return 0;
}

int decodeCharacter(int privateKey, int public_n_value, int encodedChar) {
	
	int producedMultiplier = 1;

	while(privateKey != 1) {
		if (isOdd(privateKey)) {
			privateKey = privateKey - 1;
			producedMultiplier = producedMultiplier * encodedChar;
		}

		if(producedMultiplier > public_n_value) {
			producedMultiplier = producedMultiplier % public_n_value;
		}

		if (encodedChar > public_n_value) {
			encodedChar = encodedChar % public_n_value;
		}	

		privateKey = privateKey / 2;
		encodedChar = pow(encodedChar, 2);
		encodedChar = encodedChar % public_n_value;
	}

	return (encodedChar * producedMultiplier) % public_n_value;
}

int convertToChar(int numberDecoded) {
	return numberDecoded - 3;
}

bool isOdd(int value) {
	
	if ((value % 2) == 1) {
		return true;
	}	
	else {
		return false;
	}
}

void loadRSAEncryptedMessage(vector<int> &RSA_Digits) {
	ifstream inFS;
	int temp = 0;

	inFS.open("encodedText.txt");

	if(!inFS.is_open()) {
		exit(-1);
	}

	while (inFS >> temp) {
		RSA_Digits.push_back(temp);
	}

	inFS.close();
}


void populateCharacterList(vector<char> &passedInVector) {
	
	char tempChar = 'a';
	
	for (int i = 0; i < 26; i++){
		passedInVector.push_back(tempChar);
		tempChar = tempChar + 1;
	}

	passedInVector.push_back(' ');
	passedInVector.push_back('\"');
	passedInVector.push_back('.');

	// 28 characters and indexes meaning the map conversion is character minus 3 to get the valid index.

}

const void printCharacterList (const vector<char> &passedInVector) {
	for (int i = 0; i < passedInVector.size(); i++) {
		cout << passedInVector.at(i) << endl;
	}
	
	cout << endl << passedInVector.size() - 1 << endl;

}