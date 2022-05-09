#include <iostream>
#include<stack>
#include<vector>
#include<fstream>

using namespace std;
class transaction // The transactions for each client had a few thing under one umbrella so i grouped them in a class.
{
	bool deposit; // this is to check whether we are working with a deposit or a withdrawal. if this bool is true then its a deposit if false then withdrawal
	double amount;

public:
	transaction(bool deposit, double amount)
	{
		this->deposit = deposit;
		this->amount = amount;
	}
	bool getDeposit()
	{
		return deposit;
	}
	double getAmount()
	{
		return amount;
	}


};

class bankClient
{
	string name;
	double currentBal;
	vector<transaction> trasactionHistory; // I am keeping track of all of the transactions for each client in their respective vector's.

public:

	bankClient(string name,	double currentBal)
	{
		this->name = name;
		this->currentBal = currentBal;
	}
	string getName()
	{
		return name;
	}

	double getCurrentBal()
	{
		return currentBal;
	}
	
	// Here we are simply printing out the history of a client
	void printHistory()
	{
		for (int i = 0; i < trasactionHistory.size(); i++)
		{
			cout << "Transaction Number: " << i + 1<<endl;
			if (trasactionHistory.at(i).getDeposit() == true)
			{
				cout << "This was a Deposit for "<< trasactionHistory.at(i).getAmount()<< endl;

			}
			else 
			{
				cout << "This was a Withdrawal for " << trasactionHistory.at(i).getAmount() << endl;

			}

		}

	}

	void vecPush(transaction x)
	{
		trasactionHistory.push_back(x);

	}


	// Here we take in the transaction info and proccess the deposit or withdrawll
	void processTransaction(transaction x)
	{
		

		int tempVar = trasactionHistory.size() - 1;

		if (trasactionHistory.at(tempVar).getDeposit())
		{
			currentBal = currentBal + trasactionHistory.at(tempVar).getAmount();
		}
		else 
		{
			currentBal = currentBal - trasactionHistory.at(tempVar).getAmount();

		}
	}
	
	



};
vector<bankClient> clientBase;
stack<bankClient> clientOrder;

int mainMenu()
{
	int input;
	cout << "Welcome to the Bank of UMKC!!! \n Please Select from the options below: \n";
	cout << "To Create a New Bank Customer Press 1." << endl;
	cout << "add transaction Press 2: " << endl;
	cout << "To Proccess a Transaction Press 2\n ";
	cout << "To Exit The Program Press 5 \n";

	cin >> input;

	return input;
}

void newCustomer()
{
	double amt;
	string name;

	cout << "New Customer Name: ";
	cin >> name;
	cout << "\n";

	cout << "New Customer Account Balance: ";
	cin >> amt;
	cout << "\n";

	bankClient x(name, amt);
	clientBase.push_back(x);

	cout << "They have been added into our system!!!!";

}

void addTransaction()
{
	string name = " ";
	bool c;
	int amtProcess;


	cout << "Please Enter the name of the client: ";
	cin >> name;
	
	
	cout << "Would you like this to be a deposit or withdrawll (type in true for deposit or false or withdrawl): ";
	cin >> c;

	cout << "What Amount would you like to process: ";
	cin >> amtProcess;


		for (int i = 0; i < clientBase.size(); i++)
		{
			if (clientBase.at(i).getName() == name)
			{
				clientBase.at(i).processTransaction(transaction(c,amtProcess));
					break;
			}
		}

	
}


int main()
{	
	int terminate = 5;
	
	int choice = mainMenu();
	// YOU HAVE GOTTEN THE CLASSES TAKEN CARE OF YOU NOW NEED TO 
	// MAKE A MENU THAT ALLOWS FOR { ADDING TO STACK, POPING FROM STACK, PRINTING ACCOUNT HISTORY}
	// AND ALSO NEED TO INRTODUCE A COUNTER THAT RESETS AFTER FIVE CLIENTS ARE PROCCESED
	//READ THE LAST SENTANCE IN THE GUIDLINES FOR #3


	switch (choice)
	{
	case 1:
		newCustomer();
		break;
	case 2:
		void addTransaction();
		break;
	case 3:
		clientOrder.pop();
	default:
		break;
	}



	return 0;

}