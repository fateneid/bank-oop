#pragma once
#include "clsScreen.h"
#include <iostream>
using namespace std;

class clsTransferScreen : protected clsScreen
{

private:

	static void _PrintClient(clsBankClient Client) {

		cout << "\nClient Card:";
		cout << "\n___________________________________";
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________________________\n";

	}

	static string _ReadAccountNumber(string Message) {

		string AccountNumber = clsInputValidate::ReadString(Message);
		while (!clsBankClient::IsClientExist(AccountNumber)) {
			AccountNumber = clsInputValidate::ReadString("\nAccount number is not found, choose another one: ");
		}
		return AccountNumber;

	}

	static double _ReadAmount(clsBankClient SourceClient) {

		cout << "\nEnter Transfer Amount? ";
		double Amount = clsInputValidate::ReadNumber<double>();

		while (Amount > SourceClient.AccountBalance) {
			cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
			Amount = clsInputValidate::ReadNumber<double>();
		}
		return Amount;

	}

public:

	static void ShowTransferScreen() {

		_DrawScreenHeader("\t   Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer From: "));
		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number to Transfer To: "));
		_PrintClient(DestinationClient);

		double Amount = _ReadAmount(SourceClient);

		if (clsInputValidate::AskYesNo("\nAre you sure you want to perform this operation? y/n? ")) {
			SourceClient.Transfer(Amount, DestinationClient);
			cout << "\nTransfer done successfully\n";
		}
		else {
			cout << "\nTransfer Faild \n";
		}

		_PrintClient(SourceClient);
		_PrintClient(DestinationClient);

	}

};

