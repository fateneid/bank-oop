#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
using namespace std;

class clsUpdateClientScreen : protected clsScreen
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

	static void ShowUpdateClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients)) {
			return;
		}

		_DrawScreenHeader("\tUpdate Client Screen");

		string AccountNumber = "";

		AccountNumber = clsInputValidate::ReadString("\nPlease Enter client Account Number: ");

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("\nAccount number is not found, choose another one: ");
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		cout << "\n\nUpdate Client Info:";
		cout << "\n____________________\n";

		_ReadClientInfo(Client1);

		clsBankClient::enSaveResults SaveResult = Client1.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResults::svSucceeded:
		{
			cout << "\nAccount Updated Successfully :-)\n";
			_PrintClient(Client1);
			break;
		}
		case clsBankClient::enSaveResults::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}

		}

	}

};

