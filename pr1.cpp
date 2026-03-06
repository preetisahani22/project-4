#include <iostream>

using namespace std;

class BankAccount
{
private:
    double balance;

protected:
    string accountNumber, accountHoldername;

public:
    BankAccount(string acc, string name, double bal)
    {
        accountNumber = acc;
        accountHoldername = name;
        balance = bal;
    }
    void deposit(double amount)
    {
        balance += amount;
        cout << "Money Deposited Successfully" << endl;
        cout << "Current Balance is: " << balance << endl;
    }
    virtual void withdraw(double amount)
    {
        if (amount <= balance)
        {
            balance -= amount;
            cout << "Money Withdrawed Successfully" << endl;
            cout << "Current Balance is: " << balance << endl;
        }
        else
        {
            cout << "Not enough balance." << endl;
        }
    }
    virtual void display()
    {
        cout << endl
             << "Account Number: " << accountNumber << endl;
        cout << endl
             << "Account Holder Name: " << accountHoldername << endl;
        cout << endl
             << "Account's Balance: " << balance << endl;
    }
    virtual double calculateinterest()
    {
        return 0;
    }
    double getbalance()
    {
        return balance;
    }
};
class SavingsAccount : public BankAccount
{
private:
    double interestRate;

public:
    SavingsAccount(string acc, string name, double bal, double intrate) : BankAccount(acc, name, bal)
    {
        interestRate = intrate;
    }
    double calculateinterest() override
    {
        return getbalance() * (interestRate / 100);
    }
    void display() override
    {
        BankAccount::display();
        cout << "Account Type: Savings Account" << endl;
        cout << "Interest Rate Is: " << interestRate << "%" << endl;
    }
};
class CheckingAccount : public BankAccount
{

private:
    double OverdraftLimit;

public:
    CheckingAccount(string acc, string name, double bal, double limit) : BankAccount(acc, name, bal)
    {
        OverdraftLimit = limit;
    }
    void withdraw(double amount) override
    {
        double current = getbalance();

        if (amount <= current + OverdraftLimit)
        {
            if (amount <= current)
            {
                cout << "Money Withdrawn Successfully." << endl;
                cout << "Amount withdrawn: " << amount << endl;
                double newBal = current - amount;

                cout << "Updated Balance: " << newBal << endl;
            }
            else
            {
                cout << "Money Withdrawn Successfully (Overdraft Used)." << endl;
                cout << "Overdraft Amount Used: " << amount - current << endl;
                cout << "Updated Balance: 0 (Overdraft covers the rest)" << endl;
            }
        }
        else
        {
            cout << "Overdraft Limit Exceeded!" << endl;
        }
    }

    void display() override
    {
        BankAccount::display();
        cout << endl
             << "Account Type: Checking Account" << endl;
        cout << endl
             << "OverDraft Limit: " << OverdraftLimit << endl;
    }
};

class FixedDepositAccount : public BankAccount
{
private:
    int term;

public:
    FixedDepositAccount(string acc, string name, double bal, int t) : BankAccount(acc, name, bal)
    {
        term = t;
    }
    double calculateinterest() override

    {
        return getbalance() * 0.07 * (term / 12.0);
    }
    void display() override
    {
        BankAccount::display();
        cout << endl
             << "Account's Type: Fixed Deposit Account" << endl;
        cout << endl
             << "Term: " << term << "months" << endl;
    }
};
int main()
{
    BankAccount *acc = 0;
    int choice;
    do
    {
        cout << endl
             << "1.Create Savings Account:" << endl;
        cout << "2.Create Checking Account:" << endl;
        cout << "3.Create Fixed Deposit Account:" << endl;
        cout << "4.Deposit Money" << endl;
        cout << "5.Withdraw Money" << endl;
        cout << "6.Display All Accounts" << endl;
        cout << "7.Show Interest" << endl;
        cout << "8.Exit!" << endl;
        cout << "Enter Choice:";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string accNum, name;
            double bal, rate;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Holder Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> bal;
            cout << "Enter Interest Rate (%): ";
            cin >> rate;
            acc = new SavingsAccount(accNum, name, bal, rate);
            cout << "Savings Account Created." << endl;
            break;
        }

        case 2:
        {
            string accNum, name;
            double bal, limit;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Holder Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> bal;
            cout << "Enter Overdraft Limit: ";
            cin >> limit;

            acc = new CheckingAccount(accNum, name, bal, limit);
            cout << "Checking Account Created." << endl;
            break;
        }
        case 3:
        {
            string accNum, name;
            double bal;
            int term;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter Holder Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> bal;
            cout << "Enter Term (Months): ";
            cin >> term;

            acc = new FixedDepositAccount(accNum, name, bal, term);
            cout << "Fixed Deposit Account Created." << endl;
            break;
        }
        case 4:
        {
            if (!acc)
            {
                cout << "Create an account first!" << endl;
                break;
            }
            double amt;
            cout << "Enter deposit amount: ";
            cin >> amt;
            acc->deposit(amt);
            break;
        }
        case 5:
        {
            if (!acc)
            {
                cout << "Create an account first!" << endl;
                break;
            }
            double amt;
            cout << "Enter withdrawal amount: ";
            cin >> amt;
            acc->withdraw(amt);
            break;
        }
        case 6:
            if (acc)
                acc->display();
            else
                cout << "Create an account first!" << endl;
            break;

        case 7:
            if (acc)
                cout << "Interest: " << acc->calculateinterest() << endl;
            else
                cout << "Create an account first!" << endl;
            break;

        case 8:
            cout << "Exited Succesfully" << endl;
            break;

        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 8);
}
