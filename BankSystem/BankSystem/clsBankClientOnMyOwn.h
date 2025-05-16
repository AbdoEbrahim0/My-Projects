//OnMyOwn
#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsInputValidate.h"
using namespace std;
class clsBankClientOnMyOwn : public clsPerson
{
	
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode
	=2};
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	//i make it static to get benifit from any staic global function anywhere static 
	// fn only call static fn clsString::Split 
	//private to apply on abstraction no one is dealing with client data except clients
	static clsBankClientOnMyOwn _ConvertLinetoClientObject(string Line, string Seprator="#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seprator);
		return clsBankClientOnMyOwn(vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], clsBankClientOnMyOwn::UpdateMode, vClientData[4],
			vClientData[5],stod(vClientData[6]));

	}
	static clsBankClientOnMyOwn _GetEmptyClientObject()
	{
		return clsBankClientOnMyOwn("", "", "", "", clsBankClientOnMyOwn::EmptyMode, "", "", 0);
	}
	void _Update()
	{
		vector<clsBankClientOnMyOwn> _vClients;

		_vClients = _LoadClientsDataFromFile();
		for (clsBankClientOnMyOwn& val : _vClients)
		{
			if (val.AccountNumber() == AccountNumber())//search in the vector of clients on the editedClient in the memory
			{
				val = *this; //this refer to object i edited in the Main (in the memory) 
				break;// and we pass a pointer refer to the edited one into val 
			}
		}
		_SaveClientsDataToFile(_vClients);
	}

	void _AddNewClient()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}
	void _AddDataLineToFile(string stringOfNewClient)
	{
		fstream myFile;
		myFile.open("Clients.txt", ios::out | ios::in);
		if (myFile.is_open())
		{
			myFile << stringOfNewClient << endl;
			myFile.close();
		}
	}
public:
	clsBankClientOnMyOwn(string FirstName,string LastName,string Email,string Phone,
		enMode _Mode,string _AccountNumber,string _PinCode,float _AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone)// try to comment this line and
	{
		
		this->_Mode = _Mode;
		this->_AccountNumber=_AccountNumber ;
		this->_PinCode = _PinCode;
		this->_AccountBalance = _AccountBalance;

	}
	bool  IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
		/*if (_Mode == clsBankClientOnMyOwn::EmptyMode)
			return true;
		return false;*/
	}

	string AccountNumber() {
		return _AccountNumber;
	}
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	void Print()
	{
		/*cout << "FNAME: " << GetFirstName()<<"\n";
		cout << "LNAME: " << GetLastName() << "\n";
		cout << "EAMAIL: " << Email << "\n";
		cout << "PINCODE: " << PinCode << "\n";
		cout << "PINCODE: " << GetPinCode() << "\n";
		cout << "PINCODE: " << _PinCode << "\n";*/
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";
	}

	static clsBankClientOnMyOwn Find(string AccountNumber)
	{
	//		vector<clsBankClientOnMyOwn> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read mode 
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{

				clsBankClientOnMyOwn myClient= _ConvertLinetoClientObject(Line);
				if (myClient._AccountNumber == AccountNumber)
				{
					MyFile.close();
					return myClient;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	static clsBankClientOnMyOwn Find(string AccountNumber, string PinCode)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read mode 
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{

				clsBankClientOnMyOwn myClient = _ConvertLinetoClientObject(Line);
				if (myClient._AccountNumber == AccountNumber && myClient._PinCode==PinCode)
				{
					MyFile.close();
					return myClient;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}
	static bool IsClientExist(string AccountNumber)
	{
	clsBankClientOnMyOwn c= Find(AccountNumber);
	return (!c.IsEmpty());
	}

	//my naive approach
	/*static clsBankClientOnMyOwn _GetEmptyClientObject2()
	{
		return  _GetEmptyClientObject();
	}*/

	static string _ConvertClientObjectToLine(clsBankClientOnMyOwn & Client,string seprator= "#//#")
	{
		return Client.FirstName+ seprator + Client.LastName+ seprator + Client.Email+ seprator +
			Client.Phone+ seprator + Client.AccountNumber()+ seprator +
			Client.PinCode+ seprator + to_string(Client.AccountBalance);
	}
	static void _SaveClientsDataToFile(vector<clsBankClientOnMyOwn>& vectorOfClients)
	{
		fstream myFileToOverWrite;
							  //Clients.txt
		myFileToOverWrite.open("Clients.txt" ,ios::out);//write mode
		if (myFileToOverWrite.is_open())
		{
			string line;
			for(clsBankClientOnMyOwn val: vectorOfClients)
			{
				line = _ConvertClientObjectToLine(val);
				myFileToOverWrite << line << endl;
			}
			myFileToOverWrite.close();
		}
	
	}

	static vector<clsBankClientOnMyOwn> _LoadClientsDataFromFile()
	{
		vector<clsBankClientOnMyOwn>vClients;
		fstream myFile;
		myFile.open("Clients.txt", ios::in);//readMode
		if (myFile.is_open())
		{
			string Line;
			while (getline(myFile, Line))
			{
				clsBankClientOnMyOwn myClient = _ConvertLinetoClientObject(Line);
				vClients.push_back(myClient);
			}
			myFile.close();
		}
		return vClients;
	}
	
	static clsBankClientOnMyOwn  GetAddNewClientObject(string accNumber)
	{
		return  clsBankClientOnMyOwn("", "", "", "", enMode::AddNewMode, accNumber, "", 0);;
	}
	enum enSaveResults {svFailEmptyObject=0,svSucceeded=1 , svFaildAccountNumberExist=2
	};

	enSaveResults  Save()
	{
		if (_Mode == enMode ::EmptyMode)
		{
			return enSaveResults :: svFailEmptyObject;
		}
		
		switch (_Mode)
		{
		case enMode::UpdateMode:
			_Update();
			return enSaveResults::svSucceeded;
		case enMode::AddNewMode:
			if (clsBankClientOnMyOwn::IsClientExist(_AccountNumber))
			{
				return svFaildAccountNumberExist;
			}
			else
			{
				_AddNewClient();
				_Mode = enMode::UpdateMode;
				return svSucceeded;
			}
			
		default:
			break;
		}


	}
	 /*void _Update2()
	{
		_Update();
	}*/
};

