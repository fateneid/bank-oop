#pragma once
#include <iostream>
#include <cstdlib>
#include "clsDate.h"
using namespace std;

class clsUtil
{

public:

	static enum enCharType { SmallLetter = 1, CapitalLetter = 2, SpecialCharacter = 3, Digit = 4, Mix = 5 };

    static void Srand() {
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To) {
		int RandomNumber = rand() % (To + 1 - From) + From;
		return RandomNumber;
	}

	static char GetRandomCharacter(enCharType CharType) {

		if (CharType == enCharType::Mix) {
			CharType = (enCharType)RandomNumber(1, 3);
		}

		switch (CharType)
		{
		case enCharType::SmallLetter:
			return char(RandomNumber(97, 122));
			break;
		case enCharType::CapitalLetter:
			return char(RandomNumber(65, 90));
			break;
		case enCharType::SpecialCharacter:
			return char(RandomNumber(33, 47));
			break;
		case enCharType::Digit:
			return char(RandomNumber(48, 57));
			break;
		defualt:
		    return char(RandomNumber(65, 90));
		    break;

		}

	}

	static string GenerateKey(enCharType CharType, short WordLength, short WordRepeat) {
		string Key = "", Dash = "-";

		for (int i = 1; i <= WordRepeat; i++) {
			for (int k = 1; k <= WordLength; k++) {
				Key += GetRandomCharacter(CharType);
			}
			Key += Dash;
			if (i == WordRepeat - 1) {
				Dash = "";
			}
		}
		return Key;
	}

	static string GenerateWord(enCharType CharType, short WordLength) {

		string Word = "";

		for (int i = 1; i <= WordLength; i++) {

			Word += GetRandomCharacter(CharType);

		}

		return Word;
	}

	static void GenerateKeys(short Number, enCharType CharType, short WordLength, short WordRepeat) {

		for (int i = 1; i <= Number; i++) {
			cout << "Key [" << i << "]: "
				<< GenerateKey(CharType, WordLength, WordRepeat) << endl;
		}
	}

	static void FillArrayWithRandomNumbers(int Array[], int ArrayLenght, int From, int To) {

		for (int i = 0; i < ArrayLenght; i++) {
			Array[i] = RandomNumber(From, To);
		}
	}

	static void FillArrayWithRandomWords(string Array[], int ArrayLength,
		enCharType CharType, short WordLength) {

		for (int i = 0; i < ArrayLength; i++) {
			Array[i] = GenerateWord(CharType, WordLength);
		}
	}

	static void FillArrayWithRandomKeys(string Array[], int ArrayLength, 
		enCharType CharType, short WordLength, short WordRepeat) {

		for (int i = 0; i < ArrayLength; i++) {
			Array[i] = GenerateKey(CharType, WordLength, WordRepeat);
		}
	}

	static void Swap(int& A, int& B) {
		int Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(double& A, double& B) {
		double Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(bool& A, bool& B) {
		bool Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(char& A, char& B) {
		char Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(string& A, string& B) {
		string Temp = A;
		A = B;
		B = Temp;
	}

	static void Swap(clsDate& A, clsDate& B) {
		clsDate Temp = A;
		A = B;
		B = Temp;
	}

	static void ShuffleArray(int Array[], int ArrayLength) {
		for (int i = 0; i < ArrayLength; i++) {
			Swap(Array[RandomNumber(0, ArrayLength - 1)], Array[RandomNumber(0, ArrayLength - 1)]);
		}
	}

	static void ShuffleArray(string Array[], int ArrayLength) {
		for (int i = 0; i < ArrayLength; i++) {
			Swap(Array[RandomNumber(0, ArrayLength - 1)], Array[RandomNumber(0, ArrayLength - 1)]);
		}
	}

	static string EncryptText(string Text, short EncryptionKey) {

		for (int i = 0; i < Text.length(); i++) {
			Text[i] = char((int)Text[i] + EncryptionKey);
		}

		return Text;

	}

	static string DecryptText(string Text, short EncryptionKey) {

		for (int i = 0; i < Text.length(); i++) {
			Text[i] = char((int)Text[i] - EncryptionKey);
		}

		return Text;

	}

	static string Tabs(short NumberOfTabs)
	{
		string t = "";

		for (int i = 1; i <= NumberOfTabs; i++)
		{
			t += "\t";
			cout << t;
		}
		return t;

	}


};

