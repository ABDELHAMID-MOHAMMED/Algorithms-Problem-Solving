#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string ClientsFileName = "Client.txt";
void ShowMainMenu();
void ShowTransactionsScreen();
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance=0;
	bool MarkForDelete = false;
};
enum enMainMenuOptions {
	SHOWINGCLIENTLISTS=1, ADDNEWCLIENT=2, DELETECLIENT=3,
	UBDATECLIENTINFO=4, FINDCLIENT=5,TRANSACTIONS=6,EXIT=7
};
enum enTransactionMenu { DEPOSIT = 1,WITHDRAW=2,TOTALBALANCE=3,MainMenu=4 };
vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord; 
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}
sClient ReadNewClient()
{
	sClient Client;

	// استخدمنا cin >> ws عشان نطير أي Enter معلقة في الـ Buffer وتمنع تخطي الأسطر
	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);

	cout << "Enter PinCode? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}
//void AddNewClient()
//{
//	cout << "=========================\n";
//	cout << "\tAdding New Client\n";
//	cout << "=========================\n";
//
//	ReadNewClient();
//}
sClient ReadClientDataForUpdate(string AccountNumber)
{
	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode); 

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}
void AddDataLineToFile(string FileName, string stLine)
{
	fstream ClientFile;
	ClientFile.open(FileName, ios::out | ios::app); // ios::app للإضافة في آخر الملف
	if (ClientFile.is_open())
	{
		ClientFile << stLine << endl;
		ClientFile.close();
	}
}
sClient ConvertLinetoRecord(string Line, string Seperator =" ")
{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);//cast string todouble
		return Client;
}
string ConvertRecordToLine(sClient Client, string Seperator =" ")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}
void PrintClientRecord(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintClientBalance(sClient Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintSerchClient(sClient Client)
{
	"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "Accout Number : "<<Client.AccountNumber<<endl;
	cout << "Pin Code : "<<Client.PinCode<<endl;
	cout << "Client Name : "<<Client.Name<<endl;
	cout << "Phone : "<<Client.Phone<<endl;
	cout << "Balance : "<<Client.AccountBalance;
	cout <<
		"\n_______________________________________________________";

}
void PrintAllClientsData()
{
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
		cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	if (vClients.size() == 0)
		cout << "\t\t\t No Client Available In The System .";
	else	
	for (sClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}
void ShowTotalBalance()
{
	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\tClient Account Balance (" << vClients.size() << ")Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	double TotalBalances = 0;
	if (vClients.size() == 0)
		cout << "\t\t\t No Client Available In The System .";
	else
		for (sClient &Client : vClients)
		{
			PrintClientBalance(Client);
			TotalBalances += Client.AccountBalance;
			cout << endl;
		}
	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t Total Balance : " << TotalBalances << endl;
}
bool SerchClient(string Account,sClient &Client)
{
	vector <sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	for (sClient& C : vClient)
	{
		if (C.AccountNumber == Account)
		{
			Client = C;
			return true;
		}
		else {
			return false;
		}
	}
}
bool MarkClientForDeleteByAccountNumber(string AccountNumber,vector <sClient>& vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
string ReadAccount()
{
	string Account;
	cout << "enter the Account Number : ";
	getline(cin >> ws, Account);
	return Account;
}
void AddNewClient()
{
	/*char AddMore = 'Y';
	do
	{*/

	system("cls");// تنظيف الشاشة في كل لفة
	cout << "Adding New Client:\n\n";

	sClient Client = ReadNewClient();

	// بنحول الـ Struct لسطر واحد
	string stLine = ConvertRecordToLine(Client, " ");

	// بنحفظ السطر في الملف
	AddDataLineToFile("Client.txt", stLine);

	/*	cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;

	} while (AddMore == 'Y' || AddMore == 'y');*/
}
vector<sClient> SaveClientsDataToFile(string FileName, vector<sClient>& vClient)
{
	fstream ClientFile;

	ClientFile.open(FileName, ios::out);
	string DataLine;
	if (ClientFile.is_open())
	{
		for (sClient& C : vClient)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				ClientFile << DataLine << endl;
			}

		}

		ClientFile.close();
	}
	return vClient;
}
bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClient, sClient& Client)
{
	for (sClient C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
void ShowFindClientScreen()
{
	cout << "-----------------------\n";
	cout << "\tFind Client Screen\n";
	cout << "-----------------------\n";

	vector<sClient>vClient = LoadCleintsDataFromFile(ClientsFileName);
	string Account = ReadAccount();
	sClient Client;
	if (FindClientByAccountNumber(Account, vClient, Client))
		PrintClientRecord(Client);
	else
	cout << "\nClient with Account Number (" << Account << ") is Not Found!";

}
bool DeleteClient(string Account,vector<sClient> &vClient)
{
	sClient Client;
	char Answer = 'n';
	
	if (FindClientByAccountNumber(Account,vClient,Client))
	{
		PrintSerchClient(Client);
		cout << "\n Are your sure you want to delete this Client : y/n ?";
		cin >> Answer;
		 if(Answer=='Y'||Answer=='y')
		 { 
			 MarkClientForDeleteByAccountNumber(Account, vClient);
			 SaveClientsDataToFile(ClientsFileName,vClient);
			 vClient = LoadCleintsDataFromFile(ClientsFileName);
			 cout << " \nAccount Deleting Successfully \n";
			 return true;
			}
		}
	else
	{
		cout << "\nClient with Account Number (" << Account<< ") is Not Found!";
		return false;
	}
}
void ShowDeleteClient()
{
	cout << "-----------------------\n";
	cout << "\tDeleting Client Screen\n";
	cout << "-----------------------\n";

	vector <sClient>vClient = LoadCleintsDataFromFile(ClientsFileName);
	string Account = ReadAccount();
	DeleteClient(Account, vClient);

}
bool UbdateClient(string Account, vector<sClient>& vClient)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(Account, vClient, Client))
	{
		PrintSerchClient(Client);
		cout << "\n Are your sure you want to Ubdate this Client : y/n ?";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			for (sClient& C : vClient)
			{
				if (C.AccountNumber == Account)
				{
					C = ReadClientDataForUpdate(Account);
					break;
				}
			}
			SaveClientsDataToFile(ClientsFileName,vClient);
			vClient = LoadCleintsDataFromFile(ClientsFileName);
			cout << " \nAccount Ubdating Successfully \n";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << Account << ") is Not Found!";
		return false;
	}
}
void ShowUpdateClientScreen()
{

	cout << "-----------------------\n";
	cout << "\tUbdating Client Screen\n";
	cout << "-----------------------\n";
	vector <sClient>vClient = LoadCleintsDataFromFile(ClientsFileName);
	string Account = ReadAccount();
	UbdateClient(Account, vClient);
}
void GoBackToMainMenu()
{
	cout << "\n\nPress any key to go back to Main Menu...";
	system("pause>0");
	ShowMainMenu();
}
void GoBackToTransactionMenu()
{
	cout << "\n\nPress any key to go back to Transaction Menu...";
	system("pause>0");
	ShowTransactionsScreen();
}
short ReadMainMenuOption()
{
	cout << " CHOSE WHAT DO YOU WANT TO DO [1 TO 6] ?\n";
	short Choise = 0;
	cin >> Choise;
	return Choise;
}
short ReadTransactionMenu()
{
	cout << " CHOSE WHAT DO YOU WANT TO DO [1 TO 4] ?\n";
	short Choise = 0;
	cin >> Choise;
	return Choise;
}
void ShowEndScreen()
{
	cout << "-----------------------\n";
	cout << "\tProgram Ends :-)\n";
	cout << "-----------------------\n";
}
bool DepositFromClient(string Account, vector<sClient>& vClient)
{
	sClient Client;
	int Deposit;
	if (FindClientByAccountNumber(Account, vClient, Client))
	{
		PrintSerchClient(Client);
		cout << "\n PLEASE ENTER DEPOSIT NUMBER ?";
		cin >> Deposit;


		for (sClient& C : vClient)
		{
			if (C.AccountNumber == Account)
			{
				C.AccountBalance += Deposit;
				break;
			}
		}
		SaveClientsDataToFile(ClientsFileName, vClient);
		vClient = LoadCleintsDataFromFile(ClientsFileName);
		cout << " \nAccount Deposit Successfully \n";
		return true;
	}
	else
	{
		cout << "\nClient with Account Number (" << Account << ") is Not Found!";
		return false;
	}
}
void ShowDepositFromClient()
{
	cout << "-----------------------\n";
	cout << "\Deposit Account Screen\n";
	cout << "-----------------------\n";
	string Account = ReadAccount();
	vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	DepositFromClient(Account, vClient);
}
bool WithDrawFromClient(string Account, vector<sClient>& vClient)
{
	sClient Client;
	int Withdraw;
	if (FindClientByAccountNumber(Account, vClient, Client))
	{
		PrintSerchClient(Client);

		for (sClient& C : vClient)
		{
			if (C.AccountNumber == Account)
			{
				cout << "\n PLEASE ENTER WITHDRAW AMOUNT ?";
				cin >> Withdraw;

				while (Withdraw > C.AccountBalance)
				{
					cout << "\nAmount Exceeds The Balance, You Can Withdraw Up To: " << C.AccountBalance << endl;
					cout << "Please Enter another Amount: ";
					cin >> Withdraw;
				}
				C.AccountBalance -= Withdraw;
				break;
			}
		}
			SaveClientsDataToFile(ClientsFileName, vClient);
			vClient = LoadCleintsDataFromFile(ClientsFileName);
			cout << " \nAccount Withdraw Successfully \n";
			return true;
		}
	
	else
	{
		cout << "\nClient with Account Number (" << Account << ") is Not Found!";
		return false;
	}
}
void ShowWithdrawFromClient()
{
	cout << "-----------------------\n";
	cout << "\tWithdraw Account Screen\n";
	cout << "-----------------------\n";
	string Account = ReadAccount();
	vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	WithDrawFromClient(Account, vClient);
}

void TransactionMenuoption(enTransactionMenu TransactionMenu)
{
	switch (TransactionMenu)
	{
	case enTransactionMenu::DEPOSIT:
	{
		system("cls");
		ShowDepositFromClient();
		GoBackToTransactionMenu();
		break;
	}
	case enTransactionMenu::WITHDRAW:
	{
		system("cls");
		ShowWithdrawFromClient();
		GoBackToTransactionMenu();
		break;
	}
	case enTransactionMenu::TOTALBALANCE:
	{
		system("cls");
		ShowTotalBalance();
		GoBackToTransactionMenu();
		break;
	}
	case enTransactionMenu::MainMenu:
	{
		system("cls");
		GoBackToMainMenu();
		break;
	}
	}
}
void ShowTransactionsScreen()
{
	cout << "===============================\n";
	cout << "\tTRANSACTION SCREEN \n";
	cout << "[1] DEPOSIT .\n";
	cout << "[2] WITHDRAW .\n";
	cout << "[3] TOTAL BALANCE .\n";
	cout << "[4] Main Menu .\n";
	cout << "===============================\n";
	cout << "CHOSE WHAT DO YOU WANT TO DO [1/4]?\n";
	TransactionMenuoption((enTransactionMenu)ReadTransactionMenu());
}
void PerFormMainMenuOption(enMainMenuOptions MainMenuOptions)
{
	switch (MainMenuOptions)
	{
	case enMainMenuOptions::SHOWINGCLIENTLISTS:
	{
		system("cls");
		PrintAllClientsData();
		GoBackToMainMenu();
		break;
	}
	case enMainMenuOptions::ADDNEWCLIENT:
	{
		system("cls");
		AddNewClient();
		GoBackToMainMenu();
		break;
	}
	case enMainMenuOptions::DELETECLIENT:
	{
		system("cls");
		ShowDeleteClient();
		GoBackToMainMenu();
		break;
	}
	case enMainMenuOptions::UBDATECLIENTINFO:
	{
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenu();
		break;
	}
	case enMainMenuOptions::FINDCLIENT:
	{
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;
	}
	case enMainMenuOptions::TRANSACTIONS:
	{
		system("cls");
		ShowTransactionsScreen();
		GoBackToMainMenu();
		break;
	}
	case enMainMenuOptions::EXIT:
	{
		system("cls");
		ShowEndScreen();
		GoBackToMainMenu();
		break;
	}
}

}
void ShowMainMenu()
{
	system("cls");
	cout << "------------------------------------------------\n";
	cout << "================================================\n";
	cout << setw(30) << right << "MAIN MENU SCREEN \n";
	cout << "================================================\n";
	cout << " [1] SHOWING CLIENT LISTS .\n";
	cout << " [2] ADD NEW CLIENT .\n";
	cout << " [3] DELETE CLIENT .\n";
	cout << " [4] UBDATE CLIENT INFO .\n";
	cout << " [5] FIND CLIENT .\n";
	cout << " [6] Transactions .\n";
	cout << " [7] EXIT.\n";
	cout << "===================================================\n";
	cout << " CHOSE WHAT DO YOU WANT TO DO [1 TO 7] ?\n";
	PerFormMainMenuOption((enMainMenuOptions)ReadMainMenuOption());

}

int main()
{
	ShowMainMenu();
	system("pause>0");
	return 0;
}