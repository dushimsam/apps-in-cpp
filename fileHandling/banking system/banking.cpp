#include <bits/stdc++.h>
using namespace std;

const vector<string> transaction_types = {"DEPOSIT", "WITHDRAW"};
const string accounts_file_name = "accounts.txt";
const string transaction_file_name = "transactiob.txt";

fstream AccountFile;
fstream TransactionFile;

/***
 * ERror:
 * 1. Segmentation fault : out of bounds in array.
 * 2. Prefer using this->varName on the constructors.
***/
class Account
{

public:
    int account_number;
    string names;
    double balance;

    Account() {}
    Account(int account_number, string names, double balance)
    {
        this->account_number = account_number;
        this->names = names;
        this->balance = balance;
    }

    void printAccount()
    {
        cout << "Account number: " << account_number << endl;
        cout << "Names: " << names << endl;
        cout << "Balance: " << balance << endl;
    }

    void getAccount()
    {
        cout << "Enter the account_number's ID:";
        cin >> account_number;
        cout << "\nEnter the account names: ";
        cin >> names;
        cout << "\nEnter the balance : ";
        cin >> balance;
        cout << "\n\n";
    }

    string printOnLn()
    {
        return to_string(account_number) + " " + names + " " + to_string(balance);
    }
};

class Transaction
{
public:
    int account_number;
    string transaction_type;
    float amount;

    Transaction() {}
    Transaction(int account_number, string transaction_type, float amount)
    {
        account_number = account_number;
        transaction_type = transaction_type;
        amount = amount;
    }

    void getDetails()
    {
        cout << "Enter the account number: ";
        cin >> account_number;
        cout << "\nEnter the transaction type: ";
        cin >> transaction_type;
        cout << "\nEnter the amount: ";
        cin >> amount;
    }

    void printDetails()
    {
        cout << "Account Number: " << account_number;
        cout << "\nTransaction type: " << transaction_type;
        cout << "\nAmount: " << amount;
    }

    void printOnLn()
    {
        cout << account_number << " " << transaction_type << " " << amount;
    }
};

/**** FUNCTION TO HANDLE FILES ***/

bool openAccountFile(string mode)
{
    if (mode == "a")
    {
        AccountFile.open(accounts_file_name, ios::app);
    }
    else if (mode == "r")
    {
        AccountFile.open(accounts_file_name, ios::in);
    }

    return AccountFile.is_open();
}

bool openTransactionFile(string mode)
{

    if (mode == "a")
    {
        TransactionFile.open(transaction_file_name, ios::app);
    }
    else if (mode == "r")
    {
        TransactionFile.open(transaction_file_name, ios::in);
    }
    return TransactionFile.is_open();
}


/***
ACCOUNT MANAGEMENT
***/

/*** Creation of the account ***/

bool insertion(Account account)
{
    
    if (openAccountFile("a"))
    {
        AccountFile << account.printOnLn() << "\n";
        AccountFile.close();
        return true;
    }

    return false;
}

/**  READDING OF ACCOUNTS ***/

/** READ ALL **/

vector<string> extractWordsOnArra(string ln)
{
    istringstream ss(ln);
    vector<string> words;

    string curr_word;
    while (ss >> curr_word)
        words.push_back(curr_word);

    return words;
}

void readAllAccounts()
{
    if (openAccountFile("r"))
    {
        string ln;
        while (getline(AccountFile, ln))
        {
            if (ln != "")
            {
                vector<string> words = extractWordsOnArra(ln);
                Account account(stoi(words[0]), words[1], stod(words[2]));
                account.printAccount();
                cout << "\n\n";
            }
        }

        AccountFile.close();
    }
}

bool readSingle(int account_number)
{
    if (openAccountFile("r"))
    {
        string ln;
        while (getline(AccountFile, ln))
        {
            if (ln != "")
            {
                vector<string> words = extractWordsOnArra(ln);
                if (words[0] == to_string(account_number))
                {
                    Account account(stoi(words[0]), words[1], stod(words[2]));
                    account.printAccount();
                    AccountFile.close();
                    return true;
                }
            }
        }
        AccountFile.close();
    }
    return false;
}

/*** UPDATE ***/

bool update(Account account, int account_number)
{
    fstream TempFile;
    TempFile.open("temp.txt", ios::app);
    if (TempFile.is_open() && openAccountFile("r"))
    {
        string ln;
        while (getline(AccountFile, ln))
        {

            if (ln != "")
            {
                vector<string> words = extractWordsOnArra(ln);

                if (words[0] == to_string(account_number))
                {
                    TempFile << account.printOnLn() << "\n";
                }
                else
                {
                    TempFile << ln << "\n";
                }
            }
        }

        TempFile.close();
        AccountFile.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }

    return true;
}

/*** DELETE ***/

bool deleteData(int account_number)
{
    fstream TempFile;
    TempFile.open("temp.txt", ios::app);
    if (TempFile.is_open() && openAccountFile("r"))
    {
        string ln;
        while (getline(AccountFile, ln))
        {
            if (ln != "")
            {
                vector<string> words = extractWordsOnArra(ln);
                if (words[0] != to_string(account_number))
                {
                    TempFile << ln << "\n";
                }
            }
        }

        TempFile.close();
        AccountFile.close();

        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
    }

    return true;
}

/*** HANDLING OPTIONS ***/

bool addAccount()
{
    Account account;
    account.getAccount();
    return insertion(account);
}

bool updateAcccount()
{
    Account account;
    account.getAccount();
    return update(account, account.account_number);
}

bool deleteAccount()
{
    int account_number;
    cout << " Enter the account number ";
    cin >> account_number;
    return deleteData(account_number);
}

bool searchAccount()
{
    int account_number;
    cout << " Enter the account number ";
    cin >> account_number;

    return readSingle(account_number);
}
void getOPtions()
{
    cout << " \t\t\t\t BANKING SYSTEM \t\t\t\t\n\n\n";
    cout << " 1. CREATE ACCOUNT \n";
    cout << " 2. FIND ACCOUNT \n";
    cout << " 3. READ ALL ACCOUNTS \n";
    cout << " 4. UPDATE ACCOUNTS \n";
    cout << " 5. DELETE ACCOUNT \n";

    int option;
    cin >> option;

    switch (option)
    {
    case 1:
        if (addAccount())
        {
            cout << "Successfully added account.\n";
        }
        else
        {
            cout << "Account addition failed\n";
        }
        break;
    case 2:
        searchAccount();
        break;
    case 3:
        readAllAccounts();
        break;
    case 4:
        if (updateAcccount())
        {
            cout << "Successfully updated account.\n";
        }
        else
        {
            cout << "Account updation failed\n";
        }
        break;
    case 5:
        if (deleteAccount())
        {
            cout << "Successfully deleted account.\n";
        }
        else
        {
            cout << "Account deletion failed\n";
        }
        break;
    default:
        cout << "INVALID CHOICE" << endl;
    }
}
int main()
{

    while (1)
    {
        getOPtions();
    }
    return 0;
}