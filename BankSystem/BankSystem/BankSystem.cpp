
//ProgrammingAdvices.com
//Mohmammed Abu-Hadhoud
#include <iostream>
#include "clsBankClientOnMyOwn.h"


//2nd video

void ReadClientInfo(clsBankClientOnMyOwn& myclinet)
{
    cout << "\nBEFORE EDIT ::\n" << endl;
    myclinet.Print();
    string temp = "";
    cout << "\nF.Name: ";
    cin >> temp;   myclinet.FirstName = temp;
    cout << "\nL.Name: ";
    cin >> temp; myclinet.LastName = temp;
    cout << "\nEmail: ";
    cin >> temp; myclinet.Email = temp;
    cout << "\nPhone: ";
    cin >> temp; myclinet.Phone = temp;
    cout << "\nPinCode: ";
    cin >> temp; myclinet.PinCode = temp;
    cout << "\nAccountBalance  ";  myclinet.AccountBalance = clsInputValidate::ReadDblNumber();
    cout << "\n Results After EDIT ::\n" << endl;
    myclinet.Print();

}
    //my wrong naive approch 
//void _Update()
//{
//    cout << "Enter Account number to update Info: ";
//    string s = clsInputValidate::ReadString();
//
//    while (!clsBankClientOnMyOwn:: IsClientExist(s))
//    {
//        s = clsInputValidate::ReadString("invalid account number please try another account exist: ");
//
//    }
//    clsBankClientOnMyOwn clientToEdit = clsBankClientOnMyOwn:: Find(s);
//    ReadClientInfo(clientToEdit);
//    clsBankClientOnMyOwn AfterEdit= clientToEdit.Save();
//}
void UpdateClient()
{
    cout << "Enter Account number to update Info: ";
    string s = clsInputValidate::ReadString();

    while (!clsBankClientOnMyOwn::IsClientExist(s))
    {
        cout << "invalid account number please try another account exist: \n";
        s = clsInputValidate::ReadString();

    }
    clsBankClientOnMyOwn clientToEdit = clsBankClientOnMyOwn::Find(s);
    ReadClientInfo(clientToEdit);
    clientToEdit.Save();
}

void AddNewClient()
{
    cout << "Enter Acount number of a new Client you want to add to databse\n";
    string accNum = clsInputValidate::ReadString();
    while (clsBankClientOnMyOwn::IsClientExist(accNum))
    {
        cout << "Account Number You enter Exist in database  try another one: \n";
        accNum = clsInputValidate::ReadString();
    }
    clsBankClientOnMyOwn NewClient=clsBankClientOnMyOwn::GetAddNewClientObject(accNum);
    
    ReadClientInfo(NewClient);

    clsBankClientOnMyOwn::enSaveResults SaveResults;
    SaveResults = NewClient.Save();
    if (SaveResults == clsBankClientOnMyOwn::enSaveResults::svSucceeded)
    {
        cout << "new account Added succesfully To databse" << endl;
        NewClient.Print();
    }
    else if (SaveResults == clsBankClientOnMyOwn::enSaveResults::svFailEmptyObject)
    {
    
        cout << "\nError account was not saved because it's Empty";
    }
    else if (SaveResults == clsBankClientOnMyOwn::enSaveResults::svFaildAccountNumberExist)
    {
        cout << "faid to add to database The Account Number is exist already\n";
    }
        
}
int main()

{
//1st video

    //clsBankClientOnMyOwn Client1 = clsBankClientOnMyOwn::Find("A101");
    //if (!Client1.IsEmpty())
    //{
    //    cout << "\nClient Found :-)\n";
    //}
    //else
    //{
    //    cout << "\nClient Was not Found :-(\n";
    //}
    //Client1.Print();
    //clsBankClientOnMyOwn Client2 = clsBankClientOnMyOwn::Find("A101", "1234");
    //if (!Client2.IsEmpty())
    //{
    //    cout << "\nClient Found :-)\n";
    //}
    //else
    //{
    //    cout << "\nClient Was not Found :-(\n";
    //}
    //Client2.Print();
    //cout << "\nIs Client Exist? " << clsBankClientOnMyOwn::IsClientExist("A101");
    //cout << "\nIs Client Exist? " << clsBankClientOnMyOwn::IsClientExist("A105115");

//2nd video
    // this my naive way it forced my to declare object without need all what was asked was update fn in main
    // if you go in implemenation of naive you will see that you type find fun twice
    //my wrong naive approch 
        //clsBankClientOnMyOwn clientToUpdate= clsBankClientOnMyOwn::_GetEmptyClientObject2();// static fn only can call static fn 
        //clientToUpdate._Update2();
    // the correct way 
        //UpdateClient();
    //3rd video
        AddNewClient();
//1st video
    system("pause>0");
    return 0;
}