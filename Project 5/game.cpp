#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:6262)
#include "utilities.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const char WORDFILENAME[] = "words.txt";


const int MAXWORDS = 9000;
const int MAXWORDLENGTH = 6;
void isGoldandSilver(const char words[], char probe[]);
bool isInDictionary(char dictionary[MAXWORDS][MAXWORDLENGTH + 1], char word[], int n);
int playOneRound(const char words[][MAXWORDLENGTH + 1], int nWords, int wordnum); 
void negativeRounds(int numOfRounds);



int main()
{
	cout.setf(ios::fixed);//ensures that the average will have 2 decimal points after it
	cout.precision(2);
	//int randInt(int min, int max);

	char w[MAXWORDS][MAXWORDLENGTH+1]; //declares the character array
	int n = getWords(w, MAXWORDS, WORDFILENAME); //w:character array that you put all the words into, 9000: number of words you grab from the file (change later), path to word file
	//the declaration above brings words from WORDFILENAME and puts it into array w 
	

	int numOfRounds;
	int minimum, maximum, temp_min, temp_max;
	double average;
	int score_total = 0;

	if (n < 1) { // checks if getWords is working properly
		cout << "No words were loaded, so I can't play the game." << endl;
	}

	if (n >= 1) {
		cout << "How many rounds do you want to play? ";
		cin >> numOfRounds;
		cin.ignore(10000, '\n');
		negativeRounds(numOfRounds); //checks if user enters a negative number of rounds
		for (int i = 1; i <= numOfRounds; i++) {
			cout << "\n";
			cout << "Round " << i << endl;
			int wordnum = randInt(0, n - 1); //the random number generated 
			cout << "The hidden word is " << strlen(w[wordnum]) << " letters long." << endl; //how to switch int to char
			//playOneRound(w, MAXWORDS, wordnum); //calls the playOneRound function and plays the game


			int score = playOneRound(w, n, wordnum); //sets score to the int it returns and initiates the function playOneRound


			if (score == 1) { //if score was one try, print out this sentence
				cout << "You got it in 1 try." << endl;
			}
			else if (score > 1) { //if score was greater than one try, print out this sentence
				cout << "You got it in " << score << " tries." << endl;
			}

			//checks the score of it
			if (i == 1) {
				minimum = score; //since it's the first round, min and max will be the amount of tries
				maximum = score;
				score_total += score; //updates the score for each round
				average = static_cast<double>(score_total) / i; // and divides it by the number of rounds for the average
				cout << "Average: " << average << ", minimum: " << minimum << ", maximum: " << maximum << endl;
			}
			else if (i > 1) {
				temp_min = score; //sets a temp min and max for any future scores
				temp_max = score;
				if (temp_min < minimum) { //checks if the score of the future rounds was smaller than the 
					minimum = temp_min;	//round before it and updates it
				}
				if (temp_max > maximum) { //checks if the score of the future rounds was bigger than the
					maximum = temp_max; //round before it and updates it
				}
				score_total += score; //updates the score for each round
				average = static_cast<double>(score_total) / i; // and divides it by the number of rounds for the average
				cout << "Average: " << average << ", minimum: " << minimum << ", maximum: " << maximum << endl;
			}
		}
	}
}

bool isInDictionary(const char dictionary[MAXWORDS][MAXWORDLENGTH + 1], char word[], int n) { //use strcmp !=0 and use a loop
	bool check = false;			//maybe switch it to a void function
	for (int i = 0; i< n; i++) { //continues until i reaches n(the amount of words in the dictionary)
		if (strcmp(dictionary[i], word) == 0) { //checks if the word is ever in the dictionary
			check = true;	//if it is, it'll return true
			return check;
		}
	}	
	return check; //if it never returns true, it'll return false
} 


void isGoldandSilver(const char words[], char probe[]) { //def work on this function
	int gold = 0;
	int silver = 0;
	char temp_word[MAXWORDLENGTH +1]; //is there a way to declare a temp syntax to words and probe
	char temp_probe[MAXWORDLENGTH + 1];
	strcpy(temp_word, words); //copies words and probe into their temporary c string
	strcpy(temp_probe, probe);

	if (strcmp(words, probe) != 0) { //is this the correct syntax for checking if words and probe are equal to each other
		for (int i = 0; temp_word[i] != '\0'; i++) {
			//check each index of the hidden word and compare it to the words[i]
			for (int j = 0; temp_probe[j] != '\0'; j++) {
				if (i == j && words[i] == probe[j]) { //checks if the index are the same and if the letters are
					gold++;				//the same to consider it a gold
					temp_probe[j] = '/'; //gets rid of the letter in the probe word
					temp_word[i] = '-';	//gets rid of the letter in the actual word
					break;
				}
			}
		}

		for (int i = 0; temp_word[i] != '\0'; i++) {
			for (int j = 0; temp_probe[j] != '\0'; j++) {
				if (temp_word[i] == temp_probe[j]) { //if it's not the same index, it checks if there's a letter 
					silver++;					//that's the same to consider for the silvers
					temp_probe[j] = '/'; //gets rid of the letter in the probe word
					temp_word[i] = '-';	//gets rid of the letter in the actual word
					break;
				}
			} 
		}
		
		cout << "Golds: " << gold << ", " << "Silvers: " << silver << endl; //prints out the amount of gold and silvers
	}


}


int playOneRound(const char words[][MAXWORDLENGTH + 1], int nWords, int wordnum) { //return nWords;
	char probe[150] = ""; //setting the index to 150 so user can enter any word that wouldn't crash the system but would allow
	//"Your probe word must be a word of 4 to 6 lower case letters." to print out
	int tries = 0;

	if (nWords < 0 || wordnum < 0 || wordnum >= nWords) { //checks if playOneRound can execute without error
		return -1;

	}

	while (strcmp(probe, words[wordnum]) != 0) {
		//cerr << words[wordnum] << endl;

		cout << "Probe word: ";
		cin.getline(probe, 150);
		int i = 0;
		bool error = true; //uses a bool method to check what error message gets printed out

		if (!islower(probe[i]) || strlen(probe) > 6 || strlen(probe) < 4 || !isInDictionary(words, probe, nWords)) {
			for (int i = 0; probe[i] != '\0'; i++) {
				if (!islower(probe[i])) { //checks if the probe word is a lower case letter
					error = true;
					break;
				}
				else if (strlen(probe) > 6 || strlen(probe) < 4) { //checks if the probe word has between 4-6 letters
					error = true; 
				}
				else if (!islower(probe[i]) && strlen(probe) <= 6 && strlen(probe) >= 4) { //checks if the probe word has between 4-6 letters and doesn't include a random character
					error = true;
				}
				else if (!isInDictionary(words, probe, nWords) && islower(probe[i]) && (strlen(probe) <= 6 && strlen(probe) >= 4)) { //checks if the word is in the dictionary 
					error = false;
				}
			}
			if (error) { //the error determines what error message gets printed out
				cout << "Your probe word must be a word of 4 to 6 lower case letters." << endl;
			}
			else if (!error) {
				cout << "I don't know that word." << endl;
			}
		}

		else { //if none of the criterias above are met, enter isGoldandSilver to get the function
			isGoldandSilver(words[wordnum], probe);
			tries++;
		}

	}
	return tries;

}

void negativeRounds(int numOfRounds) { //checks if the round inserted is negative
	if (numOfRounds <= 0) { //must be greater than 0
		cout << "The number of rounds must be positive.";
	}
}



