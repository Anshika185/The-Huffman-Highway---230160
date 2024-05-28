#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

class Transaction {
public:
    string date;
    double amount;
    string type; // "deposit" or "withdrawal"

    Transaction(double amt, const string& t) : amount(amt), type(t) {
        // Get current date/time
        time_t now = time(0);
        tm* ltm = localtime(&now);
        ostringstream oss;
        oss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
        date = oss.str();
    }

    void display() const {
        cout << date << " - " << type << ": $" << amount << endl;
    }
};

class Loan {
public:
    double amount;
    double interest_rate;
    int term_years;
    string start_date;

    Loan(double amt, double rate, int term) : amount(amt), interest_rate(rate), term_years(term) {
        // Get current date/time
        time_t now = time(0);
        tm* ltm = localtime(&now);
        ostringstream oss;
        oss << put_time(ltm, "%Y-%m-%d");
        start_date = oss.str();
    }

    void display() const {
        cout << "Loan of $" << amount << " at " << interest_rate << "% for " << term_years << " years starting on " << start_date << endl;
    }
};

class Account {
protected:
    string account_number;
    string holder_name;
    string address;
    string account_type;
    double funds;
    vector<Transaction> transaction_history;
    vector<Loan> loan_history;

public:
    Account(const string& acc_num, const string& holder, const string& addr, const string& acc_type) 
        : account_number(acc_num), holder_name(holder), address(addr), account_type(acc_type), funds(0.0) {}

    virtual ~Account() {}

    void deposit(double amount) {
        funds += amount;
        transaction_history.emplace_back(amount, "deposit");
        cout << "$" << amount << " deposited successfully." << endl;
    }

    void withdraw(double amount) {
        if (funds >= amount) {
            funds -= amount;
            transaction_history.emplace_back(amount, "withdrawal");
            cout << "$" << amount << " withdrawn successfully." << endl;
        } else {
            cout << "Insufficient funds for withdrawal." << endl;
        }
    }

    void update_info(const string& new_name = "", const string& new_address = "") {
        if (!new_name.empty()) {
            holder_name = new_name;
        }
        if (!new_address.empty()) {
            address = new_address;
        }
        cout << "Account information updated successfully." << endl;
    }

    void view_passbook() const {
        for (const auto& transaction : transaction_history) {
            transaction.display();
        }
    }

    void search_transaction_history(const string& date = "", double amount = 0.0) const {
        for (const auto& transaction : transaction_history) {
            if ((!date.empty() && transaction.date.find(date) != string::npos) || 
                (amount > 0.0 && transaction.amount == amount)) {
                transaction.display();
            }
        }
    }

    void take_loan(double amount, double interest_rate, int term_years) {
        loan_history.emplace_back(amount, interest_rate, term_years);
        funds += amount;
        cout << "Loan approved for $" << amount << ". Funds added to account." << endl;
    }

    string get_account_number() const {
        return account_number;
    }

    double get_funds() const {
        return funds;
    }
};

class SavingsAccount : public Account {
public:
    SavingsAccount(const string& acc_num, const string& holder, const string& addr) 
        : Account(acc_num, holder, addr, "Savings") {}
};

class CurrentAccount : public Account {
public:
    CurrentAccount(const string& acc_num, const string& holder, const string& addr) 
        : Account(acc_num, holder, addr, "Current") {}
};

class JointAccount : public Account {
public:
    JointAccount(const string& acc_num, const string& holders, const string& addr) 
        : Account(acc_num, holders, addr, "Joint") {}
};

class Bank {
private:
    vector<Account*> accounts;

public:
    ~Bank() {
        for (auto account : accounts) {
            delete account;
        }
    }

    void create_account(const string& account_type, const string& account_number, const string& holder_name, const string& address) {
        if (account_type == "Savings") {
            accounts.push_back(new SavingsAccount(account_number, holder_name, address));
        } else if (account_type == "Current") {
            accounts.push_back(new CurrentAccount(account_number, holder_name, address));
        } else {
            cout << "Unsupported account type." << endl;
            return;
        }
        cout << account_type << " account created successfully for " << holder_name << "." << endl;
    }

    void create_joint_account(const string& account_number, const string& holders_names, const string& address) {
        accounts.push_back(new JointAccount(account_number, holders_names, address));
        cout << "Joint account created successfully for " << holders_names << "." << endl;
    }

    Account* get_account(const string& account_number) {
        for (auto account : accounts) {
            if (account->get_account_number() == account_number) {
                return account;
            }
        }
        cout << "Account not found." << endl;
        return nullptr;
    }

    void transfer_funds(const string& from_account_number, const string& to_account_number, double amount) {
        Account* from_account = get_account(from_account_number);
        Account* to_account = get_account(to_account_number);
        if (from_account && to_account) {
            if (from_account->get_funds() >= amount) {
                from_account->withdraw(amount);
                to_account->deposit(amount);
                cout << "Transferred $" << amount << " from account " << from_account_number << " to account " << to_account_number << "." << endl;
            } else {
                cout << "Insufficient funds in the source account." << endl;
            }
        } else {
            cout << "One or both account numbers are invalid." << endl;
        }
    }
};

int main() {
    Bank bank;
    bank.create_account("Savings", "001", "Rahul Agrawal", "Krishna Nagar");
    bank.create_account("Current", "002", "Mahima Singh", "Sonkh Road");
    bank.create_joint_account("003", "Rahul Agrawal,Mahima Singh", "Ashoka Heights");

    Account* account1 = bank.get_account("001");
    Account* account2 = bank.get_account("002");
    Account* joint_account = bank.get_account("003");

    if (account1) {
        account1->deposit(1000);
        account1->withdraw(500);
        account1->view_passbook();

        account1->take_loan(5000, 5.0, 10);
        account1->view_passbook();
    }

    if (account2) {
        account2->deposit(2000);
        bank.transfer_funds("002", "001", 1000);
    }

    if (joint_account) {
        joint_account->deposit(3000);
        joint_account->view_passbook();
    }
    return 0;
}