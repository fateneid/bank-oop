#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsUser.h"
#include "clsInputValidate.h" 
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

    static int _ReadPermissionsToSet() {

        int Permissions = 0;

        if (clsInputValidate::AskYesNo("\nDo you want to give full access? y/n? "))
        {
            return -1;
        }

        cout << "\nDo you want to give access to : \n ";

        if (clsInputValidate::AskYesNo("\nShow Client List? y/n? "))
        {
            Permissions += clsUser::enPermissions::pListClients;
        }

        if (clsInputValidate::AskYesNo("\nAdd New Client? y/n? "))
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        if (clsInputValidate::AskYesNo("\nDelete Client? y/n? "))
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        if (clsInputValidate::AskYesNo("\nUpdate Client? y/n? "))
        {
            Permissions += clsUser::enPermissions::pUpdateClients;
        }

        if (clsInputValidate::AskYesNo("\nFind Client? y/n? "))
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        if (clsInputValidate::AskYesNo("\nTransactions? y/n? "))
        {
            Permissions += clsUser::enPermissions::pTranactions;
        }

        if (clsInputValidate::AskYesNo("\nManage Users? y/n? "))
        {
            Permissions += clsUser::enPermissions::pManageUsers;
        }

        if (clsInputValidate::AskYesNo("\nShow Login Register? y/n? "))
        {
            Permissions += clsUser::enPermissions::pShowLogInRegister;
        }

        return Permissions;

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

        switch (SaveResult)
        {
        case clsUser::enSaveResults::svSucceeded:
        {
            cout << "\nUser Addeded Successfully :-)\n";
            _PrintUser(NewUser);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved because it's Empty";
            break;

        }
        case clsUser::enSaveResults::svFaildUserExists:
        {
            cout << "\nError User was not saved because UserName is used!\n";
            break;

        }

        }
    }

};

