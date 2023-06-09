#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;



enum enATMMenuOption {

	eQuickWithdraw = 1,
	eNormalWithdraw = 2,
	eDeposit = 3,
	eTotalBalances = 4,
	eLogout = 5
};


const string ClientsFileName = "Clients.txt";

void ShowQuickWithdrawScreen();
void ShowNormalWithdrawScreen();
void ShowDepositScreen();
void ShowATMMainMenu();
void Login();

struct sClient {
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

sClient CurrentClient;

vector<string> SplitString(string S1, string Delim) {
	vector<string> vString;
	short pos = 0;
	string sWord;
	// define a string variable  
	// use find() function to get the position of the delimiters  
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos);
		// store the word   if (sWord != "")       
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	} if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.  
	} return vString;
}


sClient ConvertLinetoRecord(string Line, string Seperator = "#//#") {
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);//cast string to double;

	return Client;
}


string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {


	string stClientRecord = "";


	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);


	return stClientRecord;


}

void PrintClientCard(sClient Client) {
	cout << "\n_______________________________________________________";
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code     : " << Client.PinCode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << "\n_______________________________________________________";

}


vector <sClient> LoadClientsDataFromFile(string FileName) {

	fstream MyFile;
	vector <sClient> vClients;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {

		string Line;
		sClient Client;

		while (getline(MyFile, Line)) {

			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);

		}
	}


	MyFile.close();

	return vClients;

}


bool ClientExistsByAccountNumber(string AccountNumber, string FileName) {

	fstream MyFile;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {

		string Line;
		sClient Client;

		while (getline(MyFile, Line)) {

			Client = ConvertLinetoRecord(Line);

			if (Client.AccountNumber == AccountNumber) {

				MyFile.close();
				return true;
			}
		}

		MyFile.close();

	}
	return false;
}

sClient ReadNewClient() {
	sClient Client;


	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);


	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName)) {

		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
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


short ReadQuickWithdrawOption() {

	short Choice = 0;

	do {

	cout << "Choose what do you want to do? [1 to 9]? ";
	cin >> Choice;


	} while (Choice < 1 || Choice > 9);
		
	return  Choice;
	}






short ReadATMMainMenuOption() {

	short Choice = 0;
	cout << "Choose what do you want to do? [1 to 5]? ";
	cin >> Choice;
	return Choice;

}

void GoBackToMainMenu() {

	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowATMMainMenu();

}

void PrintClientRecordLine(sClient Client) {

	cout << "| " << setw(15) << left << Client.AccountNumber;

	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;


}



void SaveDataLineToFile(string FileName, string stLine) {

	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open()) {

		MyFile << stLine << endl;

		MyFile.close();
	}

}
vector <sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients) {

	fstream MyFile;
	MyFile.open(FileName, ios::out);//overwrite


	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient C : vClients)
		{
			if (C.MarkForDelete == false)
			{ //we only write records that are not marked for delete.  

				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	} return vClients;

}



bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client) {
	for (sClient C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}

	}

	return false;

}


bool FindClientByAccountNumberAndPassword(string AccountNumber, string Password, sClient& Client) {

	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	for (sClient & C : vClients) {
		if (C.AccountNumber == AccountNumber && C.PinCode == Password) {
			Client = C;
			return true;
		}

	}

	return false;

}



string ReadClientAccountNumber() {

	string AccountNumber = "";
	cout << "\nPlease enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;


}


bool DepositBalaneToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients) {
	char Answer = 'n';

	cout << "\n\nAre you sure you want perform this transaction? y/n ? ";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y') {

		for (sClient& C : vClients) {

			if (C.AccountNumber == AccountNumber) {

				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\nDone Successfully new balance is: " << C.AccountBalance;

				return true;

			}

		}
	}
	return false;
}


short ReadDepositAmount() {
	double Amount;
	cout << "\nEnter a positive Deposit Amount? ";
	cin >> Amount;
	while (Amount <= 0) {
		cout << "\nEnter a positive Deposit Amount? ";
		cin >> Amount;
	}
	return Amount;
}

void PerformDepositOption() {
	double DepositAmount = ReadDepositAmount();

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);


	DepositBalaneToClientByAccountNumber(CurrentClient.AccountNumber, DepositAmount, vClients);
	CurrentClient.AccountBalance += DepositAmount;

}

void ShowDepositScreen() {
	cout << "==========================================\n";
	cout << "\tDeposit Screen";
	cout << "\n==========================================\n";

	PerformDepositOption();
}

short getQuickWithdrawAmount(short QuickWithdrawOption) {

	switch (QuickWithdrawOption)
	{
	case 1:
		return 20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;
	}
}

void PerformenQuickWithdrawOption(short QuickWithdrawOption) {

	if (QuickWithdrawOption == 9) {

		return;
	}


	short WithdrawBalance = getQuickWithdrawAmount(QuickWithdrawOption);

	if (WithdrawBalance > CurrentClient.AccountBalance) {

		cout << "\nThe amount exceeds your balance, make another choice.\n";
		cout << "Press Anykey to continue...";
		system("pause>0");
		ShowQuickWithdrawScreen();
		return;
	}

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	DepositBalaneToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawBalance * -1, vClients);
	CurrentClient.AccountBalance -= WithdrawBalance;

}


short ReadWithdrawAmount() {
	int Amount;
	cout << "\n Enter an amount multiple of 5's ?";
	cin >> Amount;
	while (Amount % 5 != 0) {
		cout << "\n Enter an amount multiple of 5's ?";
		cin >> Amount;
	}

	return Amount;

}

void ShowQuickWithdrawScreen() {
	system("cls");
	cout << "==========================================\n";
	cout << "\tQuick Withdraw Screen";
	cout << "\n==========================================\n";

	cout << "\t[1] 20 \t\t"  <<  "[2] 50\n";
	cout << "\t[3] 100 \t" << "[4] 200\n";
	cout << "\t[5] 400 \t" << "[6] 600\n";
	cout << "\t[7] 800 \t" << "[8] 1000\n";
	cout << "\t[9] Exit";
	cout << "\n==========================================\n";
	cout << "your balance is " << CurrentClient.AccountBalance << endl;

	PerformenQuickWithdrawOption(ReadQuickWithdrawOption());


}

void PerformNormalWithdrawOption() {

	int WithdrawBalance = ReadWithdrawAmount();

	if (WithdrawBalance > CurrentClient.AccountBalance) {
		cout << "the amount exceeds your balance,make another choice.";
		cout << "\n Press AnyKey to continue...";
		system("pause>0");
		ShowNormalWithdrawScreen();
		return;
	}
		vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	    DepositBalaneToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawBalance * -1, vClients);
		CurrentClient.AccountBalance -= WithdrawBalance;
}

	

void ShowNormalWithdrawScreen() {

	cout << "==========================================\n";
	cout << "\tNormal Withdraw Screen";
	cout << "\n==========================================\n";

	PerformNormalWithdrawOption();
}




void ShowCheckBalanceScreen() {
	cout << "==========================================\n";
	cout << "\t\tCheck Balance Screen\n";
	cout << "==========================================\n";
	cout << "Your Balance is: " << CurrentClient.AccountBalance;
}


void PerformATMMainMenuOptions(enATMMenuOption ATMMainMenuOption) {

	switch (ATMMainMenuOption)
	{
	case enATMMenuOption::eQuickWithdraw:
		system("cls");
		ShowQuickWithdrawScreen();
		GoBackToMainMenu();
		break;
	case enATMMenuOption::eNormalWithdraw:
		system("cls");
		ShowNormalWithdrawScreen();
		GoBackToMainMenu();

		break;
	case enATMMenuOption::eDeposit:
		system("cls");
		ShowDepositScreen();
		GoBackToMainMenu();

		break;
	case enATMMenuOption::eTotalBalances:
		system("cls");
		ShowCheckBalanceScreen();
		GoBackToMainMenu();

		break;
	
	case enATMMenuOption::eLogout:
		system("cls");
		Login();
		break;

	}

}


void ShowATMMainMenu() {

	system("cls");
	cout << "===========================================\n";
	cout << "\t\tATM Main Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "===========================================\n";
	PerformATMMainMenuOptions((enATMMenuOption)ReadATMMainMenuOption());
}


bool LoadClientInfo(string AccountNumber, string PinCode) {


	if (FindClientByAccountNumberAndPassword(AccountNumber, PinCode, CurrentClient)) {
		return true;
	}
	return false;
}


void Login() {

	bool LoginFailed = false;
	string AccountNumber, PinCode;
	do {
		system("cls");
		cout << "-------------------------------------------\n";
		cout << "\t\tLogin Screen\n";
		cout << "-------------------------------------------\n";


		if (LoginFailed) {
			cout << "Invalid AccountNumber/PinCode!" << endl;
		}


		cout << "Enter Account Number? ";
		cin >> AccountNumber;
		cout << "Enter PinCode? ";
		cin >> PinCode;
		LoginFailed = !LoadClientInfo(AccountNumber, PinCode);

	} while (LoginFailed);

	ShowATMMainMenu();
}

int main() {
	Login();


	system("pause>0");

	return 0;
}

