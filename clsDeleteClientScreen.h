#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
using namespace std;

class clsDeleteClientScreen : protected clsScreen
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

	static void ShowDeleteClientScreen() {

		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) {
			return;
		}

		_DrawScreenHeader("\tDelete Client Screen");

		string AccountNumber = clsInputValidate::ReadString("\nPlease Enter Account Number: ");

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("\nAccount number is not found, choose another one: ");
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		if (clsInputValidate::AskYesNo("\nAre you sure you want to delete this client y/n? ")) {

			if (Client1.Delete()) {

				cout << "\nClient Deleted Successfully :-)\n";
				_PrintClient(Client1);

			}
			else {
				cout << "\nError Client Was not Deleted\n";
			}

		}

	}


};

