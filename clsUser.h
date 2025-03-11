#pragma once
#include "clsPerson.h"
#include <iostream>
#include <vector>
#include "clsString.h"
#include <string>
#include <fstream>
#include "clsDate.h"
#include "clsUtil.h"
using namespace std;

class clsUser : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkedForDelete = false;

	struct stLoginRegisterRecord;

	static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#") {

		vector <string> vUserData;
		vUserData = clsString::SplitString(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3],
			vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));

	}

	static clsUser _GetEmptyUserObject() {

		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);

	}

	static vector <clsUser> _LoadUsersDataFromFile() {

		vector<clsUser> vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				vUsers.push_back(_ConvertLinetoUserObject(Line));

			}

			MyFile.close();

		}

		return vUsers;

	}

	static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#") {

		string DataLine = "";

		DataLine += User.FirstName + Seperator;
		DataLine += User.LastName + Seperator;
		DataLine += User.Email + Seperator;
		DataLine += User.Phone + Seperator;
		DataLine += User.UserName + Seperator;
		DataLine += clsUtil::EncryptText(User.Password) + Seperator;
		DataLine += to_string(User.Permissions);

		return DataLine;

	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open()) {

			string DataLine;

			for (clsUser C : vUsers) {

				if (C.MarkedForDelete() == false) {

					DataLine = _ConverUserObjectToLine(C);
					MyFile << DataLine << endl;

				}

			}

			MyFile.close();

		}

	}

	void _Update() {

		vector<clsUser> _vUsers = _LoadUsersDataFromFile();

		for (clsUser& C : _vUsers) {
			if (C.UserName == UserName) {
				C = *this;
				break;
			}
		}

		_SaveUsersDataToFile(_vUsers);

	}

	void _AddDataLineToFile(string DataLine) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << DataLine << endl;

			MyFile.close();

		}

	}

	void _AddNew() {

		return _AddDataLineToFile(_ConverUserObjectToLine(*this));

	}

	string _PrepareLogInRecord(string Seperator = "#//#") {

		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
		LoginRecord += UserName + Seperator;
		LoginRecord += clsUtil::EncryptText(Password) + Seperator;
		LoginRecord += to_string(Permissions);

		return LoginRecord;

	}

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#") {

		vector <string> LoginRegisterDataLine = clsString::SplitString(Line, Seperator);
		stLoginRegisterRecord LoginRegisterRecord;

		LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
		LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
		LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
		LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;

	}

public:

    clsUser(enMode Mode, string FirstName, string LastName, string Email, 
        string Phone, string UserName, string Password, 
        int Permissions) : clsPerson(FirstName, LastName, Email, Phone) {

        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;

    }

	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32,
		pManageUsers = 64, pShowLogInRegister = 128
	};

	struct stLoginRegisterRecord
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;

	};

	bool IsEmpty() {
		return (_Mode == enMode::EmptyMode);
	}

	bool MarkedForDelete() {
		return _MarkedForDelete;
	}

	void SetUserName(string UserName) {
		_UserName = UserName;
	}

	string GetUserName() {
		return _UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;


	void SetPassword(string Password) {
		_Password = Password;
	}

	string GetPassword() {
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;


	void SetPermissions(int Permissions) {
		_Permissions = Permissions;
	}

	int GetPermissions() {
		return _Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;


	static clsUser Find(string UserName) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLinetoUserObject(Line);

				if (User.UserName == UserName) {
					MyFile.close();
					return User;
				}

			}
		}

		return _GetEmptyUserObject();

	}

	static clsUser Find(string UserName, string Password) {

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;
			while (getline(MyFile, Line)) {

				clsUser User = _ConvertLinetoUserObject(Line);

				if (User.UserName == UserName && User.Password == Password) {
					MyFile.close();
					return User;
				}

			}
		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExist(string UserName) {

		clsUser User = clsUser::Find(UserName);

		return (!User.IsEmpty());

	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

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

			if (IsUserExist(_UserName)) {
				return enSaveResults::svFaildUserExists;
			}
			else {
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

		}

	}

	static clsUser GetAddNewUserObject(string UserName) {

		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);

	}

	bool Delete() {

		vector<clsUser> _vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers) {

			if (U.UserName == UserName) {
				U._MarkedForDelete = true;
				break;
			}

		}

		_SaveUsersDataToFile(_vUsers);

		*this = _GetEmptyUserObject();

		return true;

	}

	static vector <clsUser> GetUsersList() {

		return _LoadUsersDataFromFile();

	}

	bool CheckAccessPermission(enPermissions Permission) {

		if (this->Permissions == enPermissions::eAll) return true;

		if ((Permission & this->Permissions) == Permission)
			return true;
		else
			return false;

	}

	void RegisterLogIn() {

		string DataLine = _PrepareLogInRecord();

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open()) {

			MyFile << DataLine << endl;

			MyFile.close();

		}

	}

	static vector <stLoginRegisterRecord> GetLoginRegisterList() {

		vector<stLoginRegisterRecord> vLoginRegisterRecord;

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::in);

		if (MyFile.is_open()) {

			string Line;

			while (getline(MyFile, Line)) {

				vLoginRegisterRecord.push_back(_ConvertLoginRegisterLineToRecord(Line));

			}

			MyFile.close();

		}

		return vLoginRegisterRecord;
	}

};

