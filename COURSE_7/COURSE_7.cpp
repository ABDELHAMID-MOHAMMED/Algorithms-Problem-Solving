#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;
const string ClientsFileName = "Client.txt";
const string UserFile = "Users.txt";
void ShowMainMenu();
void ShowAtmMenu();
void ShowTransactionsScreen();
void GoBackToMainMenu();
bool UserExistByUserName(string UserName, string UserFile);
int ReadPermission();
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance=0;
	bool MarkForDelete = false;
};
sClient CurrentClient;
bool SearchClient(string Account, sClient& Client);
struct stUsers
{
	string UserName;
	string Password;
	int Permissions;
	bool MarkForDelete = false;
};
vector<stUsers> LoadUsersDataFromFile(string UserFile);
void ShowUsersScreen();
void Login();
stUsers CurrentUser;
enum enMainMenuOptions {
	SHOWINGCLIENTLISTS=1, ADDNEWCLIENT=2, DELETECLIENT=3,
	UPDATECLIENTINFO=4, FINDCLIENT=5,TRANSACTIONS=6,MANAGEUSERS=7,LOGOUT=8
};
enum enAtmMainMenuOptions{enQuickWithdraw=1,enNormalWithdraw=2,enDeposit=3,enCheckBalance=4,enLogOut=5};
enum enTransactionMenu { DEPOSIT = 1,WITHDRAW=2,TOTALBALANCE=3,MainMenu=4 };
enum enUsersMenuOptions{LISTSUSERS=1,ADDNEWUSER=2,DELETEUSER=3,UPDATEUSER=4,FINDUSER=5,MAINMENU=6};
enum enPermissions { ShowClientLists=1, AddClient = 2, DeleteClient = 4, UpdateClient = 8, FindClient = 16,Transactions  = 32,ManageUsers=64};
vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	size_t pos = 0;
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
	sClient Temp;
	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);
	while (SearchClient(Client.AccountNumber, Temp))
	{
		cout << "Already exists";
		cout << "Please Enter Right Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}
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
stUsers ReadUserDataForUpdate(string UserName)
{
	stUsers User;
	User.UserName = UserName;
	cout << "Enter New Password ? ";
	getline(cin >> ws, User.Password);
	User.Permissions = ReadPermission();
	return User;
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
void AddUsersDataLineToFile(string UserFile, string stLine)
{
	fstream ClientFile;
	ClientFile.open(UserFile, ios::out | ios::app); // ios::app للإضافة في آخر الملف
	if (ClientFile.is_open())
	{
		ClientFile << stLine << endl;
		ClientFile.close();
	}
}
sClient ConvertLinetoRecord(string Line, string Seperator ="-")
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
string ConvertRecordToLine(sClient Client, string Seperator ="-")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
string ConvertUsersRecordToLine(stUsers User, string Seperator = "#//#")
{
	string stUserRecord = "";
	stUserRecord += User.UserName + Seperator;
	stUserRecord += User.Password + Seperator;
	stUserRecord += to_string(User.Permissions);
	return stUserRecord;
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
bool CheckAccessPermission(int UserPermission, enPermissions PermissionToCheck)
{
	if (UserPermission == -1)
		return true;
	if ((UserPermission & PermissionToCheck) == PermissionToCheck)
		return true;
	else
		return false;
}
void AccessDeniedScreen()
{
	cout << "==============================\n";
	cout << "Access Denied ,\n";
	cout << "You Dont Have Permission To Do This ,\n";
	cout << "Please conact Your Admin.\n";
	cout << "==============================\n\n\n";
	GoBackToMainMenu();
}
bool UserExistByUserName(string UserName, string UserFile)
{
	vector<stUsers>vUsers = LoadUsersDataFromFile(UserFile);

	for (stUsers& U : vUsers)
	{
		if (U.UserName == UserName)
		{
			return true;
		}
	}
	return false;
}
int ReadPermission()
{
	char Access;
	char GiveAccess;
	short Permission = 0;
	cout << "Do You Want TO Give Full Access ?y/n";
	cin >> Access;
	if (Access == 'Y' || Access == 'y')
	{
		return -1;
	}

	cout << "\nDo You Want To Give Access To :\n";
	cout << "Show Client lists ? ";
	cin >> GiveAccess;
	if (GiveAccess == 'Y' || GiveAccess == 'y')
	{
		Permission += enPermissions::ShowClientLists;
	}
	cout << "\nAdd New Client ? ";
	cin >> GiveAccess;
	if (GiveAccess == 'Y' || GiveAccess == 'y')
	{
		Permission += enPermissions::AddClient;
	}
	cout << "\nDelete Client ? ";
	cin >> GiveAccess;
	if (GiveAccess == 'Y' || GiveAccess == 'y')
	{
		Permission += enPermissions::DeleteClient;
	}
	cout << "\nUpdate Client ? ";
	cin >> GiveAccess;
	if (GiveAccess == 'Y' || GiveAccess == 'y')
	{
		Permission += enPermissions::UpdateClient;
	}
	cout << "\nFind Client ? ";
	cin >> GiveAccess;
	if (GiveAccess == 'Y' || GiveAccess == 'y')
	{
		Permission += enPermissions::FindClient;
	}
	cout << "\nTransactions ? ";
	cin >> GiveAccess;
	if (GiveAccess == 'Y' || GiveAccess == 'y')
	{
		Permission += enPermissions::Transactions;
	}
	cout << "\nManage Users ? ";
	cin >> GiveAccess;
	if (GiveAccess == 'Y' || GiveAccess == 'y')
	{
		Permission += enPermissions::ManageUsers;
	}
	return Permission;
}
string ConvertUserRecordToLine(stUsers User, string Seperator = "#//#")
{
	string stUserRecord = "";
	stUserRecord += User.UserName + Seperator;
	stUserRecord += User.Password + Seperator;
	stUserRecord += to_string(User.Permissions);
	return stUserRecord;
}
stUsers ConvertUserLineToRecord(string Line, string SepeRator = "#//#")
{
	stUsers User;
	vector <string> vUsersData = SplitString(Line, SepeRator);
	if (vUsersData.size() >= 3)
	{
		User.UserName = vUsersData[0];
		User.Password = vUsersData[1];
		User.Permissions = stoi(vUsersData[2]);
	}
	return User;
}
vector <stUsers> LoadUsersDataFromFile(string UserFile)
{
	vector <stUsers> vUsersData;
	fstream MyFile;
	MyFile.open(UserFile, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		stUsers User;
		while (getline(MyFile, Line))
		{
			User = ConvertUserLineToRecord(Line);
			vUsersData.push_back(User);
			cout << "[" << Line << "]" << endl;
		}
		MyFile.close();
	}
	return vUsersData;
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
void PrintUsersRecord(stUsers User)
{
	cout << "| " << setw(15) << left << User.UserName;
	cout << "| " << setw(40) << left << User.Password;
	cout << "| " << setw(12) << left << User.Permissions;
}
void PrintSearchClient(sClient Client)
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
void PrintSearchUser(stUsers User)
{
	"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "User Name : " << User.UserName << endl;
	cout << "User Password : " << User.Password << endl;
	cout << "User Permission : " << User.Permissions << endl;
	cout <<"\n_______________________________________________________";

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
void ShowUsersLists()
{
	vector<stUsers>vUsers = LoadUsersDataFromFile(UserFile);
	cout << "\n\t\t\t\t\tUser Lists  (" << vUsers.size() << ")Users(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(40) << "Password";
	cout << "| " << left << setw(12) << "Permission";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vUsers.size() == 0)
		cout << "\t\t\t No Users Available In The System .";
	else
		for (stUsers& U : vUsers)
		{
			PrintUsersRecord(U);
			cout << endl;
		}
}
bool SearchClient(string Account,sClient &Client)
{
	vector <sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	for (sClient& C : vClient)
	{
		if (C.AccountNumber == Account)
		{
			Client = C;
			return true;
		}
	}
			return false;	
	
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
bool MarkUserForDeleteByUserName(string UserName, vector<stUsers>& vUsers)
{
	for (stUsers& U : vUsers)
	{
		if (U.UserName == UserName)
		{
			U.MarkForDelete = true;
			return true;
		}
	}
	return false;
}
string ReadAccount()
{
	string Account;
	cout << "enter the Account Number : ";
	getline(cin, Account);
	return Account;
}
string ReadUserName()
{
	string Name;
	cout << "enter User Name : ";
	getline(cin, Name);
	return Name;
}
void AddNewClient()
{
	
	system("cls");
	cout << "Adding New Client:\n\n";

	sClient Client = ReadNewClient();

	string stLine = ConvertRecordToLine(Client, " ");

	AddDataLineToFile("Client.txt", stLine);


}
void AddNewUsers()
{
	stUsers User;
	char AddMore;
	do {
		system("cls");
		cout << "-----------------------------------\n";
		cout << "\tAdd New User Screen\n";
		cout << "-----------------------------------\n";


		cout << "Enter User Name? ";
		getline(cin >> ws, User.UserName);
		while (UserExistByUserName(User.UserName, UserFile))
		{
			cout << "\n User With [ " << User.UserName << " ] already Exist ,Enter anther User :\n";
			getline(cin >> ws, User.UserName);

		}
		cout << "\n Enter Password : ";
		getline(cin >> ws, User.Password);

		User.Permissions = ReadPermission();

		string stLine = ConvertUsersRecordToLine(User);
		AddUsersDataLineToFile(UserFile, stLine);

		cout << "\nUser Added Successfully! :-)\n";

		cout << "Do You Want To Add More Users ?Y/N?";
		cin >> AddMore;
	} while (AddMore == 'Y' || AddMore == 'y');
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
vector<stUsers>SaveUserDataToFile(string UserFile, vector<stUsers>vUsers)
{
	fstream USERSFILE;
	USERSFILE.open(UserFile, ios::out);
	string DataLine;
	if (USERSFILE.is_open())
	{
		for (stUsers& U : vUsers)
		{
			if (U.MarkForDelete == false)
			{
				DataLine = ConvertUsersRecordToLine(U);
				USERSFILE << DataLine << endl;
			}
		}
		USERSFILE.close();
	}
	return vUsers;
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
bool FindUserByUserName(string UserName, vector<stUsers>vUsers, stUsers& User)
{
	for (stUsers U : vUsers)
	{
		if (U.UserName == UserName)
		{
			User = U;
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
		PrintSearchClient(Client);
	else
	cout << "\nClient with Account Number (" << Account << ") is Not Found!";

}
void ShowFindUserScreen()
{
	cout << "-----------------------\n";
	cout << "\tFind User Screen\n";
	cout << "-----------------------\n";

	vector<stUsers>vUsers = LoadUsersDataFromFile(UserFile);
	string UserName = ReadUserName();
	stUsers User;
	if (FindUserByUserName(UserName, vUsers, User))
		PrintSearchUser(User);
	else
		cout << "\nUser with User Name (" << UserName << ") is Not Found!";

}
bool DeleteClientByAccountNumber(string Account,vector<sClient> &vClient)
{
	sClient Client;
	char Answer = 'n';
	
	if (FindClientByAccountNumber(Account,vClient,Client))
	{
		PrintSearchClient(Client);
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
bool DeleteUser(string UserName, vector<stUsers>& vUsers)
{
	stUsers User;
	char Answer;
	if (FindUserByUserName(UserName, vUsers, User))
	{
		PrintSearchUser(User);
		cout << "\n Are your sure you want to delete this Client : y/n ?";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			if (UserName == "Admin")
			{
				cout << "Cannot Delete Admin";
				return false;
			}
			MarkUserForDeleteByUserName(UserName, vUsers);
			SaveUserDataToFile(UserFile, vUsers);
			cout << " \nUser Deleting Successfully \n";
			return true;
		}
	}
		else
		{
			cout << "\nUser with User Name (" << UserName << ") is Not Found!";
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
	DeleteClientByAccountNumber(Account, vClient);

}
void ShowDeleteUser()
{
	cout << "-----------------------\n";
	cout << "\tDeleting Users Screen\n";
	cout << "-----------------------\n";

	vector <stUsers>vUsers = LoadUsersDataFromFile(UserFile);
	string UserName = ReadUserName();
	DeleteUser(UserName, vUsers);


}
bool UpdateClientByAccountNumber(string Account, vector<sClient>& vClient)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(Account, vClient, Client))
	{
		PrintSearchClient(Client);
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
bool UpdateUsers(string UserName, vector<stUsers>& vUsers)
{
	stUsers User;
	char Answer = 'n';
	if (FindUserByUserName(UserName, vUsers, User))
	{
		PrintSearchUser(User);
		cout << "\n Are your sure you want to Ubdate this User : y/n ?";
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			for (stUsers& U : vUsers)
			{
				if (U.UserName == UserName)
				{
					U = ReadUserDataForUpdate(UserName);
					break;
				}
			}
			SaveUserDataToFile(UserFile, vUsers);
			vUsers = LoadUsersDataFromFile(UserFile);
			cout << " \nUser Ubdating Successfully \n";
			return true;
		}
	}
	else
	{
		cout << "\nUser with User Name (" << UserName << ") is Not Found!";
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
	UpdateClientByAccountNumber(Account, vClient);
}
void ShowUpdateUserScreen()
{
	cout << "-----------------------\n";
	cout << "\tUbdating User Screen\n";
	cout << "-----------------------\n";
	vector <stUsers>vUsers = LoadUsersDataFromFile(UserFile);
	string UserName = ReadUserName();
	UpdateUsers(UserName, vUsers);

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
void GoBackToUsersMenuOptions()
{
	cout << "\n\nPress any key to go back to Transaction Menu...";
	system("pause>0");
	ShowUsersScreen();
}
void GoBackToAtmMenuOptions()
{
	cout << "\n\nPress any key to go back to Transaction Menu...";
	system("pause>0");
	ShowAtmMenu();
}
short ReadMainMenuOption()
{
	cout << " CHOSE WHAT DO YOU WANT TO DO [1 TO 8] ?\n";
	short Choise = 0;
	cin >> Choise;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Choise;
}
short ReadAtmMainMenuOption()
{
	cout << " CHOSE WHAT DO YOU WANT TO DO [1 TO 5] ?\n";
	short Choise = 0;
	cin >> Choise;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Choise;
}
short ReadTransactionMenu()
{
	cout << " CHOSE WHAT DO YOU WANT TO DO [1 TO 4] ?\n";
	short Choise = 0;
	cin >> Choise;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Choise;
}
short ReadUsersMenuOptions()
{
	cout << " CHOSE WHAT DO YOU WANT TO DO [1 TO 6] ?\n";
	short Choise = 0;
	cin >> Choise;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
		PrintSearchClient(Client);
		cout << "\n PLEASE ENTER DEPOSIT NUMBER ?";
		cin >> Deposit;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		for (sClient& C : vClient)
		{
			if (C.AccountNumber == Account)
			{
				C.AccountBalance += Deposit;
				break;
			}
		}
		SaveClientsDataToFile(ClientsFileName, vClient);
		cout << " \nAccount Deposit Successfully \n";
		return true;
	}
	else
	{
		cout << "\nClient with Account Number (" << Account << ") is Not Found!";
		return false;
	}
}
bool AtmDepositFromClient(string Account, vector<sClient>& vClient)
{
	sClient Client;
	int Deposit;
	if (FindClientByAccountNumber(Account, vClient, Client))
	{
		cout << "\n PLEASE ENTER A POSITIVE DEPOSIT NUMBER ?";
		cin >> Deposit;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		for (sClient& C : vClient)
		{
			if (C.AccountNumber == Account)
			{
				C.AccountBalance += Deposit;
				CurrentClient.AccountBalance = C.AccountBalance;
				break;
			}
		}
		SaveClientsDataToFile(ClientsFileName, vClient);
		cout << " \nAccount Deposit Successfully \n";
		cout << "\n New Balance is : " << CurrentClient.AccountBalance;
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
	cout << "\tDeposit Account Screen\n";
	cout << "-----------------------\n";
	string Account = ReadAccount();
	vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	DepositFromClient(Account, vClient);
}
void showAtmDepositScreen()
{
	cout << "-----------------------\n";
	cout << "\tDeposit Screen\n";
	cout << "-----------------------\n\n";
	vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	AtmDepositFromClient(CurrentClient.AccountNumber, vClient);
}
short GetQuickWithdrawAmount(short Options)
{
	switch (Options)
	{
	case 1:return 20;
	case 2:return 50;
	case 3:return 100;
	case 4:return 200;
	case 5:return 400;
	case 6:return 600;
	case 7:return 800;
	case 8:return 1000;
	default: return 0;

	}
}
bool WithDrawFromClient(string Account, vector<sClient>& vClient)
{
	sClient Client;
	int Withdraw;
	if (FindClientByAccountNumber(Account, vClient, Client))
	{
		PrintSearchClient(Client);

		for (sClient& C : vClient)
		{
			if (C.AccountNumber == Account)
			{
				cout << "\n PLEASE ENTER WITHDRAW AMOUNT ?";
				cin >> Withdraw;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
			cout << " \nAccount Withdraw Successfully \n";
			return true;
		}
	
	else
	{
		cout << "\nClient with Account Number (" << Account << ") is Not Found!";
		return false;
	}
}
bool QuickWithDrawFromClient(string Account, vector<sClient>& vClient)
{
	sClient Client;
	short Withdraw;
	char Answer = 'n';
	if (FindClientByAccountNumber(Account, vClient, Client))
	{
		for (sClient& C : vClient)
		{
			if (C.AccountNumber == Account)
			{
				cout << "Chose What To Withdraw from [1] to [8] ? ";
				cin >> Withdraw;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				while (GetQuickWithdrawAmount(Withdraw) > C.AccountBalance)
				{
					cout << "\nAmount Exceeds The Balance, You Can Withdraw Up To: " << C.AccountBalance << endl;
					cout << "Please Choose another option: ";
					cin >> Withdraw;
				}
			}
			cout << "Are Your Sure You Want Perform This Transaction ? ";
			cin >> Answer;
			if (Answer == 'Y' || Answer == 'y')
			{
				C.AccountBalance -= GetQuickWithdrawAmount(Withdraw);
				CurrentClient.AccountBalance = C.AccountBalance;

				SaveClientsDataToFile(ClientsFileName, vClient);
				cout << " \nAccount Withdraw Successfully \n";
				cout << "New Balance is : " << CurrentClient.AccountBalance;
				return true;
			}
		}

	}
	else
	{
		cout << "\nClient with Account Number (" << Account << ") is Not Found!";
		return false;
	}
	return false;
}
bool NormalWithDrawFromClient(string Account, vector<sClient>& vClient)
{
	sClient Client;
	int Withdraw;
	char Answer = 'n';
	if (FindClientByAccountNumber(Account, vClient, Client))
	{
		for (sClient& C : vClient)
		{
			if (C.AccountNumber == Account)
			{
				cin >> Withdraw;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				while (Withdraw % 5 != 0)
				{
					cout << "Please Enter another Amount multple of 5's : ";
					cin >> Withdraw;
				}
				while (Withdraw > C.AccountBalance)
				{
					cout << "\nAmount Exceeds The Balance, You Can Withdraw Up To: " << C.AccountBalance << endl;
					cout << "Please Enter another Amount: ";
					cin >> Withdraw;
				}
				cout << "Are Your Sure You Want Perform This Transaction ? ";
				cin >> Answer;
				if (Answer == 'Y' || Answer == 'y')
				{
					C.AccountBalance -= Withdraw;
					CurrentClient.AccountBalance = C.AccountBalance;

					SaveClientsDataToFile(ClientsFileName, vClient);
					cout << " \nAccount Withdraw Successfully \n";
					cout << "New Balance is : " << CurrentClient.AccountBalance;
					return true;
				}

			}
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << Account << ") is Not Found!";
		return false;
	}
	return false;

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
void ShowQuickWithdrawScreen()
{
	cout << "============================================\n";
	cout << "\t\t Quick Withdraw \n";
	cout << "============================================\n";
	cout << setw(10) << "[1] 20 \t\t\t [2] 50\n";
	cout << setw(10) << "[3] 100 \t\t [4] 200\n";
	cout << setw(10) << "[5] 400 \t\t [6] 600\n";
	cout << setw(10) << "[7] 800 \t\t [8] 1000\n";
	cout << "  [9] Exit.\n";
	cout << "============================================\n";
	cout << "Your Balance Is : " << CurrentClient.AccountBalance << endl;
	vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	QuickWithDrawFromClient(CurrentClient.AccountNumber, vClient);
}
void ShowNormalWithdrawScreen()
{
	cout << "============================================\n";
	cout << "\t\t Normal Withdraw Screen \n";
	cout << "============================================\n";
	cout << "Enter an amount multiple of 5's ?  ";
	vector<sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);
	NormalWithDrawFromClient(CurrentClient.AccountNumber, vClient);
}
void ShowAtmCheckBalanceScreen()
{
	cout << "============================================\n";
	cout << "\t\t Normal Withdraw Screen \n";
	cout << "============================================\n";
	cout << "Your Balance Is : " << CurrentClient.AccountBalance;
}
void PerFormTransactionMenuoption(enTransactionMenu TransactionMenu)
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
		ShowMainMenu();
		break;
	}
	}
}
void PerFormUsersMenuOptions(enUsersMenuOptions UserMenuOptions)
{
	switch (UserMenuOptions)
	{
	case enUsersMenuOptions::LISTSUSERS:
	{
		system("cls");
		ShowUsersLists();
		GoBackToUsersMenuOptions();
		break;
	}
	case enUsersMenuOptions::ADDNEWUSER:
	{
		system("cls");
		AddNewUsers();
		GoBackToUsersMenuOptions();
		break;
	}
	case enUsersMenuOptions::DELETEUSER:
	{
		system("cls");
		ShowDeleteUser();
		GoBackToUsersMenuOptions();
		break;
	}
	case enUsersMenuOptions::UPDATEUSER:
	{
		system("cls");
		ShowUpdateUserScreen();
		GoBackToUsersMenuOptions();
		break;
	}
	case enUsersMenuOptions::FINDUSER:
	{
		system("cls");
		ShowFindUserScreen();
		GoBackToUsersMenuOptions();
		break;
	}
	case enUsersMenuOptions::MAINMENU:
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
	PerFormTransactionMenuoption((enTransactionMenu)ReadTransactionMenu());
}
void ShowUsersScreen()
{
	cout << "===============================\n";
	cout << "    MANAGE USER MENU SCREEN\n";
	cout << "===============================\n";
	cout << "\n[1] LISTS USERS .\n";
	cout << "[2] ADD NEW USER .\n";
	cout << "[3] DELETE USER .\n";
	cout << "[4] UPDATE USER .\n";
	cout << "[5] FIND USER .\n";
	cout << "[6] Main Menu .\n";
	cout << "===============================\n";
	PerFormUsersMenuOptions((enUsersMenuOptions)ReadUsersMenuOptions());
}
void PerFormMainMenuOption(enMainMenuOptions MainMenuOptions)
{
	switch (MainMenuOptions)
	{
	case enMainMenuOptions::SHOWINGCLIENTLISTS:
	{
		if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::ShowClientLists))
		{
			AccessDeniedScreen();
			break;
		}

		system("cls");
		PrintAllClientsData();
		GoBackToMainMenu();
		break;
	}
	case enMainMenuOptions::ADDNEWCLIENT:
	{
		if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::AddClient))
		{
			AccessDeniedScreen();
			break;
		}

		system("cls");
		AddNewClient();
		GoBackToMainMenu();
		break;
	}
	case enMainMenuOptions::DELETECLIENT:
	{
		if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::DeleteClient))
		{
			AccessDeniedScreen();
			break;
		}

		system("cls");
		ShowDeleteClient();
		GoBackToMainMenu();
		break;
	}
	case enMainMenuOptions::UPDATECLIENTINFO:
	{
		if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::UpdateClient))
		{
			AccessDeniedScreen();
			break;
		}

		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenu();
		break;
	}
	case enMainMenuOptions::FINDCLIENT:
	{
		if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::FindClient))
		{
			AccessDeniedScreen();
			break;
		}

		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;
	}
	case enMainMenuOptions::TRANSACTIONS:
	{
		if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::Transactions))
		{
			AccessDeniedScreen();
			break;
		}

		system("cls");
		ShowTransactionsScreen();
		GoBackToMainMenu();
		break;
	}
	case enMainMenuOptions::MANAGEUSERS:
	{
		if (!CheckAccessPermission(CurrentUser.Permissions, enPermissions::ManageUsers))
		{
			AccessDeniedScreen();
			break;
		}

		system("cls");
		ShowUsersScreen();
		GoBackToMainMenu();
		break;
	}
	case enMainMenuOptions::LOGOUT:
	{
		system("cls");
		Login();
		break;
	}

	}

}
void PerFormAtmMainMenuOption(enAtmMainMenuOptions AtmMainMenuOprions)
{
	switch (AtmMainMenuOprions)
	{
	case enAtmMainMenuOptions::enQuickWithdraw:
	{
		system("cls");
		ShowQuickWithdrawScreen();
		GoBackToAtmMenuOptions();
		break;
	}
	case enAtmMainMenuOptions::enNormalWithdraw:
	{
		system("cls");
		ShowNormalWithdrawScreen();
		GoBackToAtmMenuOptions();
		break;
	}
	case enAtmMainMenuOptions::enDeposit:
	{
		system("cls");
		showAtmDepositScreen();
		GoBackToAtmMenuOptions();
		break;
	}
	case enAtmMainMenuOptions::enCheckBalance:
	{
		system("cls");
		ShowAtmCheckBalanceScreen();
		GoBackToAtmMenuOptions();
		break;
	}
	case enAtmMainMenuOptions::enLogOut:
	{
		system("cls");
		return;
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
	cout << " [7] Manage Users .\n";
	cout << " [8] EXIT.\n";
	cout << "===================================================\n";
	PerFormMainMenuOption((enMainMenuOptions)ReadMainMenuOption());
}
void ShowAtmMenu()
{
	system("cls");
	cout << "------------------------------------------------\n";
	cout << "================================================\n";
	cout << setw(30) << right << "ATM MAIN MENU SCREEN \n";
	cout << "================================================\n";
	cout << " [1] QUICK WITHDRAW .\n";
	cout << " [2] NORMAL WITHDRAW .\n";
	cout << " [3] DEPOSIT .\n";
	cout << " [4] CHECK BALANCE .\n";
	cout << " [5] LOGOUT .\n";
	cout << "===================================================\n";
	PerFormAtmMainMenuOption((enAtmMainMenuOptions)ReadAtmMainMenuOption());
}
void Login()
{
	string UserName,Password;
	bool LoginFailed = false;
	vector<stUsers>vUsers;
	
	do {
		vUsers = LoadUsersDataFromFile(UserFile);
		system("cls");
		cout << "================================\n";
		cout << "          LogIn Screen\n";
		cout << "================================\n";
		if (LoginFailed)
		{
			cout << "Invalid UserName/Password!\n";
		}


		cout << "\n Enter UserName : ";
		getline(cin >> ws, UserName);
		cout << "\n Enter Password : ";
		getline(cin >> ws, Password);

		for (stUsers& U : vUsers)
		{
			if (U.UserName == UserName && U.Password == Password)
			{
				CurrentUser = U;
				ShowMainMenu();
				return;
			}
		}
		LoginFailed = true;
	} while (true);
}
void LoginAtm()
{
	string AccountNumber, PinCode;
	bool LoginFailed = false;
	vector<sClient>vClient;

	do {
		vClient = LoadCleintsDataFromFile(ClientsFileName);
		system("cls");
		cout << "================================\n";
		cout << "          LogIn Screen\n";
		cout << "================================\n";
		if (LoginFailed)
		{
			cout << "Invalid Account Number/Pin Code!\n";
		}


		cout << "\n Enter Account Number : ";
		getline(cin >> ws, AccountNumber);
		cout << "\n Enter Pin Code : ";
		getline(cin >> ws, PinCode);

		for (sClient& C : vClient)
		{
			if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
			{
				CurrentClient = C;
				ShowAtmMenu();
				return;
			}
		}
		LoginFailed = true;
	} while (true);
}
int main()
{
	while (true)
	{
		LoginAtm();
	}
	system("pause>0");
	return 0;
}