#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsUser.h"
#include "clsInputValidate.h"
using namespace std;

class clsFindUserScreen : protected clsScreen
{

private:

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________________________\n";

    }

public:
	static void ShowFindUserScreen() {

		_DrawScreenHeader("\t  Find User Screen");

        string UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");

        while (!clsUser::IsUserExist(UserName)) {
            UserName = clsInputValidate::ReadString("\nUser is not found, choose another one: ");
        }

        clsUser User1 = clsUser::Find(UserName);

        if (!User1.IsEmpty()) {
            cout << "\nUser Found :-)\n";
        }
        else {
            cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User1);

	}

};

