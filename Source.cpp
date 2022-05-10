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

	// This functions simply push's back transactions to the transactionHistory vector for each client.
	void vecPush(transaction x) 
	{
		trasactionHistory.push_back(x);

	}


	// Here we take in the transaction info and proccess the deposit or withdrawll.
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
	int input = 0;
	cout << "**********************************************************************\n";
	cout << "Welcome to the Bank of UMKC!!! \n Please Select from the options below: \n";
	cout << "\nTo Create a New Bank Customer Press 1." << endl;
	cout << "\nTo add transaction Press 2. " << endl;
	cout << "\nTo Proccess a Transaction Press 3.\n ";
	cout << "\nTo Print a Clients Transaction History Press 4.\n";
	cout << "\nTo Print a Clients Account Total Press 5.\n";
	cout << "\nTo Exit The Program Press 6.\n";
	cout << "**********************************************************************\n";

	cin >> input;

	return input;
}
//OPTION 1
// For the creation of new customers.
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

	// We create the Client and add it to our data base. 
	bankClient x(name, amt);
	clientBase.push_back(x);

	cout << "Client has been added to the Client Base. \n";



}
// OPTION 2
// Used to add transactions to the Stack and to each clients respective transaction history.
void addTransaction()
{
	string name = " ";
	bool x;
	int c;
	double amtProcess;


	cout << "Please Enter the name of the client: ";
	cin >> name;
	
	
	cout << "Would you like this to be a deposit or withdrawll (type in 1 for deposit or any other nuumber for withdrawl): ";
	cin >> c;
	if (c == 1)
		x = true;
	else
		x = false;
		


	cout << "What Amount would you like to process: ";
	cin >> amtProcess;



	for (int i = 0; i < clientBase.size(); i++)
		{
			if (clientBase.at(i).getName() == name)
			{
				// Here we find if we have created a Client with that name & if we have stored them in the clientBase Vector, if that is true we 
				// add the transaction to that spacific clients history (IN THEIR CLASS)  and add them to the stack for processing.
				clientBase.at(i).vecPush(transaction(x,amtProcess));
				clientOrder.push(clientBase.at(i));
				cout << "This Client's Transaction has been added to the Stack. \n" << endl;
					break;
			}
			else if (i == clientBase.size() - 1)
			{
				cout << " \nThis person is not within our System, Please add them in.\n";
			}
	}

	
}
// A function to satisfy the condition of size projection after five POPs in the vector 
void fiveCounter(int& terminate)
{
	cout << "The Size of the Stack: "<< clientOrder.size()<<"\n";
	cout << "The Next Customer that will be Served is: " << clientOrder.top().getName();
	
	terminate = 0;
}

// OPTION 5
// Here is a funtion to check client total by using a clients name.
void clientBankTotal()
{
	string name = " ";

	cout << "Please Enter the name of the client: ";
	cin >> name;

	for (int i = 0; i < clientBase.size(); i++)
	{
		if (clientBase.at(i).getName() == name)
		{
			// Here we find if we have created a Client with that name & if we have stored them in the clientBase Vector, if that is true we 
			// add the transaction to that spacific clients history (IN THEIR CLASS)  and add them to the stack for processing.
			
			cout << "This Client's Account Total is:  \n"<< clientBase.at(i).getCurrentBal() << endl;
			break;
		}
		else if (i == clientBase.size() - 1)
		{
			cout << " \nThis person is not within our System, Please add them in.\n";
		}
	}

}

//OPTION 4
// This function is used to print out the clients history of transactions.
void printClientHistory()
{
	string name;
	cout << "Please Enter the name of the Client: ";
	cin >> name;


	for (int i = 0; i < clientBase.size(); i++)
	{
		if (clientBase.at(i).getName() == name)
		{
			// Here we are calling the printHistory() function from the bankClient Class
			clientBase.at(i).printHistory();
			
			break;
		}
		else if (i == clientBase.size() - 1)
		{
			cout << " \nThis person is not within our System, Please add them in.\n";
		}
	}
}


int main()
{	
	int terminate = 0;
	
	bool carryOn = true;

	while (carryOn)
	{

		switch (mainMenu())
		{
		case 1:
			newCustomer();
			break;
		case 2:
			addTransaction();
			break;
		case 3:

			if (terminate == 5)
			{
				fiveCounter(terminate);
			}
			clientOrder.pop();
			terminate++;
			break;
		case 4:
			printClientHistory();
			break;
		case 5: 
			clientBankTotal();
			break;
		case 6:
			carryOn = false;
			break;

		default:
			break;
		}
	}



	return 0;

}