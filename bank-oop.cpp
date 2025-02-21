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


int main()
{
	UpdateClient();
	
	system("pause>0");

	return 0;

}

