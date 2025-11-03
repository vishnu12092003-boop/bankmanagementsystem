#include<iostream>
#include<vector>
#include<string>
#include<iomanip>
#include<limits> // To set Limits

using namespace std;

class Bank {
    private:
    long long account_number;
    string customer_name;
    double balance;

    public:
    //Constructor to initialize account
    Bank(long long acc_num , string name , double initial_balance) 
     : account_number(acc_num) , customer_name(name) , balance(initial_balance) {}

    //getter methods
    long long get_account_number() const {
        return account_number;
    }

    string get_customer_name() const {
        return customer_name;
    }

    double get_balance() const {
        return balance;
    }

    // Deposit Method
    void deposit(double amount){
        if(amount > 0){
            balance += amount;
            cout<<endl<<"Deposit successful.New Balance: "<<fixed<<setprecision(2) << balance << endl;
        }
        else {
            cout<<endl<<"Error:Deposit amount must be positive."<<endl;
        }
    }

    //Withdraw Method
    bool withdraw(double amount){
        if (amount <= 0){
            cout<<endl<<"Error:Withdrawl amount must be positive."<<endl;
            return false;
        }
        if (balance >= amount){
            balance -= amount;
            cout<<endl<<"Withdraw Successful.Remaining Balance: "<<fixed<<setprecision(2)<< balance << endl;
            return true;
        }
        else {
            cout<<endl<<"Insufficient Balance.Available: "<<fixed<<setprecision(2) <<balance<<'\n';
            return false;
        }
    }

    void display_account() const {
        cout<<endl<<"====================================="<<endl;
        cout<<endl<<"Account Holder: "<< customer_name <<endl;
        cout<<endl<<"Account Number: "<<account_number <<endl;
        cout<<endl<<"Current Balance: "<<fixed<<setprecision(2)<< balance <<endl;
        cout<<endl<<"===================================="<<endl;
    }
};

//Global vector to store all data
vector<Bank> accounts;

//Function to find an account by number
//Returns a pointer to the account or nullptr if not found
Bank* find_account(long long acc_num) {
    for(size_t i = 0 ; i < accounts.size(); ++i ){
        if (accounts[i].get_account_number() == acc_num){
            return &accounts[i];
        }
    }
    return nullptr;
}

//Function to generate a simple, unique account number
long long generate_account_number() {
    static long long next_account_number = 100000;
    return next_account_number++;
}

//Function to handle the "Open Account" operation
void open_account() {
    string name;
    double initial_deposit;

    cout<<endl<<"Open New Account: "<<endl;
    cout<<"Enter customer name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // To clear buffer before getline
    getline(cin, name);

    cout<<"Enter initial deposit amount (minimum 100): ";
    while (!(cin >> initial_deposit) || initial_deposit < 100) {
        cout<<"Invalid amount. Minimum deposit is 100.Enter again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max());
    }

    long long acc_num = generate_account_number();
    accounts.emplace_back(acc_num , name , initial_deposit); //create and add new account

    cout<<endl<<"****    Account successfully opened!  ****"<<endl;
    cout<<"Your Account Number is: "<<acc_num<<endl;
}

//Function to handle the "Deposit" operation
void deposit_funds() {
    long long acc_num;
    double amount;

    cout<<endl<<"----- Deposit Funds ------"<<endl;
    cout<<"Enter Account Number: ";
    if(!(cin >> acc_num)) {
        cout<<"Invalid Input for Account Number."<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max());
        return;
    }

    Bank* account = find_account(acc_num);

    if(account) {
        cout <<"Enter deposit amount: ";
        while(!(cin >> amount) || amount <= 0) {
            cout<<"Invalid amount.Must be positive.Enter again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max());
        }
        account->deposit(amount);
    } else{
        cout<<endl<<"Error: Account not found."<<endl;
    }
}

//Function to handle "Withdraw" operation
void withdraw_funds() {
    long long acc_num;
    double amount;

    cout<<endl<<"----- Withdraw Funds -------"<<endl;
    cout<<"Enter Account Number:  ";
    if(!(cin >> acc_num)) {
        cout<<"Invalid input for account number"<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max());
        return;
    }

    Bank* account = find_account(acc_num);

    if(account) {
        cout<<"Enter Withdrawl amount:  ";
        while (!(cin >> amount) || amount <= 0) {
            cout<<"Invalid amount.Must be positive.Enter again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max());
        }
        account->withdraw(amount);
    } else {
        cout<<"Error:Account not found."<<endl;
    }
}

//Function to handle the "Check Balance" operation
void check_balance() {
    long long acc_num;

    cout<<endl<<"------- Check Account Balance -------"<<endl;
    cout<<"Enter Account Number: ";
    if(!(cin >> acc_num)) {
        cout << "Invalid input for account number."<<endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max());
        return;
    }

    Bank* account = find_account(acc_num);

    if (account) {
        cout<<endl<<"Account Balance for "<<account->get_customer_name() <<": "
            <<fixed<<setprecision(2)<<account->get_balance() <<endl;
    } else {
        cout << "Error: Account not found."<<endl;
    }
}

//Function to display the main menu
void display_menu() {
    cout<<endl<<endl<<"*************************************************"<<endl;
    cout<<"               Bank Management System              "<<endl;
    cout<<"*************************************************"<<endl;
    cout<<"1.Open New Account"<<endl;
    cout<<"2.Deposit Funds"<<endl;
    cout<<"3.Withdraw Funds"<<endl;
    cout<<"4.Chech Balance"<<endl;
    cout<<"5.Exit"<<endl;
    cout<<"-------------------------------------------------------"<<endl;
    cout<<"Enter your choice (1-5): ";
}

int main() {
    int choice;

    //set output stream for two decimal places (currency format)
    cout << fixed << setprecision(2);

    do {
        display_menu();

        //Input validation for the menu choice
        if (!(cin >> choice)) {
            cout<<endl<<"Invalid input. Please enter a number between 1 and 5 "<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max());
            continue; //skip the rest of loop and show menu again
        }

        switch(choice) {
            case 1:
            open_account();
            break;
            case 2:
            deposit_funds();
            break;
            case 3:
            withdraw_funds();
            break;
            case 4:
            check_balance();
            break;
            case 5:
            cout<<endl<<"Thank you for using the Bank Management System."<<endl;
            break;
            default:
            cout<<endl<<"Invalid choice. Please enter number between 1 and 5"<<endl;
            break;
        }
    } while (choice != 5);

    return 0;
}
