#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value) {
	if (n >= 0) { //n can't be negative 
		for (int i = 0; i < n; i++) {
			a[i] += value; // adds the value to the string at that index position
		}
		return n;
	}
	return -1; //returns -1 if n is negative
}

int lookup(const string a[], int n, string target) { 
	if (n >= 0) {
		for (int i = 0; i < n; i++) {
			if (a[i] == target) { //checks if a[i] is equal to that target
				return i; //what do you mean return the smallest position number?
			}
		}
	}
	return -1;
}

int positionOfMax(const string a[], int n) { //work on this like what determines if it's max
	string temp= a[0]; //sets the max string to the first position
	int ipos=0;
	//if (n == 0) { //if there's only one item, that item will be the max
	//	return 0; 
	//}
	if (n > 0) { //checks if n is positive
		for (int i = 0; i < n; i++) {
			if (temp < a[i]) { //checks if the next string is greater than the next index
				temp = a[i];
				ipos = i;
			}
		}
		return ipos;
	}
	return -1;
		
}

int rotateLeft(string a[], int n, int pos) {
	string temp;
	int j = pos;

	if (pos >= n) {}

	return -1;

	if (n >= 0 && pos>=0) { //checks n and pos are positive
		for (int i = 0; i < n; i++) { //goes through each index of the array
			if (pos == i) { //if the index matches the pos go into this for loop
				temp = a[pos];
				for (j = pos; j < n; j++) {
				
					if ((j + 1) < (n)) { //make sure it doesn't go out of bound
						a[j] = a[j + 1]; //sets the current index to that infront of it
					}
				}
			a[n - 1] = temp; // how to add something to the end of an array
		}
			
	}
		return pos;
}
	return -1;
}

int countRuns(const string a[], int n) {
	string temp = a[0];
	if (n >= 0) { //make sure n is positive
		if (n == 0) {
			return 0;
		}
		else if (n >= 0) {
			int items = 0; //sets the counter to 0 incase of an empty string
			for (int i = 0; i < n; i++) {
				if (temp != a[i]) { //checks if there's a consecutive line of words
					temp = a[i];	//if there isn't, add one to the counter
					items++;
				}
			}
			return (items + 1); // return the counter + 1 incase of the empty string
		}
	}
	return -1;
}

int flip(string a[], int n) {
	if (n >= 0) { //make sure n is postive
		string temp = a[0]; // sets a temporary variable to the start of the array
		int tempn = n - 1; //sets a variable to find the end of the array 
	if (n == 0) {
		return 0;
	}
	else if (n >= 0) {
		for (int i = 0; i < n / 2; i++) { //splits the distance in half so it only changes half of the string
			a[i] = a[tempn]; //makes the last index (at n) the first index
			a[tempn] = temp; //makes the first index the last index (at n)
			temp = a[i + 1]; //changes temp and tempn to switch the variable within the first and last index 
			tempn -= 1;
		}
		return n;
	}
	}
	return -1;  //if nothing else returns, return -1 bc this means there's a bad argument
}

int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 >= 0 && n2 >= 0) {
		for (int i = 0; i < n1; i++) { //runs through each index to see if the position 
			if (a1[i] != a2[i]) {	// at a1[i] is equal to a2[i]
				return i;
			}
		}
	}
	if (n1 <= n2) { //if nothing is different, return the value that of n
		return n1; // that is smaller
	}
	else if (n2 <= n1) {
		return n2;
	}
	else if (n1==0 || n2==0) { //if n1 or n2 is 0, return o
		return 0;
	}
	return -1;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
	int count = 0;
	int i_temp;
	if (n2 == 0 && n1 >= 0 && n2 >= 0) { //if n2 was a string with 0 elements
		return 0;
	}
	else if (n1 >= 0 && n2 >= 0 && n2 < n1) { // double checks if n1 and n2 are positive and if n1 is greater than n2
		for (int i = 0; i < n1; i++) { //examines each index up to the value of n1
			for (int j = 0; j < n2; j++) { //examines each index up to the value of n2
				if(a1[i] == a2[j]) { 
					i_temp = i; //sets i_temp to the position of i just incase it's a sequence
					count++; //for each matching index, count goes up one
					i++;
					if (count == n2) { //if all sequences are present, the count should match up with n2
						return i_temp -  (n2 - 1); //i_temp returns the farthest index of the string so subtract the size (n2) and one to find the beginning
					}

				}
				else {
					count = 0; //if the sequence ever messes up, the count restarts
				}
			}
		}
	}
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) { 
	if (n1 >= 0 && n2 >= 0) { //checks if n1 and n2 are positive integers
		for (int i = 0; i < n1; i++) { //if they are, check if an item in array a1 
			for (int j = 0; j < n2; j++) { //is located in array a2
				if (a1[i] == a2[j]) {
					return i;
				}
			}
		}
	}
	return -1;
}


int split(string a[], int n, string splitter) { //what happens if splitter is in the array
	int split = 0;
	string temp;
	string split_temp;
	if (n >= 0) { //checks if n is a positive integer
		for (int i = 0; i < n; i++) {
			if (a[i] > splitter) { //if the element at index i is greater than the splitter
				temp = a[i];
				for (int j = i; j < n; j++) {
					if ((j + 1) < (n)) { 
						a[j] = a[j + 1]; //move everything to the left
					}
				}
				a[n - 1] = temp; //and move the element to the end
			}
			else if (a[i] == splitter) { //checks if splitter is in the array
				split_temp = a[i]; //set temp split variable to the splitter
				a[split] = split_temp; //make the split index equal to the splitter
				split++; //increase the index
			}
			else {
				split++; //increase the index
			}

		}
		for (int i = 0; i < n; i++) {
			if (a[i] > splitter) { //with the new array, check what element is first to be greater than splitter
				return i;
			}
		}
		return n; //if they're all less than or is the splitter, return n
	}
	return -1;
}



int main() {
	//string h[7] = { "tiffany", "ryan","grace","sacha","gabe", "tyler", "simona" };
	//assert(lookup(h, 7, "tiffany") == 0); //checks if it'll return the correct position
	//assert(lookup(h, 7, "ryan") == 1); //checks if it'll return the correct position
	//assert(lookup(h, 7, "tyler") == 5); //checks if it'll return the correct position
	//assert(lookup(h, -1, "tiffany") == -1); //checks if it'll return -1 because of the negative n value
	//assert(lookup(h, 3, "tyler") == -1); //checks if it'll return -1 since tyler isn't in the first 3 elements
	//assert(positionOfMax(h,7) == 5); //checks if the max is correctly executed (tyler > tiffany)
	//assert(positionOfMax(h, -10) == -1); //checks if it'll return -1 because of a bad argument

	//assert(positionOfMax(h, 2) == 0); //checks if it can only take in an integer that equals the amount of elements in the array (are they checking when n is less than the amount of elements)
	//assert(appendToAll(h, 7, "!!!") == 7 && h[0] == "tiffany!!!" && h[2] == "grace!!!"); //checks if it adds the string correctly
	//assert(appendToAll(h, 7, "!") == 7 && h[0] == "tiffany!!!!" && h[2] == "grace!!!!"); //checks if it'll add a string on top of the modified array
	//assert(countRuns(h, 7) == 7); //checks if each element is counted as one item

	//string fruits[4] = { "peach", "cherry","strawberry","mango"};
	//assert(countRuns(fruits, 4) == 4); //checks that each index is one consecutive item
	//assert(countRuns(fruits, 2) == 2);  //checks that each index is one consecutive item up to 2 elements
	//assert(flip(fruits, 4) == 4 && fruits[0] == "mango" && fruits[2] == "cherry"); //checks if the entire array flips
	//assert(flip(fruits, -4) == -1); //negative n value flip
	////assert(flip(fruits, 2) == 2 && fruits[0] == "cherry" && fruits[2] == "strawberry"); //checks if part of an array can be flipped without messing up the other part of the array
	//assert(differ(h, 4, fruits, 4) == 0); //checks that it differs at the 0 index
	//assert(rotateLeft(fruits, -3, 1) == -1); //checks if it'll return -1 because of the negative n value
	//assert(rotateLeft(fruits, 3, -1) == -1); //checks if it'll return -1 because of the negative pos value
	//assert(lookupAny(h, 7, fruits, 4) == -1); //checks if there's no elements in fruits that are the same in h, return -1
	//

	//string a[7] = { "rishi", "margaret", "gordon", "tony", "", "john", "liz" };
	//assert(lookup(a, 7, "john") == 5); //checks if it'll return the correct position
	//assert(lookup(a, 7, "gordon") == 2); //checks if it'll return the correct position
	//assert(lookup(a, 2, "gordon") == -1); //checks if it'll return -1 since gordon isn't in the first 2 elements
	//assert(positionOfMax(a, 7) == 3); //checks that tony is the max of the string
	//

	//string g[4] = { "rishi", "margaret", "liz", "theresa" };
	//string g2[6] = { "rishi", "margaret", "liz", "theresa", "extra","extra"};
	//assert(differ(a, 4, g, 4) == 2); //shows that the string differs at index 2
	//assert(differ(g, 4, g2, 6) == 4); //checks that differ will return the lower value of n1 and n2 when strings run out and it's not different
	////assert(differ(a, -4, g, -4) == -1); //checks if it'll return -1 because of the negative n value
	//assert(appendToAll(g, 4, "?") == 4 && g[0] == "rishi?" && g[3] == "theresa?");//adds ? to each string of the index
	//assert(rotateLeft(g, 4, 1) == 1 && g[1] == "liz?" && g[3] == "margaret?");//checks that it correctly rotates

	//string e[4] = { "gordon", "tony", "", "john" };
	//assert(subsequence(a, 7, e, 4) == 2); //checks that the subsequence does exist and it begins at index 2
	//assert(subsequence(h, 7, e, 4) == -1); //checks that if the subsequence doesn't exist in the main sequence, -1 will be returned

	//string d[5] = { "margaret", "margaret", "margaret", "tony", "tony" };
	//assert(countRuns(d, 5) == 2); // checks that there are 2 continuous segments of items
	////assert(positionOfMax(d,5) == 4);

	//string f[3] = { "liz", "gordon", "tony" };
	////assert(lookupAny(a, 7, f, 3) == 2); //checks the first index in a that has an item in f
	////assert(flip(f, 3) == 3 && f[0] == "tony" && f[2] == "liz"); //checks if it'll flip an array with an odd amount of integers correctly
	//assert(split(f, 3, "liz") == 2); //checks if split works

	//string same[7] = { "help","help","help","help","help","help","help" };
	//assert(split(same, 7, "help") == 7); //checks if split will return n if nothing is greater than splitter
	//assert(split(same, -1, "help") == -1); //checks if -1 will return because of negative n value

}


