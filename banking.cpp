
 #include <fstream>
 #include<iomanip>
 #include<ctime>
#include<vector>
#include<string>
#include <iostream>
#include <sstream>
using namespace std;


struct Account{
	int accountNumber;
	string customerName;
	double balance;
	string accountType;
	string createdDate;
};
vector<Account> accounts;
int nextAccountNumber=10001;
void saveAccounts(){
ofstream file("accounts.dat");

if (!file){
	cout<<"Error Saving Accounts!"<<endl;
	return;
}
   file<<accounts.size()<<endl;
for (const auto& acc : accounts){
	file<<acc.accountNumber<<"|";
    file<<acc.customerName<<"|";
    file<<acc.balance<<"|";
    file<<acc.accountType<<endl;
}
file.close();
}
void loadAccounts(){
	ifstream file("accounts.dat");
	if(!file){
		return;
	}
	int maxAccountNumber = 10000;
	int count;
	file>>count;
	file.ignore(1000,'\n');
	for(int i=0;i<count;i++){
		Account acc;
		string value;
		string line;
        getline(file, line);
        stringstream ss(line);
        getline(ss, value, '|');
        acc.accountNumber = stoi(value);
        getline(ss, value, '|');
        acc.customerName = value;
        getline(ss, value, '|');
        acc.balance=stod(value);
        getline(ss, value, '|');
        acc.accountType=value;
        accounts.push_back(acc);
        if(acc.accountNumber > maxAccountNumber){
            maxAccountNumber = acc.accountNumber;
        }
	}
	nextAccountNumber =maxAccountNumber + 1;

}
void createAccount(){
	Account newAccount;
	newAccount.accountNumber=nextAccountNumber;
	cout<<"Account Number: "<<newAccount.accountNumber<<endl;
    nextAccountNumber++;
	cout<<"Customer Name: ";
	cin.ignore(1000, '\n');
	getline(cin,newAccount.customerName);
	cout<<"Account Type: ";
	getline(cin,newAccount.accountType);
	cout<<"Balance: ";
    cin>>newAccount.balance;
    if(newAccount.balance<0){
    	cout<<"Balance cannot be negative."<<endl;
    	return;
	}
    time_t now=time(0);
    tm* timeInfo=localtime(&now);
    newAccount.createdDate=asctime(timeInfo);
    cout<<"Date of Creation: "<<newAccount.createdDate;
    
    
	accounts.push_back(newAccount);
}
void deposit(){
	int accNum;
	cout<<"Account Number: ";
	cin>>accNum;
	Account* foundAccount=nullptr;
	for(int i=0;i<accounts.size();i++){
		if(accounts[i].accountNumber==accNum){
			foundAccount=&accounts[i];
		break;
		}
	}
	if(foundAccount==nullptr){
		cout<<"Account Not Found"<<endl;
		return;
	}
	double amount;
	cout<<"Amount to deposit: ";
	cin>>amount;
	if(amount<=0){
		cout<<"Amount must be positive.";
		return ;
	}
	foundAccount -> balance+=amount;
	cout<<"New BAlance: "<<foundAccount->balance<<endl;
}
void withdraw(){
	int accNum;
	cout<<"Account Number: ";
	cin>>accNum;
	Account* foundAccount=nullptr;
	for(int i=0;i<accounts.size();i++){
		if(accounts[i].accountNumber==accNum){
			foundAccount=&accounts[i];
			break;
		}
	}
	if(foundAccount==nullptr){
		cout<<"Account Not Found";
		return;
	}
	double amount;
	cout<<"Amount to Withdraw: ";
	cin>>amount;
	if(amount<=0){
		cout<<"Amount must be positive";
		return;
	}
	if(amount>foundAccount->balance){
		cout<<"Insufficient Funds!";
		return;
	}
	foundAccount->balance -= amount;
	cout<<"New Balance: "<<foundAccount->balance<<endl;
}
void displayAllAccounts(){
	if(accounts.empty()){
		cout<<"No Account Found"<<endl;
		return;
	}
		cout<<"----------------------"<<endl;
		cout<<"-----All Accounts-----"<<endl;
		cout<<"----------------------"<<endl;

			for (const auto& acc : accounts){
				cout<<"Account N0.: "<<acc.accountNumber<<endl;
				cout<<"Name: "<<acc.customerName<<endl;
				cout<<"Account Type: "<<acc.accountType<<endl;
				cout<<"Balance: "<<acc.balance<<endl;
				cout<<"-----------------"<<endl;
			}
			cout<<"<---------------->"<<endl;
	
}
void checkBalance(){
	int accNum;
	cout<<"Account Number: ";
	cin>>accNum;
	for (const auto& acc : accounts){
		if(acc.accountNumber==accNum){
			cout<<"Customer Name: "<<acc.customerName<<endl;
			cout<<"Balance: "<<acc.balance<<endl;
			return;
		}
	}
	cout<<"Account not found";
}

int main(){
	loadAccounts();
	cout<<"----------------------"<<endl;
    cout<<"Simple Banking System"<<endl;
    cout<<"----------------------"<<endl;
    int choice;
    while(true){
    	cout<<"1.Create Account"<<endl;
    	cout<<"2.Deposit"<<endl;
    	cout<<"3.Withdraw"<<endl;
    	cout<<"4.Display All Accounts"<<endl;
    	cout<<"5.Check Balance"<<endl;
    	cout<<"6.Exit"<<endl;
	
	cout<<"Enter Choice: ";
	cin>>choice;
	switch(choice){
		case 1:
			createAccount();
			break;
		case 2:
			deposit();
			break;
		case 3:
			withdraw();
			break;
		case 4:
			displayAllAccounts();
			break;
		case 5:
			checkBalance();
			break;
		case 6:
			cout<<"Exiting...";
			saveAccounts();
			return 0;
			
		default:
			cout<<"Invalid choice"<<endl;
	}
}
	}
