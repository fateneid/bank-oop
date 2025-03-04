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

	static void _Login() {

		bool LoginFaild = false;
		string Username, Password;

		do {

			if (LoginFaild) {
				cout << "\nInvlaid Username/Password!\n\n";
			}

			Username = clsInputValidate::ReadString("Enter Username? ");
			Password = clsInputValidate::ReadString("Enter Password? ");

			CurrentUser = clsUser::Find(Username, Password);
			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);

		clsMainScreen::ShowMainMenue();

	}

public:

	static void ShowLoginScreen() {

		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		_Login();

	}


};

