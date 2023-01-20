// Code for Project 1
	// Report poll results

#include <iostream>
using namespace std;

int main()
{
	int numberSurveyed;
	int forGavin;
	int forBrian;

	cout << "How many registered voters were surveyed? ";
	cin >> numberSurveyed;
	cout << "How many of them say they will vote for Gavin? ";
	cin >> forGavin;
	cout << "How many of them say they will vote for Brian? ";
	cin >> forBrian;

	double pctGavin = 100.0 * forGavin / numberSurveyed;
	double pctBrian = 100.0 * forBrian / numberSurveyed;

	cout.setf(ios::fixed);
	cout.precision(1);

	cout << endl;
	cout << pctGavin << "% say they will vote for Gavin." << endl;
	cout << pctBrian << "% say they will vote for Brian." << endl;
/* The logic error that was implemented would be the aspect that if forGavin < forBrian, "Gavin is predicted to win the election" will 
be executed when Gavin has less votes than Brian which doesn't make sense because Gavin had less votes than Brian. Vice versa will occur.
However, this error won't prevent a sucessful build but just an incorrect one. */
	if (forGavin < forBrian)
		cout << "Gavin is predicted to win the election." << endl;
	else
		cout << "Brian is predicted to win the election." << endl;
}