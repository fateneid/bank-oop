#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;

class clsFindCurrencyScreen : protected clsScreen
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

    static void ShowFindCurrencyScreen() {

		_DrawScreenHeader("\t  Find Currency Screen");

		cout << "\nFind By: [1] Code or [2] Country ? ";
		short Answer = clsInputValidate::ReadShortNumberBetween(1, 2, "\nChoose between 1 and 2? ");

		clsCurrency Currency = Answer == 1 ?
			clsCurrency::FindByCode(clsInputValidate::ReadString("\nPlease Enter Currency Code: ")) :
			clsCurrency::FindByCountry(clsInputValidate::ReadString("\nPlease Enter Country Name: "));

		if (!Currency.IsEmpty()) {
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else {
			cout << "\nCurrency Was not Found :-(\n";
		}

    }


};

