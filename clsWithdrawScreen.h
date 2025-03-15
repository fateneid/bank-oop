#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
using namespace std;

class clsWithdrawScreen : protected clsScreen
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

	static void ShowWithdrawScreen() {

		_DrawScreenHeader("\t   Withdraw Screen");

		string AccountNumber = clsInputValidate::ReadString("\nPlease enter AccountNumber? ");

		while (!clsBankClient::IsClientExist(AccountNumber)) {
			cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
			AccountNumber = clsInputValidate::ReadString("\nPlease enter AccountNumber? ");
		}

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_PrintClient(Client1);

		cout << "\nPlease enter Withdraw amount? ";
		double Amount = clsInputValidate::ReadNumber<double>();

		if (clsInputValidate::AskYesNo("\nAre you sure you want to perform this transaction? ")) {
			if (Client1.Withdraw(Amount)) {
				cout << "\nAmount Withdrew Successfully.\n";
				cout << "\nNew Balance Is: " << Client1.AccountBalance;
			}
			else {
				cout << "\nCannot withdraw, Insuffecient Balance!\n";
				cout << "\nAmout to withdraw is: " << Amount;
				cout << "\nYour Balance is: " << Client1.AccountBalance;
			}
		}
		else {
			cout << "\nOperation was cancelled.\n";
		}

	}


};

