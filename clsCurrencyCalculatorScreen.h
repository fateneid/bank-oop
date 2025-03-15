#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iostream>
#include "clsInputValidate.h"
using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{

private:

	static void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:") {

		cout << "\n" << Title << "\n";
		cout << "_____________________________\n";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCode          : " << Currency.CurrencyCode();
		cout << "\nName          : " << Currency.CurrencyName();
		cout << "\nRate(1$) =    : " << Currency.Rate();
		cout << "\n_____________________________\n\n";

	}

	static clsCurrency _GetCurrency(string Message) {

		string CurrencyCode = clsInputValidate::ReadString(Message);

		while (!clsCurrency::IsCurrencyExist(CurrencyCode)) {
			CurrencyCode = clsInputValidate::ReadString("\nCurrency is not found, choose another one: ");
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return Currency;
	}

	static void _PrintCalculationsResults(float Amount, clsCurrency Currency1, clsCurrency Currency2) {

		_PrintCurrencyCard(Currency1, "Convert From:");

		float C1InUSD = Currency1.ConvertToUSD(Amount);
		cout << "\n" << Amount << " " << Currency1.CurrencyCode()
			<< " = " << C1InUSD << " USD \n";

		if (Currency2.CurrencyCode() == "USD") {
			return;
		}

		cout << "\nConverting from USD to:\n";
		_PrintCurrencyCard(Currency2, "To:");

		float AmountInCurrrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);
		cout << "\n" << Amount << " " << Currency1.CurrencyCode()
			<< " = " << AmountInCurrrency2 << Currency2.CurrencyCode();

	}

public:

	static void ShowCurrencyCalculatorScreen() {

		do {

			system("cls");
			_DrawScreenHeader("\tCurrency Calculator Screen");

			clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code:\n");
			clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code:\n");

			cout << "\nEnter Amount to Exchange: ";
			float Amount = clsInputValidate::ReadNumber<float>();

			_PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);

		} while (clsInputValidate::AskYesNo("\n\nDo you want to perform another calculation? y/n ? "));

	}

};

