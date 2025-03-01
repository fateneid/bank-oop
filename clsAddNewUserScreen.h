#pragma once
#include "clsScreen.h"
#include <iostream>
using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:

    static void _ReadUserInfo(clsUser& User)
    {
        User.FirstName = clsInputValidate::ReadString("\nEnter FirstName: ");
        User.LastName = clsInputValidate::ReadString("\nEnter LastName: ");
        User.Email = clsInputValidate::ReadString("\nEnter Email: ");
        User.Phone = clsInputValidate::ReadString("\nEnter Phone: ");
        User.Password = clsInputValidate::ReadString("\nEnter Password: ");
        cout << "\nEnter Permission: ";
        User.Permissions = _ReadPermissionsToSet();
    }

    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

    static int _ReadPermissionsToSet() {

    }

public:

    static void ShowAddNewUserScreen() {

        _DrawScreenHeader("\t  Add New User Screen");

        string UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");

        while (clsUser::IsUserExist(UserName))
        {
            UserName = clsInputValidate::ReadString("\nUserName Is Already Used, Choose another one: ");
        }

        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
        _ReadUserInfo(NewUser);

        clsUser::enSaveResults SaveResult = NewUser.Save();


    }

};

