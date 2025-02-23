#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

void ReadClientInfo(clsBankClient& Client) {

	Client.FirstName = clsInputValidate::ReadString("\nEnter FirstName: ");
	Client.LastName = clsInputValidate::ReadString("\nEnter LastName: ");
	Client.Email = clsInputValidate::ReadString("\nEnter Email: ");
	Client.Phone = clsInputValidate::ReadString("\nEnter Phone: ");
	Client.PinCode = clsInputValidate::ReadString("\nEnter PinCode: ");
	cout << "\nEnter Account Balance: ";
	Client.AccountBalance = clsInputValidate::ReadFloatNumber();

}

void UpdateClient() {

	string AccountNumber = "";

	AccountNumber = clsInputValidate::ReadString("\nPlease Enter client Account Number: ");

	while (!clsBankClient::IsClientExist(AccountNumber)) {
		AccountNumber = clsInputValidate::ReadString("\nAccount number is not found, choose another one: ");
	}

	clsBankClient Client1 = clsBankClient::Find(AccountNumber);
	Client1.Print();

	cout << "\n\nUpdate Client Info:";
	cout << "\n____________________\n";

	ReadClientInfo(Client1);

	clsBankClient::enSaveResults SaveResult = Client1.Save();

	switch (SaveResult)
	{
	case clsBankClient::enSaveResults::svSucceeded:
	{
		cout << "\nAccount Updated Successfully :-)\n";
		Client1.Print();
		break;
	}
	case clsBankClient::enSaveResults::svFaildEmptyObject:
	{
		cout << "\nError account was not saved because it's Empty";
		break;
	}

	}


}

void AddNewClient() {

	string AccountNumber = clsInputValidate::ReadString("\nPlease Enter Account Number: ");

	while (clsBankClient::IsClientExist(AccountNumber)) {
		AccountNumber = clsInputValidate::ReadString("\nAccount Number Is Already Used, Choose another one: ");
	}

	clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

	ReadClientInfo(NewClient);

	clsBankClient::enSaveResults SaveResult = NewClient.Save();

	switch (SaveResult)
	{
	case clsBankClient::enSaveResults::svSucceeded:
	{
		cout << "\nAccount Addeded Successfully :-)\n";
		NewClient.Print();
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

void DeleteClient() {

	string AccountNumber = clsInputValidate::ReadString("\nPlease Enter Account Number : ");

	while (!clsBankClient::IsClientExist(AccountNumber)) {
		AccountNumber = clsInputValidate::ReadString("\nAccount number is not found, choose another one: ");
	}

	clsBankClient Client1 = clsBankClient::Find(AccountNumber);
	Client1.Print();

	if (clsInputValidate::AskYesNo("\nAre you sure you want to delete this client y/n? ")) {

		if (Client1.Delete()) {

			cout << "\nClient Deleted Successfully :-)\n";
			Client1.Print();
			
		}
		else {
			cout << "\nError Client Was not Deleted\n";
		}

	}

}

void PrintClientRecordLine(clsBankClient Client) {

	cout << "| " << setw(15) << left << Client.AccountNumber();
	cout << "| " << setw(20) << left << Client.FullName();
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(20) << left << Client.Email;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowClientsList() {

	vector <clsBankClient> vClients = clsBankClient::GetClientsList();

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(20) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(20) << "Email";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vClients.size() == 0) {
		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else {

		for (clsBankClient Client : vClients) {

			PrintClientRecordLine(Client);
			cout << endl;

		}

	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

}

int main()
{
	ShowClientsList();
	
	system("pause>0");

	return 0;

}

