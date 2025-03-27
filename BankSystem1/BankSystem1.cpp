#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "myLib.h"

using namespace std;

enum eMode { Show = 1, Add = 2, Delete = 3, update = 4, Find = 5, Exit = 6 };

struct sClient
{
	string accountNumber;
	string pinCode;
	string name;
	string phone;
	float balance = 0.0;
	bool deleteFlag = false;
};

// global variables
const string clientFileName = "clients.txt";
const string delimiter = "|#|";

//---------------------------------------------------------------

// definition
sClient readNewClientInfo(string);

void resetScreen()
{
	system("cls");
}

void printMainMenu()
{
	cout << "\t\t------------------------------\n";
	cout << "\t\t      M A I N    M E N U      \n";
	cout << "\t\t------------------------------\n\n";

	cout << "\t\t [1] Show Client List\n";
	cout << "\t\t [2] Add New Client \n";
	cout << "\t\t [3] Delete Client \n";
	cout << "\t\t [4] Update Client Info\n";
	cout << "\t\t [5] Find Client\n";
	cout << "\t\t [6] Exit\n\n";

	cout << "\t\t------------------------------\n\n";
}

eMode readMode()
{
	short answer = 0;

	do {

		cout << "\tplz Choose number [1 - 6] : ";
		cin >> answer;
		cin.ignore(100, '\n');

	} while (answer < 1 || answer > 6);

	return (eMode)answer;
}

string clientRecordToLine(sClient client, string seperator)
{
	string line = "";

	line += client.accountNumber + seperator;
	line += client.pinCode + seperator;
	line += client.name + seperator;
	line += client.phone + seperator;
	line += to_string(client.balance);

	return line;
}

void addDataLineToFile(string fileName, string line)
{
	fstream clientFile;

	clientFile.open(fileName, ios::out | ios::app);
	if (clientFile.is_open())
	{
		clientFile << line << endl;

		clientFile.close();
	}
}

bool updateFile(vector<sClient> vClients, string fileName)
{
	fstream clientFile;

	clientFile.open(fileName, ios::out);
	if (clientFile.is_open())
	{
		string line = "";

		for (sClient& c : vClients)
		{
			if (c.deleteFlag == false)
			{
				line = clientRecordToLine(c, delimiter);
				clientFile << line << endl;
			}
		}

		clientFile.close();
		return true;
	}

	return false;
}

bool searchClientByAccountNumber(vector<sClient>& vAllClient, string toSearch, sClient& client)
{
	for (sClient& c : vAllClient)
	{
		if (c.accountNumber == toSearch)
		{
			client = c;
			return true;
		}
	}

	return false;
}

void printClientInfo(sClient client)
{
	cout << "\n\n----------------------------------\n";
	cout << "number  : " << client.accountNumber << endl;
	cout << "pinCode : " << client.pinCode << endl;
	cout << "name    : " << client.name << endl;
	cout << "phone   : " << client.phone << endl;
	cout << "balance : " << client.balance;
	cout << "\n----------------------------------\n";
}

sClient lineToClientRecord(string line)
{
	sClient c;
	vector<string> vClientRecord;

	vClientRecord = mystd::splitString(line, delimiter);

	c.accountNumber = vClientRecord[0];
	c.pinCode = vClientRecord[1];
	c.name = vClientRecord[2];
	c.phone = vClientRecord[3];
	c.balance = stof(vClientRecord[4]);

	return c;
}

vector<sClient> loadClientsFromFile(string fileName)
{
	vector<sClient> vClients;

	fstream clientFile;
	clientFile.open(fileName, ios::in);

	if (clientFile.is_open())
	{
		sClient client;
		string line = "";

		while (getline(clientFile, line))
		{
			client = lineToClientRecord(line);
			vClients.push_back(client);
		}

		clientFile.close();
	}

	return vClients;
}

//------------------------------show client list fucntion

void printShowClientTitle()
{
	cout << "\n                                  C L I E N T    R E C O R D S";
	cout << "\n__________________________________________________________________________________________________\n";
	cout << "   Number   |  pincode   |            name               |       phone       |      balance      |\n";
	cout << "__________________________________________________________________________________________________\n";
}

void printClientRecordList(sClient client)
{

	cout << "  " << setw(10) << left << client.accountNumber << "| ";
	cout << setw(11) << left << client.pinCode << "| ";
	cout << setw(30) << left << client.name << "| ";
	cout << setw(18) << left << client.phone << "| ";
	cout << setw(18) << left << client.balance << "| ";

	cout << endl;

}

void showClientList(vector<sClient>& vClients)
{
	resetScreen();
	printShowClientTitle();

	for (sClient& c : vClients)
	{
		printClientRecordList(c);
	}

	cout << "\n\nlist clients number = " << vClients.size() << endl;
	cout << "\nthis is all clients ...\n";
	system("pause");

}

//----------------------------------- add client fucntion

bool matchCaseAccountNumber(vector<sClient> vClients, string accountNumber)
{
	for (sClient& c : vClients)
	{
		if (c.accountNumber == accountNumber)
			return true;
	}

	return false;
}

void addNewClient(vector<sClient>& vClients)
{
	sClient newClient;
	string newAccountNumber;

	resetScreen();
	cout << "\n           A D D    C L I E N T \n\n";

	newAccountNumber = mystd::readString("enter account number : ");
	while (matchCaseAccountNumber(vClients, newAccountNumber))
	{
		cout << "there is exist [" << newAccountNumber << "] account number..." << endl;
		newAccountNumber = mystd::readString("plz enter another account number : ");
	}

	// reach here, no match case. good
	newClient = readNewClientInfo(newAccountNumber);

	vClients.push_back(newClient); // adding to the main vector

	//updateFile(vClients, clientFileName); // this take O(n)
	addDataLineToFile(clientFileName, clientRecordToLine(newClient, delimiter));

	cout << "\n   adding client successfuly done !\n";
	system("pause");

}

//---------------------------------- delete client fucntion

void markDeleteFlagClient(vector<sClient>& vClients, string accountNumber)
{
	for (sClient& c : vClients)
	{
		if (c.accountNumber == accountNumber)
		{
			c.deleteFlag = true;
		}
	}
}

void deleteClient(vector<sClient>& vClients)
{

	string accountNumber;
	sClient findedClient;
	char answer = 'n';

	resetScreen();
	cout << "\n           D E L E T E    C L I E N T \n\n";
	accountNumber = mystd::readString("enter account number : ");

	if (searchClientByAccountNumber(vClients, accountNumber, findedClient))
	{
		printClientInfo(findedClient);

		cout << "\n\n are u sure to delete this client [y-YES | n-NO] : ";
		cin >> answer;
		cin.ignore(100, '\n');

		if (answer == 'y' || answer == 'Y')
		{
			markDeleteFlagClient(vClients, accountNumber);
			updateFile(vClients, clientFileName);
			vClients = loadClientsFromFile(clientFileName);

			cout << "\n   deleting client successfuly done !\n";
		}

	}
	else
	{
		cout << "account number [" << accountNumber << "] is not found.\n";
	}

	system("pause");

}

//------------------------------ update client function

sClient readNewClient()
{
	sClient newClient;

	cout << "enter Account number : ";
	getline(cin >> ws, newClient.accountNumber);

	cout << "enter PinCode : ";
	getline(cin, newClient.pinCode);

	cout << "enter name : ";
	getline(cin, newClient.name);

	cout << "enter phone : ";
	getline(cin, newClient.phone);

	cout << "enter account balance : ";
	cin >> newClient.balance;

	return newClient;
}

sClient readNewClientInfo(string accountNumber)
{
	sClient client;

	client.accountNumber = accountNumber;

	cout << "enter PinCode : ";
	getline(cin >> ws, client.pinCode);

	cout << "enter name : ";
	getline(cin, client.name);

	cout << "enter phone : ";
	getline(cin, client.phone);

	cout << "enter account balance : ";
	cin >> client.balance;

	return client;
}

void updateClientInfo(vector<sClient>& vClients)
{
	string accountNumber;
	sClient findedClient;
	char answer = 'n';

	resetScreen();
	cout << "\n           U P D A T E    C L I E N T \n\n";
	accountNumber = mystd::readString("enter account number : ");

	if (searchClientByAccountNumber(vClients, accountNumber, findedClient))
	{
		printClientInfo(findedClient);

		cout << "\n\n are u sure to update info this client [y-YES | n-NO] : ";
		cin >> answer;
		cin.ignore(100, '\n');

		if (answer == 'y' || answer == 'Y')
		{

			for (sClient& c : vClients) // by ref, vClients is changed
			{
				if (c.accountNumber == accountNumber)
				{
					c = readNewClientInfo(accountNumber);
				}
			}

			updateFile(vClients, clientFileName);

			cout << "\n   updating client successfuly done !\n";
		}
	}
	else
	{
		cout << "account number [" << accountNumber << "] is not found.\n";
	}

	system("pause");

}

//--------------------------------------- find client fucntion

void findClient(vector<sClient>& vClients)
{
	string accountNumber;
	sClient findedClient;

	resetScreen();
	cout << "\n           F I N D    C L I E N T \n\n";
	accountNumber = mystd::readString("enter account number : ");

	if (searchClientByAccountNumber(vClients, accountNumber, findedClient))
	{
		printClientInfo(findedClient);

	}
	else
	{
		cout << "account number [" << accountNumber << "] is not found.";
	}

	cout << "\n\n";
	system("pause");

}

int main() {

	eMode mode = eMode::Show;
	vector<sClient> vClients = loadClientsFromFile(clientFileName);

	while (mode != eMode::Exit)
	{
		resetScreen();
		printMainMenu();

		mode = readMode();
		switch (mode)
		{
		case eMode::Show:
			showClientList(vClients);
			break;

		case eMode::Add:
			addNewClient(vClients);
			break;

		case eMode::Delete:
			deleteClient(vClients);
			break;

		case eMode::update:
			updateClientInfo(vClients);
			break;

		case eMode::Find:
			findClient(vClients);
			break;

		case eMode::Exit:
			break;
		}



	}

	resetScreen();
	cout << "\t\tthis is the end of this program :)\n"
		<< "\t\t    thanks for your time" << endl;
	system("pause>0");

	return 0;
}