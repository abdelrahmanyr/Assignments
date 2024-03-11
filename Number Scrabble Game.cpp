/*
- File:     CS112_A1_T5_20230220.py
- Program:  Number Scrabble (Game 2) ->     The game displays a list of available numbers for 2 players 
-                                           and each time a player chooses a number it's added to his account
-                                           the first player to get 3 numbers with sum of 15 wins
-                                           if all numbers were picked but no one satisfied the condition, it's a draw
- Author:   Abdelrahman Yasser Ali  |   20230220    |   Section not registered yet
- Version:  1.0
- Date:     3/3/2024
*/


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to print an array in format of [i, j, k]
string print_list(vector<int> list){
    string nlist = "[";
    if (list.empty()){
        return "[ ] ";
    }
    for (int i = 0; i < list.size(); i++){
        nlist += to_string(list[i]) + ", ";
        
    }
    nlist[nlist.size() - 2] = ']';
    return nlist;
}

// Function to check if a player has satisfied the condition or not
bool check_winner(vector<int> account){
    if (account.size() < 3){
        return false;
    }
    else {
        for (auto i = account.begin(); i != account.end(); i++){
            for (auto j = account.begin(); j != account.end(); j++){
                for (auto k = account.begin(); k != account.end(); k++){
                    if (*k + *j + *i == 15 and (*i != *j) and (*j != *k) and (*i != *k)){
                        cout << "Player has three numbers with sum of 15: (" << *k << ", " << *j << ", " << *i << ")";
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// Function to check if the input is a valid integer and if not, checks again until it return a valid one
string check_number(string n, vector<int> numbers){
    for (int i = 0; i < n.size(); i++){
        if (isdigit(n[i])){                                                 // Check if the input is an integer
            continue;
        }
        else {
            cout << "\n!!!  Wrong number! Please pick again: \nPlease pick a number from " << print_list(numbers) << ": ";
            cin >> n;
            return check_number(n, numbers);
        }
    }

    if (find(numbers.begin(), numbers.end(), stoi(n)) != numbers.end()){    // Check if the input is in the list of available numbers
        return n;
    }
    else {
        cout << "\n!!!  Wrong number! Please pick again: \nPlease pick a number from " << print_list(numbers) << ": ";
        cin >> n;
        return check_number(n, numbers);
    }
}


int main(){
    vector <int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector <int> player_1, player_2;
    string n;

    cout << "<-- Number Scrabble Game -->" << endl;
    cout << "- Each player should pick a number until he has three numbers that add up to 15." << endl;
    cout << "- List of available numbers: ";
    cout << print_list(numbers) << endl;

    while (true){
        /*              Player 1                    */
        cout << "\n<-- Player 1's turn! -->";
        cout << "\nPlayer 1 has " << print_list(player_1) << "in his account";
        cout << "\nPlease pick a number from " << print_list(numbers) << ": ";
        cin >> n;

        n = check_number(n, numbers);                       // After making sure the input number is correct
        numbers.erase(remove(numbers.begin(), numbers.end(), stoi(n)));       // it's removed from the available numbers to pick from
        player_1.push_back(stoi(n));                        // and added to the player's account balance

        if (check_winner(player_1)){
            cout << "\n\n--> Player 1 has won! <--";
            break;
        }

        if (numbers.empty()){                               // Empty array
            cout << "\n--> We have a draw! <--";
            break;
        }

        //__________________________________________________________________________________________
        //__________________________________________________________________________________________

        /*              Player 2                    */
        cout << "\n<-- Player 2's turn! -->";
        cout << "\nPlayer 2 has " << print_list(player_2) << "in his account";
        cout << "\nPlease pick a number from " << print_list(numbers) << ": ";
        cin >> n;

        n = check_number(n, numbers);
        numbers.erase(remove(numbers.begin(), numbers.end(), stoi(n)));
        player_2.push_back(stoi(n));

        if (check_winner(player_2)){
            cout << "\n\n--> Player 2 has won! <--";
            break;
        }

        if (numbers.empty()){
            cout << "\n--> We have a draw! <--";
            break;
        }

    }
}
