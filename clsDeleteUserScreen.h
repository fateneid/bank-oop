#pragma once
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include <iostream>
using namespace std;

class clsDeleteUserScreen : protected clsScreen
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

    static void ShowDeleteUserScreen() {

        _DrawScreenHeader("\tDelete User Screen");

        string UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");

        while (!clsUser::IsUserExist(UserName)) {
            UserName = clsInputValidate::ReadString("\nUser is not found, choose another one: ");
        }

        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);

        if (clsInputValidate::AskYesNo("\nAre you sure you want to delete this User y/n? ")) {

            if (User1.Delete()) {

                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(User1);

            }
            else {
                cout << "\nError User Was not Deleted\n";
            }

        }

    }


};

