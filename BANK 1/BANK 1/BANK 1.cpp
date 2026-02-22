#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
#include <limits>
using namespace std;
const string ClientFileName = "Client.txt";

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelet = false;
};

vector<string> SplitString(string Line, string Separator = "#**#")
{
	vector<string> vClient;
	size_t Pos = 0;
	string Word = "";

	while ((Pos = Line.find(Separator)) != std :: string :: npos)
	{
		Word = Line.substr(0, Pos);
		if (Word != "")
		{
			vClient.push_back(Word);
		}
		Line = Line.erase(0, Pos + Separator.length());
	}
	if (Line != "")
	{
		vClient.push_back(Line);
	}
	return vClient;
} 

sClient ConvertLineToData(string Line, string Separator = "#**#")
{
	vector<string> vClient = SplitString(Line ,Separator);
	sClient Client;

	if (vClient.size() >= 5)
	{
		Client.AccountNumber = vClient[0];
		Client.PinCode = vClient[1];
		Client.Name = vClient[2];
		Client.Phone = vClient[3];
		Client.AccountBalance = stod(vClient[4]);
	}
	return Client;
}

string ConvertDataToLine(sClient Client , string Separator = "#**#")
{
	string DataLine;
	DataLine += Client.AccountNumber + Separator;
	DataLine += Client.PinCode + Separator;
	DataLine += Client.Name + Separator;
	DataLine += Client.Phone + Separator;
	DataLine += to_string(Client.AccountBalance);

	return DataLine;
}

vector<sClient> LoadDataFromFile(string FileName)
{
	vector<sClient> vClient;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{

			Client = ConvertLineToData(Line);
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return vClient;
}

void PrintClientRecord(const sClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(const vector <sClient>& vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")Client(s).";
		cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (const sClient & Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

}

void PrintClientBalance(const sClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
double TotalBalance(const vector <sClient>& vClients)
{
	double TotalBalance = 0.00;
	for (sClient Client : vClients)
	{
		TotalBalance += Client.AccountBalance;
	}
	return TotalBalance;
}
void PrintAllClientBalance(const vector <sClient>& vClients)
{
	cout << "\n\t\t\t\t\tBalance List (" << vClients.size() << ")Client(s).";
	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	for (const sClient & Client : vClients)
	{
		PrintClientBalance(Client);
		cout << endl;
	}
	cout <<"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "                              Total Balance = " << TotalBalance(vClients) << endl;
}
void PrintClientCard(sClient Client)
{
	cout << "\nThe Following are the Client details: ";
	cout << "\n-------------------------------------------------------------";
	cout << "\nAccount Number: " << Client.AccountNumber;
	cout << "\nPin Code: " << Client.PinCode;
	cout << "\nName: " << Client.Name;
	cout << "\nPhone: " << Client.Phone;
	cout << "\nAccount Balanc: " << Client.AccountBalance;
	cout << "\n-------------------------------------------------------------";

}

sClient AddNewClient()
{
	sClient Client;
	cout << "-------------------------------------------------------------";
	cout << "\nEnter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);

	cout << "Enter Pin Code? ";
	getline(cin , Client.PinCode);

	cout << "Enter Name? ";
	getline(cin , Client.Name);

	cout << "Enter Phone? ";
	getline(cin , Client.Phone);

	cout << "Enter Account Balance? ";
	cin >> Client.AccountBalance;
	cout << "\n\nClient added successfully.";
	cout << "\n-------------------------------------------------------------";

	return Client;
}

vector<sClient> SaveClientDataToFile(string FileName,vector<sClient >vClient)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	if (MyFile.is_open())
	{
		string DataLine;

		for (sClient C : vClient)
		{
			if(C.MarkForDelet == false)
			{
				//we only write records that are not marked for delete.

				DataLine = ConvertDataToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClient;
}

void MenueAddNewClient(sClient Client, vector<sClient>& vClient)
{
	cout << "\n=============================================================" << endl;
	cout << "                       Add New Client                        " << endl;
	cout << "=============================================================" << endl;
	cout << "   Add New Client: " << endl;
	
	Client = AddNewClient();
	vClient.push_back(Client);
	SaveClientDataToFile(ClientFileName, vClient);

}

bool FindClientByAccountNumber(string AccountNumber, const vector<sClient>& vClient, sClient& Client)
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

void PrintFindClientScrean(string AccountNumber)
{
    vector<sClient> vClients = LoadDataFromFile(ClientFileName);
    sClient Client;
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }
   
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClient)
{
	for (sClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelet = true;
			return true;
		}
	}
	return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	return Client;
}

string ReadClientAccountNumber()
{
	string AccountNumber;
	cout << "Please Enter Account Number? ";
	getline(cin >> ws, AccountNumber);
	return AccountNumber;
}

bool DeleteClientDataByAccountNumber(string AccountNumber, vector<sClient>& vClient, sClient& Client)
{
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{

		PrintClientCard(Client);

		char Answer = 'n';
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			MarkClientForDeleteByAccountNumber(AccountNumber, vClient);
			SaveClientDataToFile(ClientFileName, vClient);

			vClient = LoadDataFromFile(ClientFileName);
			cout << "\n\nClient Deleted Successfully.";
			
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		
		return false;
	}
}

bool UpdateClientDataByAccountNumber(string AccountNumber, vector<sClient>& vClient, sClient& Client)
{
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{

		PrintClientCard(Client);

		char Answer = 'n';
		cout << "\n\nAre you sure you want Update this client? y/n ? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			for (sClient& C : vClient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
				
			}
			SaveClientDataToFile(ClientFileName, vClient);
			cout << "\n\nClient Updated Successfully.";
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
		
		return false;
	}
}

bool WithDrawToClient(string AccountNumber, vector<sClient>& vClient, sClient& Client)
{
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintClientCard(Client);

		char Answer = 'n';
		cout << "\n\nAre you sure you want WithDraw this Account? y/n ? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			double Amount = 0;

			cout << "Enter WithDraw Amount: ";
			cin >> Amount;
			if ( Amount <= 0)
			{
				cout << "Invalid Amount!\n";
				return false;
			}
		
			for (sClient& C : vClient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					if (Amount > C.AccountBalance)
					{
						cout << "Invalid Amount!\n";
						return false;
					}

					C.AccountBalance -= Amount;

					cout << "\nWithDraw Done Successfully!\n";
					cout << "New Balance = " << C.AccountBalance << endl;

					return true;
				}
			}

		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";

		return false;
	}
}

bool DepositToClient(string AccountNumber, vector<sClient>& vClient, sClient& Client)
{
	if (FindClientByAccountNumber(AccountNumber, vClient, Client))
	{
		PrintClientCard(Client);

		char Answer = 'n';
		cout << "\n\nAre you sure you want Deposit this Account? y/n ? ";
		cin >> Answer;

		if (Answer == 'Y' || Answer == 'y')
		{
			double Amount = 0;

			cout << "Enter Deposit Amount: ";
			cin >> Amount;

			if (Amount <= 0)
			{
				cout << "Invalid Amount!\n";
				return false;
			}
			for (sClient& C : vClient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C.AccountBalance += Amount;

					cout << "\nDeposit Done Successfully!\n";
					cout << "New Balance = " << C.AccountBalance << endl;

					return true;
				}
			}

		}
		else
		{
			return false;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";

		return false;
	}
}
short ReadAnswerinMainMenueScrean()
{
	short Answer = 0;
	cin >> Answer;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Answer;
}

short TransactionsMenueScreen()
{
	cout << "=============================================================" << endl;
	cout << "                    TransactionsMenueScreen                  " << endl;
	cout << "=============================================================" << endl;
	cout << "        [1] Deposit." << endl;
	cout << "        [2] Withdraw." << endl;
	cout << "        [3] Total Balances." << endl;
	cout << "        [4] Exit." << endl;
	cout << "Chooes What Do You Want to Do?[ 1 TO 4]?";

	short Chooes = ReadAnswerinMainMenueScrean();
	return Chooes;
}

short MainMenueScrean()
{
	cout << "=============================================================" << endl;
	cout << "                       MainMenueScrean                       " << endl;
	cout << "=============================================================" << endl;
	cout << "        [1] Show Clients List." << endl;
	cout << "        [2] Add New Client." << endl;
	cout << "        [3] Delete Client." << endl;
	cout << "        [4] Update Client Info." << endl;
	cout << "        [5] Find Client." << endl;
	cout << "        [6] Transactions." << endl;
	cout << "        [7] Exit." << endl;
	cout << "Chooes What Do You Want to Do?[ 1 TO 7]?" ;
	
	short Chooes = ReadAnswerinMainMenueScrean();
	return Chooes;
}

void ActionBox()
{
	bool Exit = false;

	while (!Exit)
	{
		vector<sClient> vClients = LoadDataFromFile(ClientFileName);
		short choice = MainMenueScrean();
		switch (choice)
		{
		case 1:
			PrintAllClientsData(vClients);
			cout << "\nPress any key to go back to main menue...";
			system("pause>0");
			system("cls");
			break;

		case 2:
		{
			sClient Client;
			MenueAddNewClient(Client, vClients);
			cout << "\nPress any key to go back to main menue...";
			system("pause>0");
			system("cls");
			break;
		}

		case 3:
		{
			string AccountNumber = ReadClientAccountNumber();
			sClient Client;
			DeleteClientDataByAccountNumber(AccountNumber, vClients, Client);
			cout << "\nPress any key to go back to main menue...";
			system("pause>0");
			system("cls");
			break;
		}
		case 4:
		{
			string AccountNumber = ReadClientAccountNumber();
			sClient Client;
			UpdateClientDataByAccountNumber(AccountNumber, vClients, Client);
			cout << "\nPress any key to go back to main menue...";
			system("pause>0");
			system("cls");
			break;
		}
		case 5:
		{
			string AccountNumber = ReadClientAccountNumber();
			PrintFindClientScrean(AccountNumber);
			cout << "\nPress any key to go back to main menue...";
			system("pause>0");
			system("cls");
			break;
		}
		case 6:
		{
			while (!Exit)
			{
				system("cls");

				vector<sClient> vClients = LoadDataFromFile(ClientFileName);
	        	short choiceTransaction = TransactionsMenueScreen();

				switch (choiceTransaction)
				{
				    case 1:
				    {
						string AccountNumber = ReadClientAccountNumber();
						sClient Client;
						DepositToClient(AccountNumber, vClients, Client);
						cout << "\nPress any key to go back to main menue...";
						system("pause>0");
						system("cls");
						break;
				    }
				    case 2:
				    {
						string AccountNumber = ReadClientAccountNumber();
						sClient Client;
						WithDrawToClient(AccountNumber, vClients, Client);
						cout << "\nPress any key to go back to main menue...";
						system("pause>0");
						system("cls");
						break;
				    }
				    case 3:
				    {
						system("cls");
						PrintAllClientBalance(vClients);
						cout << "\nPress any key to go back to main menue...";
						system("pause>0");
						system("cls");
						break;
				    }
				    case 4:
				    {
						system("cls");
						MainMenueScrean();
				    	break;
				    }
				}
			}
		}
		
		case 7:
			Exit = true;
			break;
		}
	}
}

int main()
{
	ActionBox();

	return 0;
}
