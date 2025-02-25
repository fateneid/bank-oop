#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

class clsFindClientScreen : protected clsScreen
{

private:

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

	static void ShowFindClientScreen() {

		_DrawScreenHeader("\tFind Client Screen");

		string AccountNumber = clsInputValidate::ReadString("\nPlease Enter Account Number: ");

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("\nAccount number is not found, choose another one: ");
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		if (!Client1.IsEmpty()) {
			cout << "\nClient Found :-)\n";
		}
		else{
			cout << "\nClient Was not Found :-(\n";
		}

		_PrintClient(Client1);

	}

};

