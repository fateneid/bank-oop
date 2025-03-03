#pragma once
#include "clsScreen.h"
#include <iostream>
#include "clsUser.h"
#include "clsInputValidate.h"
using namespace std;

class clsUpdateUserScreen : protected clsScreen
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

        return Permissions;


    }

public:

    static void ShowUpdateUserScreen() {

        _DrawScreenHeader("\tUpdate User Screen");

        string UserName = clsInputValidate::ReadString("\nPlease Enter UserName: ");

        while (!clsUser::IsUserExist(UserName)) {
            UserName = clsInputValidate::ReadString("\nUser is not found, choose another one: ");
        }

        clsUser User1 = clsUser::Find(UserName);
        _PrintUser(User1);

        if (clsInputValidate::AskYesNo("\nAre you sure you want to update this User y/n? ")) {

            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";

            _ReadUserInfo(User1);

            clsUser::enSaveResults SaveResult = User1.Save();

            switch (SaveResult)
            {
            case clsUser::enSaveResults::svSucceeded:
            {
                cout << "\nUser Updated Successfully :-)\n";
                _PrintUser(User1);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError User was not saved because it's Empty";
                break;
            }

            }

        }

    }


};

