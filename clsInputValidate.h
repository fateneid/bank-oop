#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsUtil.h"
#include <string>
using namespace std;

class clsInputValidate
{

public:

	static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n") {

		int Number;

		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		float Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n") {

		double Number;

		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}
	
	static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n") {

		int Num = ReadIntNumber();

		while (!IsNumberBetween(Num, From, To)) {
			cout << ErrorMessage;
			Num = ReadIntNumber();
		}
		return Num;
	}

	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n") {

		short Num = ReadIntNumber();

		while (!IsNumberBetween(Num, From, To)) {
			cout << ErrorMessage;
			Num = ReadIntNumber();
		}
		return Num;
	}

	static float ReadFloatNumberBetween(float From, float To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		float Number = ReadFloatNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadDblNumber();
		}
		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n") {

		double Num = ReadIntNumber();

		while (!IsNumberBetween(Num, From, To)) {
			cout << ErrorMessage;
			Num = ReadIntNumber();
		}
		return Num;
	}

	static bool IsNumberBetween(short Num, short From, short To) {
		return (Num >= From && Num <= To);
	}

	static bool IsNumberBetween(int Num, int From, int To) {
		return (Num >= From && Num <= To);
	}

	static bool IsNumberBetween(float Num, float From, float To) {
		return (Num >= From && Num <= To);
	}

	static bool IsNumberBetween(double Num, double From, double To) {
		return (Num >= From && Num <= To);
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To) {

		if (clsDate::CompareDate(From, To) == clsDate::enCompareDate::After) {
			clsUtil::Swap(From, To);

		}

		return !(clsDate::CompareDate(Date, From) == clsDate::enCompareDate::Before ||
			clsDate::CompareDate(Date, To) == clsDate::enCompareDate::After);

	}

	static bool IsValidDate(clsDate Date) {

		return clsDate::IsAValidDate(Date);

	}

	static string ReadString(string Message = "") {

		string S1 = "";
		cout << Message;
		getline(cin >> ws, S1);
		return S1;

	}

	static bool AskYesNo(string Message) {
		char Answer;
		cout << Message;
		cin >> Answer;
		return toupper(Answer) == 'Y' ? true : false;
	}

};

