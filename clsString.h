#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsString
{

private:
	string _Value;
	
public:

	clsString() {
		_Value = "";
	}

	clsString(string Value) {
		_Value = Value;
	}

	void SetValue(string Value) {
		_Value = Value;
	}

	string GetValue() {
		return _Value;
	}

	__declspec(property(get = GetValue, put = SetValue)) string Value;


	static short Length(string S) {
		return S.length();
	}

	short Length() {
		return Length(_Value);
	}

	/* :: [^*^] ::  */

	static void PrintFirstLetterOfEachWord(string MyString) {
		bool IsFirstLetter = true;

		for (short i = 0; i <= MyString.length(); i++) {
			if (MyString[i] != ' ' && IsFirstLetter) {
				cout << MyString[i] << endl;
			}
			IsFirstLetter = (MyString[i] == ' ' ? true : false);

		}

	}

	void PrintFirstLetterOfEachWord() {
		return PrintFirstLetterOfEachWord(_Value);
	}

	/* :: [^*^] ::  */

	static string UpperFirstLetterOfEachWord(string MyString) {
		bool IsFirstLetter = true;

		for (short i = 0; i < MyString.length(); i++) {
			if (MyString[i] != ' ' && IsFirstLetter) {
				MyString[i] = toupper(MyString[i]);
			}

			IsFirstLetter = (MyString[i] == ' ' ? true : false);
		}

		return MyString;
	}

	void UpperFirstLetterOfEachWord() {
		_Value = UpperFirstLetterOfEachWord(_Value);
	}

	/* :: [^*^] ::  */

	static string LowerFirstLetterOfEachWord(string MyString) {
		bool IsFirstLetter = true;
		for (short i = 0; i < MyString.length(); i++) {
			if (MyString[i] != ' ' && IsFirstLetter) {
				MyString[i] = tolower(MyString[i]);
			}
			IsFirstLetter = (MyString[i] == ' ' ? true : false);
		}
		return MyString;
	}

	void LowerFirstLetterOfEachWord() {
		_Value = LowerFirstLetterOfEachWord(_Value);
	}

	/* :: [^*^] ::  */

	static string UpperAllLettersOfAString(string MyString) {
		for (short i = 0; i < MyString.length(); i++) {
			MyString[i] = toupper(MyString[i]);
		}
		return MyString;
	}

	void UpperAllLettersOfAString() {
		_Value = UpperAllLettersOfAString(_Value);
	}

	/* :: [^*^] ::  */


	static string LowerAllLettersOfAString(string MyString) {
		for (short i = 0; i < MyString.length(); i++) {
			MyString[i] = tolower(MyString[i]);
		}
		return MyString;
	}

	void LowerAllLettersOfAString() {
		_Value = LowerAllLettersOfAString(_Value);
	}

	/* :: [^*^] ::  */

	static char InvertCharcterCase(char MyChar) {
		return isupper(MyChar) ? tolower(MyChar) : toupper(MyChar);
	}

	/* :: [^*^] ::  */

	static string InvertAllLettersCase(string MyString) {

		for (short i = 0; i < MyString.length(); i++) {
			MyString[i] = InvertCharcterCase(MyString[i]);
		}

		return MyString;

	}
	
	void InvertAllLettersCase() {
		_Value = InvertAllLettersCase(_Value);
	}

	/* :: [^*^] ::  */

	enum enWhatToCount { CapitalLetters = 0, SmallLetters = 1, All = 3 };

	static short CountLetters(string MyString, enWhatToCount WhatToCount = enWhatToCount::All) {

		if (WhatToCount == enWhatToCount::All) {
			return MyString.length();
		}

		short Counter = 0;
		for (short i = 0; i < MyString.length(); i++) {
			if (WhatToCount == enWhatToCount::CapitalLetters && isupper(MyString[i])) {
				Counter++;
			}
			else if (WhatToCount == enWhatToCount::SmallLetters && islower(MyString[i])) {
				Counter++;
			}
		}
		return Counter;


	}

	/* :: [^*^] ::  */

	static short CountCapitalLetters(string MyString) {
		short Counter = 0;
		for (short i = 0; i < MyString.length(); i++) {
			if (isupper(MyString[i])) {
				Counter++;
			}
		}
		return Counter;
	}

	short CountCapitalLetters() {
		return CountCapitalLetters(_Value);
	}

	/* :: [^*^] ::  */

	static short CountSmallLetters(string MyString) {
		short Counter = 0;
		for (short i = 0; i < MyString.length(); i++) {
			if (islower(MyString[i])) {
				Counter++;
			}
		}
		return Counter;

	}

	short CountSmallLetters() {
		return CountSmallLetters(_Value);
	}

	/* :: [^*^] ::  */

	static short CountLetters(string MyString, char Letter) {
		short Counter = 0;
		for (short i = 0; i < MyString[i]; i++) {
			if (MyString[i] == Letter) {
				Counter++;
			}
		}
		return Counter;
	}

	short CountLetters(char Letter) {
		return CountLetters(_Value, Letter);
	}

	/* :: [^*^] ::  */

	static short CountLettersMatchCase(string MyString, char Letter, bool MatchCase = 1) {
		short Counter = 0;

		for (short i = 0; i < MyString[i]; i++) {
			if (MatchCase) {
				if (MyString[i] == Letter) {
					Counter++;
				}
			}
			else {

				if (MyString[i] == Letter || MyString[i] == InvertCharcterCase(Letter)) {
					Counter++;
				}
			}
		}
		return Counter;
	}

	short CountLettersMatchCase(char Letter, bool MatchCase = 1) {
		return CountLettersMatchCase(_Value, Letter, MatchCase);
	}

	/* :: [^*^] ::  */

	static bool IsVowel(char MyChar) {
		MyChar = tolower(MyChar);
		return((MyChar == 'a' || MyChar == 'e' || MyChar == 'i' || MyChar == 'o' || MyChar == 'u'));
	}

	static short CountVowelInString(string MyString) {

		short Counter = 0;

		for (short i = 0; i < MyString.length(); i++) {

			if (IsVowel(MyString[i]))
				Counter++;

		}

		return Counter;
	}

	short CountVowelInString() {
		return CountVowelInString(_Value);
	}

	/* :: [^*^] ::  */

	static void PrintAllVowelsInString(string MyString) {

		for (short i = 0; i < MyString.length(); i++) {

			if (IsVowel(MyString[i]))
				cout << MyString[i] << "   ";

		}

	}

	void PrintAllVowelsInString() {
		return PrintAllVowelsInString(_Value);
	}

	/* :: [^*^] ::  */

	static void PrintEachWordInString(string MyString) {

		string delim = " ", sWord;
		short pos = 0;

		while ((pos = MyString.find(delim)) != string::npos) {

			sWord = MyString.substr(0, pos);
			if (sWord != "") {
				cout << sWord << endl;
			}

			MyString.erase(0, pos + delim.length());

		}

		if (MyString != "") {
			cout << MyString << endl;
		}

	}

	void PrintEachWordInString() {
		return PrintEachWordInString(_Value);
	}

	/* :: [^*^] ::  */

	static short CountEachWordInString(string MyString) {

		string delim = " ", sWord;
		short pos = 0, Counter = 0;

		while ((pos = MyString.find(delim)) != string::npos) {

			sWord = MyString.substr(0, pos);
			if (sWord != "") {
				Counter++;
			}
			MyString.erase(0, pos + delim.length());
		}

		if (MyString != "") {
			Counter++;
		}

		return Counter;
	}

	short CountEachWordInString() {
		return CountEachWordInString(_Value);
	}

	/* :: [^*^] ::  */

	static vector<string> SplitString(string MyString, string split) {
		string sWord;
		short pos = 0;
		vector <string> vSplitString;

		while ((pos = MyString.find(split)) != string::npos) {

			sWord = MyString.substr(0, pos);

			if (sWord != "") {
				vSplitString.push_back(sWord);
			}

			MyString.erase(0, pos + split.length());
		}

		if (MyString != "") {
			vSplitString.push_back(MyString);
		}

		return vSplitString;

	}

	vector<string> SplitString(string split) {
		return SplitString(_Value, split);
	}

	/* :: [^*^] ::  */

	static string TrimLeft(string MyString) {

		for (short i = 0; i < MyString.length(); i++) {
			if (MyString[i] != ' ') {
				MyString.erase(0, i);
				return MyString;
			}
		}

		return "";

	}

	void TrimLeft() {
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string MyString) {

		for (short i = MyString.length() - 1; i >= 0; i--) {
			if (MyString[i] != ' ') {
				MyString.erase(i + 1, MyString.length());
				return MyString;
			}
		}

		return "";

	}

	void TrimRight() {
		_Value = TrimRight(_Value);
	}

	static string Trim(string MyString) {

		return TrimRight(TrimLeft(MyString));

	}

	void Trim() {
		_Value = Trim(_Value);
	}

	/* :: [^*^] ::  */

	static string JoinString(vector <string> vStrings, string Split) {
		string S = "";
		for (string& s1 : vStrings) {
			S += s1 + Split;
		}
		return S.substr(0, S.length() - Split.length());
	}

	static string JoinString(string arrStrings[], short arrLength, string Split) {
		string S = "";
		for (short i = 0; i < arrLength; i++) {
			S += arrStrings[i] + Split;
		}
		return S.substr(0, S.length() - Split.length());
	}

	/* :: [^*^] ::  */

	static string ReversedWords(string MyString) {

		vector <string> vString = SplitString(MyString, " ");
		string S = "";
		// declare iterator
		vector<string>::iterator iter = vString.end();

		while (iter != vString.begin()) {
			--iter;
			S += *iter + " ";
		}

		return S.substr(0, S.length() - 1);

	}

	void ReversedWords() {
		_Value = ReversedWords(_Value);
	}

	/* :: [^*^] ::  */

	static string ReplaceWords(string MyString, string StringToReplace, string ReplaceTo) {

		short pos = MyString.find(StringToReplace);

		while (pos != string::npos) {

			MyString = MyString.replace(pos, StringToReplace.length(), ReplaceTo);
			pos = MyString.find(StringToReplace);

		}

		return MyString;

	}

	void ReplaceWords(string StringToReplace, string ReplaceTo) {
		_Value = ReplaceWords(_Value, StringToReplace, ReplaceTo);
	}

	static string InvertFirstLetter(string Word) {
		Word[0] = isupper(Word[0]) ? tolower(Word[0]) : toupper(Word[0]);
		return Word;
	}

	void InvertFirstLetter() {
		_Value = InvertFirstLetter(_Value);
	}

	static string ReplaceWordsDontMatchCase(string MyString, string ToReplace, string ReplaceTo, bool MatchCase = 1) {

		string S = ReplaceWords(MyString, ToReplace, ReplaceTo);

		if (MatchCase) {

			return S;
		}
		else {

			S = ReplaceWords(S, InvertFirstLetter(ToReplace), ReplaceTo);
			return S;

		}

	}

	void ReplaceWordsDontMatchCase(string StringToReplace, string ReplaceTo, bool MatchCase = 1) {
		_Value = ReplaceWordsDontMatchCase(_Value, StringToReplace, ReplaceTo, MatchCase);
	}

	/* :: [^*^] ::  */

	static string RemovePunctuations(string MyString) {

		string S = "";

		for (short i = 0; i < MyString.length(); i++) {

			if (!ispunct(MyString[i])) {
				S += MyString[i];
			}
		}

		return S;

	}

	void RemovePunctuations() {
		_Value = RemovePunctuations(_Value);
	}

	/* :: [^*^] ::  */


};

