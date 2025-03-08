#pragma once
#include "clsPerson.h"
#include <iostream>
#include "clsString.h"
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float  _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#") {

		vector <string> vClientData;
		vClientData = clsString::SplitString(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], vClientData[5], stod(vClientData[6]));

	}

	static clsBankClient _GetEmptyClientObject() {

		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);

	}

	static vector <clsBankClient> _LoadClientsDataFromFile() {

		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				vClients.push_back(_ConvertLinetoClientObject(Line));

			}

			MyFile.close();

		}

		return vClients;

	}

	static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#") {

		string DataLine = "";

		DataLine += Client.FirstName + Seperator;
		DataLine += Client.LastName + Seperator;
		DataLine += Client.Email + Seperator;
		DataLine += Client.Phone + Seperator;
		DataLine += Client.AccountNumber() + Seperator;
		DataLine += Client.PinCode + Seperator;
		DataLine += to_string(Client.AccountBalance);

		return DataLine;

	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open()) {

			string DataLine;

			for (clsBankClient C : vClients) {

				if (C.MarkedForDelete() == false) {

					DataLine = _ConverClientObjectToLine(C);
					MyFile << DataLine << endl;

				}

			}

			MyFile.close();

		}

	}

	void _Update() {

		vector<clsBankClient> _vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {
			if (C.AccountNumber() == AccountNumber()) {
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);

	}

	void _AddDataLineToFile(string DataLine) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << DataLine << endl;

			MyFile.close();

		}

	}

	void _AddNew() {

		return _AddDataLineToFile(_ConverClientObjectToLine(*this));

	}


public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone) {

		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;

	}

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete() {
		return _MarkedForDelete;
	}

	string AccountNumber() {
		return _AccountNumber;
	}

	void SetPinCode(string PinCode) {
		_PinCode = PinCode;
	}

	string GetPinCode() {
		return _PinCode;
	}
	
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;


	void SetAccountBalance(float AccountBalance) {
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance() {
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	//No UI Related code iside object. (Print)

	static clsBankClient Find(string AccountNumber) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsBankClient Client = _ConvertLinetoClientObject(Line);

				if (Client.AccountNumber() == AccountNumber) {
					MyFile.close();
					return Client;
				}

			}
		}

		return _GetEmptyClientObject();

	}

	static clsBankClient Find(string AccountNumber, string PinCode) {

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsBankClient Client = _ConvertLinetoClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode) {
					MyFile.close();
					return Client;
				}

			}
		}

		return _GetEmptyClientObject();
	}

	static bool IsClientExist(string AccountNumber) {

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());

	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	enSaveResults Save() {

		switch (_Mode)
		{

		case enMode::EmptyMode:
		{
			if (IsEmpty()) {

				return enSaveResults::svFaildEmptyObject;

			}

		}
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;

		}
		case enMode::AddNewMode:

			if (IsClientExist(_AccountNumber)) {
				return enSaveResults::svFaildAccountNumberExists;
			}
			else {
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

		}
	
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber) {

		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);

	}

	bool Delete() {

		vector<clsBankClient> _vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients) {

			if (C.AccountNumber() == AccountNumber()) {
				C._MarkedForDelete = true;
				break;
			}

		}

		_SaveClientsDataToFile(_vClients);

		*this = _GetEmptyClientObject();

		return true;

	}

	static vector <clsBankClient> GetClientsList() {

		return _LoadClientsDataFromFile();

	}

	static double GetTotalBalances() {

		vector <clsBankClient> vCLients = GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient Client : vCLients) {

			TotalBalances += Client.AccountBalance;

		}

		return TotalBalances;

	}

	void Deposit(double Amount) {

		_AccountBalance += Amount;
		Save();

	}

	bool Withdraw(double Amount) {

		if (Amount > _AccountBalance) {
			return false;
		}
		else {
			_AccountBalance -= Amount;
			Save();
			return true;
		}

	}

	bool Transfer(double Amount, clsBankClient& DestinationClient) {

		if (Amount > AccountBalance || AccountNumber() == DestinationClient.AccountNumber()) {
			return false;
		}
		else {
			Withdraw(Amount);
			DestinationClient.Deposit(Amount);
			return true;
		}

	}

};

