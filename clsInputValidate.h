#pragma once
#include <iostream>
#include "clsDate.h"
#include "clsUtil.h"
#include <string>
using namespace std;

class clsInputValidate
{

public:

	template <typename T>
	static T ReadNumber(string ErrorMessage = "Invalid Number, Enter again\n") {

		T Number;

		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}
	
	template <typename T>
	static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, Enter again:\n") {

		T Num = ReadNumber<T>();

		while (!IsNumberBetween(Num, From, To)) {
			cout << ErrorMessage;
			Num = ReadNumber<T>();
		}
		return Num;
	}
	
	template <typename T>
	static T IsNumberBetween(T Num, T From, T To) {
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
		return toupper(Answer) == 'Y';

	}

};

