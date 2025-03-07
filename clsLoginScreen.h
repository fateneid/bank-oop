#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{

private:

	static bool _Login() {

		bool LoginFaild = false;
		string Username, Password;
		short Trials = 3;

		do {

			if (LoginFaild) {
				Trials--;
				cout << "\nInvlaid Username/Password!";
				cout << "\nYou have " << Trials << " Trial(s) to login.\n\n";
			}

			if (Trials == 0) {
				cout << "\nYour are Locked after 3 faild trails \n\n";
				return false;
			}

			Username = clsInputValidate::ReadString("Enter Username? ");
			Password = clsInputValidate::ReadString("Enter Password? ");

			CurrentUser = clsUser::Find(Username, Password);
			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;

	}

public:

	static bool ShowLoginScreen() {

		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();

	}


};

