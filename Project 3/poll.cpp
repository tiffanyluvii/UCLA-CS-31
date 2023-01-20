#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

bool isValidUppercaseStateCode(string stateCode) //this function was given by Professor Smallberg where it gives all the states in capital letters
{
    const string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2 &&
        stateCode.find('.') == string::npos &&  // no '.' in stateCode
        codes.find(stateCode) != string::npos);  // match found
}

bool isValidParty(char Party) { //this function takes in a character and capitalize it, after this it checks if its a letter
    Party = toupper(Party);     //it returns true if it's a letter
    if (isalpha(Party)) {
        return true;
    }
    else {
        return false;
    }
}


bool isValidState(string state) { //this function checks it the string contains a valid state
    string upperState = "";
    for (int i = 0; i < state.size(); i++) { //an empty string is utilized so for every index of the state, it evaluates each letter 
        upperState += toupper(state.at(i));  // in each index and capitalize it. Then it adds it on to the upperState string. This converts 
    }                                       // it to the state but capitalized.

    if (isValidUppercaseStateCode(upperState)) {
        return true;
    }
    else {
        return false;
    }
}

bool isValidPartyResult(string PartyResult) {
    for (int i = 0; i < (PartyResult.size()); i++) {    //it enters a for loop to check if the PartyResult is valid, it'll break out when i is less than the PartyResult
        if (isValidState(PartyResult.substr(0, 2))) {     //it first checks if the first 2 indexes are a valid state (i seperated the poll string by commas so the first 2 indexes should always be a state)
            for (int j = 2; j < PartyResult.size(); j++) {


                if ((j) < PartyResult.size()) {           //then it checks if the 2nd index exist. 
                    j++;                                    //increment j each time if j< PartyResult.size
                    if (isdigit(PartyResult.at(j-1))) {      // if it does, it'll check if it's a digit at the 2nd index. If it's not, it returns false.

                        if ((j) < PartyResult.size()) {    //then it checks if the 3rd index exist.
                            j++;
                            if (isdigit(PartyResult.at(j - 1))) { //if it does, it'll check if it's a digit at 3rd index. If it's a party, 2 is added to i to continue to loop. Anything else returns false.

                                if ((j) < PartyResult.size()) {    //if there's a digit at the 3rd index, it checks if the 4th index exists.
                                    j++;
                                    if (isValidParty(PartyResult.at(j - 1))) {    //if the 4th index exists, it has to be a valid party. If it isn't, it returns false.
                                        j--;                                      //decrement j when there's a party so it doesn't skip an index
                                    }
                                    else {
                                        return false;
                                    }
                                }
                                else {
                                    return false;
                                }
                            }

                            else if (isValidParty(PartyResult.at(j - 1))) {
                                j--;

                            }
                            else {
                                return false;
                            }
                        }
                        else {
                            return false;
                        }
                    }
                    else {
                        return false;
                    }
                }
            }
        }
        else if (!isValidState(PartyResult.substr(0, 2))) { //if the first 2 indexes aren't a valid state, it returns false
            return false;
        }



    }
    return true;
}




bool isValidPollString(string pollData) { 
    bool temp = true;   //sets another boolean variable to use later in the code
    if (pollData == "") { //declares if polldata was an empty string, it's still valid
        return true;
    }
    else {
        char space = ' ';   
        pollData += ','; //adds a comma to the end of the pollData so the following code below can execute
        for (int i = 0; i < pollData.size(); i++) { //a for loop to look at the value at each index
            if (pollData.at(i) == space) {  // if there's a space anywhere, the poll string becomes false
                return false;
            }
            else if (pollData.at(i) != space) { //if there's no space, the following code below will execute
                char comma = ',';
                string tempPollData = "";
                int startingString = 0;


                for (int i = 0; i < pollData.size(); i++) { // a for loop that looks for a comma and seperates the characters previous
                    int endingString = i - startingString;  //to it to make a new temporary string
                    if (pollData.at(i) == comma) {          
                        tempPollData = pollData.substr(startingString, endingString); //the string would be from the starting string and take in the size of the ending string
                        startingString = i + 1;                    // since this code executes when there's a comma, the new starting string would be from the comma's index +1
                        for (int j = 0; j < tempPollData.size(); j++) { //checks if each individual temporary string is a valid party result with
                            if (isValidPartyResult(tempPollData)) {     // the isValidPollString function mentioned above
                                temp = true;                            //sets the boolean to true
                            }
                            else if (!isValidPartyResult(tempPollData)) {
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return temp;
} 
              
int countSeats(string pollData, char party, int& seatCount) {
    
    if (!isValidParty(party)) {  //if it's not a valid poll string, it returns 1
        return 2;
       
    }
    else if (!isValidPollString(pollData)) {    //if it's not a valid party, it returns 2
        return 1;
        
    }
    else if (!isValidParty(party) && !isValidPollString(pollData)) { //if it's not a valid poll string or party, it returns 2
        return 2;
        
    }
    else if (isValidPollString(pollData) && isValidParty(party)) {
        seatCount = 0;
        for (int i = 0; i < pollData.size(); i++) { //ask how we can account for the states like if we're looking for letters
            if (i + 1 >= 3) {
                int seat;
                if (isValidUppercaseStateCode(pollData)) {
                }
                else if (pollData.at(i) == toupper(party) || pollData.at(i) == tolower(party)) {  //looks for the char party at each index i
                    if (isdigit(pollData.at(i - 2))) { //if the char party matches the index i, it looks if 2 indexes before it is a digit
                        //multiply it by 10             //and if it is, it'll convert back to an int and multiplied by 10
                        seat = (pollData.at(i - 2)) - '0';
                        seatCount += (seat * 10);
                        if (isdigit(pollData.at(i - 1))) { //if there's an digit at index i-2, there has to be a digit at index i-1
                            seat = (pollData.at(i - 1)) - '0'; // sets seat to the value of i-1
                            seatCount += seat;                   //adds it to seatCount
                        }
                    }
                    else if (isdigit(pollData.at(i - 1))) {     //if there's no digit at i-2, there has to be one at i-1
                        seat = (pollData.at(i - 1)) - '0';  //set seat to the value of i-1
                        seatCount += seat;                      //adds it to seatCount
                    }
                    else {
                        seatCount += 0; //if none of this works, add zero to seatCount
                    }
                }
            }
       }
    }
   return 0;
}
  

int main() {
    //assert(isValidPollString("MD")); //checks if one state is true
    //assert(isValidPollString("")); //checks if an empty string is true
    //assert(!isValidPollString("CA3 D45e24t")); //checks if there's a space it returns false
    //assert(!isValidPollString("CT5D,Ny9Rf")); //a state with no digits before it
    //assert(!isValidPollString("Ny9R33")); // a number with no party after it
    //assert(!isValidPollString("CT3"));
    //assert(isValidPollString("CT5D,NY9R16D1I,VT,ne3r00D")); //checks if multiple states and results can be taken in
    //assert(!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D")); // checks if multiple states and reults can be taken in
    //assert(!isValidPollString("CT5D,NY9R16D1I,VT2,ne3r00D")); //digit with no state with long poll string
    //assert(!isValidPollString("ZT5D,NY9R16D1I,VT,ne3r00D"));
    //int seats;
    //seats = -999;   
    //assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", 'd', seats) == 0 && seats == 21);  // so we can detect whether countSeats sets seats
    //seats = -999;    
    //assert(countSeats("CT5D,NY9R16D1I,VT,ne3r00D", '%', seats) == 2 && seats == -999); //checks if it returns 1 for invalid party
    //seats = -999;
    //int seats;
    //assert(countSeats("Md42e5c2d,md31e63e3g,ny1d", 'd', seats) == 0 && seats == 3);  // so we can detect whether countSeats sets seats
    //seats = -999;
    //assert(countSeats("ZT5D,NY9R16D1I,VT,ne3r00D", 'e', seats) == 1 && seats == -999); //checks if invalid strings returns 2

   
}


