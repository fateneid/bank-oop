#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
using namespace std;

class clsAddNewClientScreen : protected clsScreen
{

private:

	static void _ReadClientInfo(clsBankClient& Client) {

		Client.FirstName = clsInputValidate::ReadString("\nEnter FirstName: ");
		Client.LastName = clsInputValidate::ReadString("\nEnter LastName: ");
		Client.Email = clsInputValidate::ReadString("\nEnter Email: ");
		Client.Phone = clsInputValidate::ReadString("\nEnter Phone: ");
		Client.PinCode = clsInputValidate::ReadString("\nEnter PinCode: ");
		cout << "\nEnter Account Balance: ";
		Client.AccountBalance = clsInputValidate::ReadNumber<float>();

	}

	static void _PrintClient(clsBankClient Client) {

		cout << "\nClient Card:";
		cout << "\n___________________________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________________________\n";

	}

public:

	static void ShowAddNewClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient)) {
			return;
		}

		_DrawScreenHeader("\t  Add New Client Screen");

		string AccountNumber = clsInputValidate::ReadString("\nPlease Enter Account Number: ");

		while (clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("\nAccount Number Is Already Used, Choose another one: ");
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResults::svSucceeded:
		{
			cout << "\nAccount Addeded Successfully :-)\n";
			_PrintClient(NewClient);
			break;
		}
		case clsBankClient::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}
		case clsBankClient::enSaveResults::svFaildAccountNumberExists:
		{
			cout << "\nError account was not saved because account number is used!\n";
			break;
		}

		}

	}


};

