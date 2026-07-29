
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#define nl endl
using namespace std;

const string ClientsFile = "MyClients.txt";
const string Delimeter = "#//#";

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};
enum enMenu
{
    ShowClientsList = 1,
    AddClient,
    DeleteClient,
    UpdateClient,
    FindClient,
    Exit
};


vector<string> SplitString(string s, string delimeter) {
    vector<string> words;
    string new_word;
    int pos = 0;
    while ((pos = s.find(delimeter)) != s.npos) {
        new_word = s.substr(0, pos);

        if (new_word != "") {
            words.push_back(new_word);
        }
        s.erase(0, pos + delimeter.length());
    }
    if (s != "") words.push_back(s);

    return words;
}
stClient ConvertLineToRecord(string& line, string delimeter = Delimeter) {
    vector<string> data = SplitString(line, delimeter);
    stClient client;

    client.AccountNumber = data[0];
    client.PinCode = data[1];
    client.Name = data[2];
    client.Phone = data[3];
    client.AccountBalance = stod(data[4]);

    return client;
}
string ConvertRecordToLine(stClient client, string delimeter = Delimeter) {
    string s;

    s += client.AccountNumber + delimeter;
    s += client.PinCode + delimeter;
    s += client.Name + delimeter;
    s += client.Phone + delimeter;
    s += to_string(client.AccountBalance);

    return s;
}
vector<stClient> ConvertAllLinesToRecords(vector<string>& lines, string delimeter = Delimeter) {
    vector<stClient> AllClients;
    for (string& s : lines) {
        AllClients.push_back(ConvertLineToRecord(s));
    }
    return AllClients;
}
vector<string> ConvertAllRecordsToLines(vector<stClient> &AllClients, string delimeter = Delimeter) {
    vector<string> Lines;
    for (stClient& i : AllClients) {
        Lines.push_back(ConvertRecordToLine(i));
    }
    return Lines;
}

vector<string> LoadLinesFromFileToVector(string FileName) {
    vector<string> lines;
    fstream MyFile;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {
        string line;

        while (getline(MyFile, line)) {
            lines.push_back(line);
        }

        MyFile.close();
    }
    return lines;

}
void SaveVectorToFile(string FileName, vector<string>lines) {
    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open()) {

        for (string& line : lines) {
            MyFile << line << nl;
        }

        MyFile.close();
    }
}

int IsClientExist(string AccountNumber, vector<stClient> &AllClients) {
    for (int i = 0; i < AllClients.size(); i++) {
        if (AllClients[i].AccountNumber == AccountNumber) {
            return i;
        }
    }
    return -1;
}

int ReadNumInRange(string message, int from, int to) {
    int num;
    do
    {
        cout << message;
        cin >> num;

        // fial عشان لو دخل حاجة غير رقم
        // peek عشان لو دخل رقم عشري ميقبلش بردو
        // peek بتجيب الباقي في البفر بعد الادخال 
        // فلو كان الباقي سطر كامل او مسافة فاضية يبقى تمام والا يبقى غلط بردو
        if (cin.fail() || (cin.peek() != '\n' && cin.peek() != ' ')) {
            cin.clear();
            cin.ignore(10000, '\n');
            num = to + 1;
        }


    } while (num < from || num > to);
    return num;
}
string ReadString(string message) {
    string s;
    cout << message;
    getline(cin>>ws, s);
    return s;
}
enMenu ReadChoice(string message, int from, int to) {
    int choice = ReadNumInRange(message, from, to);
    return (enMenu)choice;
}
stClient ReadClientData(vector<stClient> &AllClients) {
    stClient client;
 
    while (true) {
        cout << "Enter Account Number: ";
        // ws to ignore all white spaces
        getline(cin >> ws, client.AccountNumber);
        if (IsClientExist(client.AccountNumber, AllClients) == -1) break;
        cout << "\nClient with [ " << client.AccountNumber << " ] already exist, ";
    }

    cout << "Enter Pin Code: ";
    getline(cin, client.PinCode);

    cout << "Enter Name: ";
    getline(cin, client.Name);

    cout << "Enter Phone: ";
    getline(cin, client.Phone);

    cout << "Enter Acount Balance: ";
    cin >> client.AccountBalance;

    return client;
}
stClient UpdateClientData(stClient& client) {
    cout << "\nEnter Pin Code: ";
    getline(cin >> ws, client.PinCode);

    cout << "Enter Name: ";
    getline(cin, client.Name);

    cout << "Enter Phone: ";
    getline(cin, client.Phone);

    cout << "Enter Acount Balance: ";
    cin >> client.AccountBalance;

    return client;
}


void PrintClientData(stClient client) {
    cout << "Account Number  : " << client.AccountNumber << nl;
    cout << "Pin Code        : " << client.PinCode << nl;
    cout << "Name            : " << client.Name << nl;
    cout << "Phone           : " << client.Phone << nl;
    cout << "Account Balance : " << client.AccountBalance << nl;
}
void PrintHeader(short ClientsNumber) {
    cout << "\t\t\t\t\tClient List(" << ClientsNumber << ") Clients.";
    cout << "\n----------------------------------------------------------------------------------------------------\n";
    cout << left << setw(20) << "| Account Number ";
    cout << left << setw(10) << "| Pin Code ";
    cout << left << setw(30) << "| Client Name ";
    cout << left << setw(20) << "| Phone ";
    cout << left << setw(15) << "| Account Balance |";
    cout << "\n----------------------------------------------------------------------------------------------------\n";
}
void PrintFooter() {
    cout << "\n----------------------------------------------------------------------------------------------------\n";
}
void PrintClientRecord(stClient& client) {
    cout << "| " << left << setw(17) << client.AccountNumber;
    cout << " | " << left << setw(8) << client.PinCode;
    cout << " | " << left << setw(27) << client.Name;
    cout << " | " << left << setw(17) << client.Phone;
    cout << " | " << left << setw(15) << client.AccountBalance << " |";
}

void AddClients(vector<stClient> &AllClients) {
    char AddMoreClients = 'y';
    do
    {
        //system("cls");
        cout << "\nAdding new client: \n" << nl;

        stClient client = ReadClientData(AllClients);
        AllClients.push_back(client);

        cout << "\nClient added successfully, do you want to add more clients? (y/n): ";
        cin >> AddMoreClients;

    } while (tolower(AddMoreClients) == 'y');
    SaveVectorToFile(ClientsFile, ConvertAllRecordsToLines(AllClients));
}
void DeleteClientByAccountNumber(string AccountNumber, vector<stClient> &AllClients) {
    int index;
    if ((index = IsClientExist(AccountNumber, AllClients)) != -1) {
        cout << "\nThe following are the client data:\n\n";
        PrintClientData(AllClients[index]);

        char Ok;
        cout << "\nAre you sure you want to delete this client (y/n): ";
        cin >> Ok;
        if (tolower(Ok) == 'y') {
            AllClients.erase(AllClients.begin() + index);
            SaveVectorToFile(ClientsFile, ConvertAllRecordsToLines(AllClients));
            cout << "\nClient deleted successfully.\n";
        }
    }
    else {
        cout << "Client with account number [ " << AccountNumber << " ] not exist!" << nl;
    }
}
void UpdateClientByAccountNumber(string AccountNumber, vector<stClient> &AllClients) {
    int index;
    if ((index = IsClientExist(AccountNumber, AllClients)) != -1) {
        cout << "\nThe following are the client data:\n\n";
        PrintClientData(AllClients[index]);

        char Ok;
        cout << "\nAre you sure you want to update this client (y/n): ";
        cin >> Ok;
        if (tolower(Ok) == 'y') {
            UpdateClientData(AllClients[index]);
            SaveVectorToFile(ClientsFile, ConvertAllRecordsToLines(AllClients));
            cout << "\nClient updated successfully.\n";
        }
    }
    else {
        cout << "Client with account number [ " << AccountNumber << " ] not exist!" << nl;
    }
}
void FindClientByAccountNumber(string AccountNumber, vector<stClient> &AllClients) {
    int index;
    if ((index = IsClientExist(AccountNumber, AllClients)) != -1) {
        PrintClientData(AllClients[index]);
    }
    else {
        cout << "Client with account number [ " << AccountNumber << " ] not exist!" << nl;
    }
}

void ShowAllClients(vector<stClient>& AllClients) {
    PrintHeader(AllClients.size());

    for (int i = 0; i < AllClients.size(); i++) {
        PrintClientRecord(AllClients[i]);
        if (i < AllClients.size() - 1) cout << nl;
    }

    PrintFooter();
}
void ShowAddNewClientsScreen(vector<stClient>& AllClients) {
    cout << "======================================\n";
    cout << "\t\tAdd Clients:\n";
    cout << "======================================\n";
    AddClients(AllClients);
}
void ShowDeleteClientScreen(vector<stClient>& AllClients) {
    cout << "======================================\n";
    cout << "\t\tDelete Client:\n";
    cout << "======================================\n";
    DeleteClientByAccountNumber(ReadString("Enter Account Number: "), AllClients);
}
void ShowUpdateClientScreen(vector<stClient>& AllClients) {
    cout << "======================================\n";
    cout << "\t\tUpdate Client:\n";
    cout << "======================================\n";
    UpdateClientByAccountNumber(ReadString("Enter Account Number: "), AllClients);
}
void ShowFindClientScreen(vector<stClient>& AllClients) {
    cout << "======================================\n";
    cout << "\t\tFind Client:\n";
    cout << "======================================\n";
    FindClientByAccountNumber(ReadString("Enter Account Number: "), AllClients);
}
void ShowEndScreen() {
    cout << "======================================\n";
    cout << "\t\tProgram ends :-)\n";
    cout << "======================================\n";
}
void ShowMainMenu() {
    cout << "======================================\n";
    cout << "\t\tMain Menu\n";
    cout << "======================================\n";
    cout << "\t[1] Show clients list.\n";
    cout << "\t[2] Add new client.\n";
    cout << "\t[3] Delete client.\n";
    cout << "\t[4] Update client info.\n";
    cout << "\t[5] Find client.\n";
    cout << "\t[6] Exit.\n";
    cout << "======================================\n";
}

void GoBackToMainMenu() {
    cout << "\nPress any key to go back to main menu...";
    system("pause>nul");
    system("cls");
}



int main()
{
    vector<string> AllLines = LoadLinesFromFileToVector(ClientsFile);
    vector<stClient> AllClients = ConvertAllLinesToRecords(AllLines);
    enMenu choice;
    do
    {
        ShowMainMenu();
        choice = ReadChoice("What is your choice from 1 to 6: ", 1, 6);
        system("cls");

        switch (choice) {
        case enMenu::ShowClientsList:
            ShowAllClients(AllClients);
            GoBackToMainMenu();
            break;
        case enMenu::AddClient:
            ShowAddNewClientsScreen(AllClients);
            GoBackToMainMenu();
            break;
        case enMenu::DeleteClient:
            ShowDeleteClientScreen(AllClients);
            GoBackToMainMenu();
            break;
        case enMenu::UpdateClient:
            ShowUpdateClientScreen(AllClients);
            GoBackToMainMenu();
            break;
        case enMenu::FindClient:
            ShowFindClientScreen(AllClients);
            GoBackToMainMenu();
            break;
        case enMenu::Exit:
            ShowEndScreen();
            break;
        }
    } while (choice != enMenu::Exit);

    return 0;
}




