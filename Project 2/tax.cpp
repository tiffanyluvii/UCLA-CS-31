
using namespace std;
#include <iostream>
#include <string>

int main()
{

	string name = "";
	string occupation = "";
	int numberofChildren;
	double childrenTax = 0.0;
	double taxableIncome, tax;
	double ataxableIncome = 0.0; 
	double btaxableIncome = 0.0;
	double ctaxableIncome = 0.0;


	cout << "Name: ";
	getline(cin, name);
	cout << "Taxable income: ";
	cin >> taxableIncome;
	cin.ignore(10000, '\n');
	cout << "Occupation: ";
	getline(cin, occupation);
	cout << "Number of children: ";
	cin >> numberofChildren;
	cout << "---" << endl;

	double originaltaxableIncome = taxableIncome; //setting taxable income to a variable before future codes scew taxableIncome

	// code for invalid name
	if (name == "") {
		cout << "You must enter a name";
		return 1;
	}
		
	// code for negative income
	if (taxableIncome < 0) {
		cout << "The taxable income must not be negative" << endl;
		return 1;
	}

	// code for invalid occupation
	if (occupation == "") {
		cout << "You must enter an occupation" << endl;
		return 1;
	}

	// code for negative children 
	if (numberofChildren < 0) {
		cout << "The number of children must not be negative" << endl;
		return 1;
	}


	//income tax calculations
	if (taxableIncome <= 55000 && taxableIncome > 0) { //this code is for when income is less than $55000
		ataxableIncome = (0.04 * taxableIncome);
	}
	else if (taxableIncome > 55000) { // this code is for when income is more than $55000
		ataxableIncome = (0.04 * 55000);
		taxableIncome = (taxableIncome - 55000);

		if ((taxableIncome <= 70000 && taxableIncome > 0) && (occupation == "nurse" || occupation == "teacher")) { 
			btaxableIncome = (taxableIncome * 0.05);
			//this code for when the (income - 50000) is less than 70000 and their occupation is a nurse or teacher
		}else if ((taxableIncome <= 70000 && taxableIncome > 0) && (occupation != "nurse" && occupation != "teacher")) {
			btaxableIncome = (taxableIncome * 0.07);
			//this code for when the (income - 50000) is less than 70000 and their occupation isn't a nurse or teacher
		}else if ((taxableIncome > 70000 ) && (occupation == "nurse" || occupation == "teacher")) {
			btaxableIncome = (0.05 * 70000);
			taxableIncome = (taxableIncome - 70000);
			//this code for when the (income - 50000) is more than 70000 and their occupation is a nurse or teacher
			if (taxableIncome > 0) {
				ctaxableIncome = taxableIncome * 0.093;
			//this code is for when the income exceeds 125000 as a nurse or teacher
			}
		}
		else if ((taxableIncome > 70000) && (occupation != "nurse" && occupation != "teacher")) {
			btaxableIncome = (0.07 * 70000);
			taxableIncome = (taxableIncome - 70000);
			//this code for when the (income - 50000) is more than 70000 and their occupation isn't a nurse or teacher
			if (taxableIncome > 0) {
				ctaxableIncome = taxableIncome * 0.093;
			//this code is for when the income exceeds 125000 not as a nurse or teacher
			}
		}
	}

	//code taxable income with the account for kids
	tax = ataxableIncome + btaxableIncome + ctaxableIncome; 
	if (numberofChildren != 0 && originaltaxableIncome < 125000) { //originaltaxableIncome is used here because the if statements above changes the taxableIncome
		childrenTax = (numberofChildren * 200);
		tax = tax - childrenTax;
	}
	else if (numberofChildren == 0 || originaltaxableIncome >= 125000) {
		tax = tax;  
	}

	cout.setf(ios::fixed); //setting the price to 2 decimal points
	cout.precision(2);

	if (tax < 0) { //code for when the amount of children that an individual has makes the tax negative
		cout << name << " would pay $0";
	}
	else { 
		cout << name << " would pay $" << tax;
	}

}