#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
using namespace std;

//void UpdateClient() {
//
//	string AccountNumber = "";
//
//	AccountNumber = clsInputValidate::ReadString("\nPlease Enter client Account Number: ");
//
//	while (!clsBankClient::IsClientExist(AccountNumber)) {
//		AccountNumber = clsInputValidate::ReadString("\nAccount number is not found, choose another one: ");
//	}
//
//	clsBankClient Client1 = clsBankClient::Find(AccountNumber);
//	Client1.Print();
//
//	cout << "\n\nUpdate Client Info:";
//	cout << "\n____________________\n";
//
//	ReadClientInfo(Client1);
//
//	clsBankClient::enSaveResults SaveResult = Client1.Save();
//
//	switch (SaveResult)
//	{
//	case clsBankClient::enSaveResults::svSucceeded:
//	{
//		cout << "\nAccount Updated Successfully :-)\n";
//		Client1.Print();
//		break;
//	}
//	case clsBankClient::enSaveResults::svFaildEmptyObject:
//	{
//		cout << "\nError account was not saved because it's Empty";
//		break;
//	}
//
//	}
//
//
//}
//
//
//void PrintClientRecordBalanceLine(clsBankClient Client) {
//
//	cout << "| " << setw(15) << left << Client.AccountNumber();
//	cout << "| " << setw(40) << left << Client.FullName();
//	cout << "| " << setw(12) << left << Client.AccountBalance;
//
//}
//
//void ShowTotalBalances() {
//
//	vector <clsBankClient> vClients = clsBankClient::GetClientsList();
//
//	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
//	cout << "\n_______________________________________________________";
//	cout << "_________________________________________\n" << endl;
//
//	cout << "| " << left << setw(15) << "Accout Number";
//	cout << "| " << left << setw(40) << "Client Name";
//	cout << "| " << left << setw(12) << "Balance";
//	cout << "\n_______________________________________________________";
//	cout << "_________________________________________\n" << endl;
//
//	double TotalBalances = clsBankClient::GetTotalBalances();
//
//	if (vClients.size() == 0) {
//		cout << "\t\t\t\tNo Clients Available In the System!";
//
//		cout << "\n_______________________________________________________";
//		cout << "_________________________________________\n" << endl;
//	}
//	else {
//
//		for (clsBankClient Client : vClients) {
//
//			PrintClientRecordBalanceLine(Client);
//			cout << endl;
//
//		}
//
//		cout << "\n_______________________________________________________";
//		cout << "_________________________________________\n" << endl;
//		cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
//		cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(TotalBalances) << ")";
//
//	}
//
//}

int main()
{
	clsMainScreen::ShowMainMenue();
	
	system("pause>0");

	return 0;

}

