#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{

private:

	static void _PrintCurrency(clsCurrency Currency) {

		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();
		cout << "\n_____________________________\n";

	}

public:

	static void ShowUpdateCurrencyRateScreen() {

		_DrawScreenHeader("\tUpdate Currency Screen");

		string CurrencyCode = clsInputValidate::ReadString("\nPlease Enter Currency Code: ");
		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			CurrencyCode = clsInputValidate::ReadString("\nCurrency is not found, choose another one: ");
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrency(Currency);

		if (clsInputValidate::AskYesNo("\nAre you sure you want to update the rate of this Currency y/n? "))
		{
			cout << "\n\nUpdate Currency Rate:";
			cout << "\n____________________\n";

			cout << "\nEnter New Rate: ";
			Currency.UpdateRate(clsInputValidate::ReadFloatNumber());

			cout << "\nCurrency Rate Updated Successfully :-)\n";
			_PrintCurrency(Currency);

		}
	}

};

