/* 
FCAI – Structured Programming (CS112) | 2024 | Assignment 2 | Task 4
Program Name:           Cipher System.cpp

Program Description:    Cipher/Decipher System that has 4 different ciphers
                        Affine / Route / Vigenere / Atbash

Author:                 Abdelrahman Yasser

Last Modification Date: 19/3/2024
Professor:              Dr.Mohamed El-Ramly
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Formula for affine cipher
int affine_(int chr, int a, int b){
    int cipher = (a*(chr - 65) + b) % 26;
    char chrc = (cipher + 'A');
    return chrc;
}

// Formula for affine decipher
int de_affine(int chr, int b, int c){
    int cipher = c*((chr - 65) - b);
    int modulo = ((26 + ((cipher) % 26)) % 26); // The only difference here is adding 26 and getting modulo again
    char chrc = (modulo + 'A');                 // to handle negative values
    return chrc;
}

// 0. Affine Cipher
void affine(){
    cout << "=======================\n";
    cout << "==== Affine Cipher ====\n";
    cout << "=======================\n";
    cout << "= Affine cipher is an encryption cipher that uses the formula (ax + b % 26)\n" 
         << "  where x is the order of the character starting from Zero\n"
         << "= You can encrypt a text but any non-alphabetical characters will be removed\n";
    
    while (true) {
        string choice;
        string def;
        cout << "\n1) Encrypt\n2) Decrypt\n3) Exit\n- Enter your choice\n--> ";
        cin >> choice;
        // Check if choice is valid
        while (choice != "1" && choice != "2" && choice != "3") {
            cout << "- Invalid choice! Please pick a number between 1 and 3\n";
            cout << "\n1) Encrypt\n2) Decrypt\n3) Exit\n- Enter your choice\n--> ";
            cin >> choice;    
        }

        if (choice == "3")
            break;

        cout << "\n1) Default\n2) Enter (ax + b)%26 | c (y - b)%26\n- Enter your choice\n--> ";
        cin >> def;
        // Check if choice is valid
        while (def != "1" && def != "2") {
            cout << "- Invalid choice! Please pick a number between 1 and 2\n";
            cout << "\n1) Default\n2) Enter (ax + b)%26 | c (y - b)%26\n- Enter your choice\n--> ";
            cin >> def;
        }

        // Initialize variables with the default values to put in the formula
        string x = "5";
        string y = "8";
        string z = "21";
        int a, b, c;    // Actual variables used in the formula

        if (def == "2") {
            cout << "- Enter (a) (b) (c)\n --> ";
            cin >> x >> y >> z;
            while (true) {
                try {
                    a = stoi(x);    b = stoi(y);    c = stoi(z);
                    break;
                }
                catch (const invalid_argument) {// Check if a b c are valid integers
                cout << "- Invalid numbers! Please insert correct integers\n"
                     << "- Enter (a) (b) (c)\n--> ";
                cin >> x >> y >> z;
                }
            }
            // Check for the condition required to cipher and decipher successfully
            while (((a * c) % 26) != 1) {
                cout << "- Invalid values! You must satisfy the equation [(a * c) % 26 = 1]\n- Enter (a) (b) (c)\n--> ";
                cin >> x >> y >> z;
            }
        }
        
        a = stoi(x);    b = stoi(y);    c = stoi(z);
        string out = "";
        string text;
        cout << "- Enter your text\n" << "--> ";
        cin.ignore();
        getline(cin, text);

    // Loop on text and add the uppercase letters after conversion to the output
    for (int i = 0; i < text.length(); i++){
        if (isalpha(text[i])){
            int chr = toupper(text[i]);
            if (choice == "1") {
                char f = affine_(chr, a, b);
                out += f;
            }
            
            else if (choice == "2") {
                char f = de_affine(chr, b, c);
                out += f;
            }
        }
    }

    cout << "<--- "<< out << " --->" << endl;
    }
}

// 1. Route Cipher
void route () {
    cout << "========================\n"
         << "===== Route Cipher =====\n"
         << "========================\n"
         << "= Route cipher is an encryption cipher that stores the text in a matrix (2D Array)\n" 
         << "  with number of columns equals to the entered key\n"
         << "  and if there are empty slots in the matrix they are replaced with X\n"
         << "= After that the text is collected using a spiral path in the matrix and printed as an encrypted text\n"
         << "= You only need to a insert the key and the text to encrypt/decrypt\n";

    while (true) {
        string choice;
        cout << "\n1) Encrypt\n2) Decrypt\n3) Exit\n- Enter your choice\n--> ";
        cin >> choice;
        while (choice != "1" && choice != "2" && choice != "3") {
            cout << "- Invalid choice! Please pick a number between 1 and 3\n";
            cout << "\n1) Encrypt\n2) Decrypt\n3) Exit\n- Enter your choice\n--> ";
            cin >> choice;    
        }

        if (choice == "3")
            break;

        if (choice == "1") {

            char key;
            cout << "- Input key\n--> ";
            cin >> key;

            // Check if the key is valid
            while (!isdigit(key)) {
                cout << "- Invalid input! Please enter a valid integer for the matrix width\n--> ";
                cin >> key;
            }

            // Assign the width (number of columns of matrix) - Number of elements in each array
            int width = key - '0';
            string out;
            string text;
            cout << "- Input text\n--> ";
            cin.ignore();
            getline(cin, text);
            // Remove each character that is not an alphabet letter
            text.erase(remove_if(text.begin(), text.end(), [](char x) {return !isalpha(x);}), text.end());            

            // Add X if the text length is shorter than (width*height)
            for (int i = 0; i < width; i++) {
                if (text.length() % width == 0) {
                    break;
                }
                else {
                    text += "X";
                }
            }

            // Assign the height (number of rows of the matrix) - Number of arrays in the main array
            int height;
            height = text.length() / width;

            vector <vector<char>> matrix;

            int count = 0;  // Counter for the text characters
            // Create the matrix and add characters of text to the 2D Array from left to right
            for (int j = 0; j < height; j++) {
                matrix.push_back({});
                for (int k = 0; k < width; k++) {
                    matrix[j].push_back(toupper(text[count]));
                    count++;
                }
            }

            string encrypt = "";
            string dir = "down";
            // Initialize boundaries of the matrix
            int max_top = 0, max_left = 0;
            int max_bot = height - 1;
            int max_right = width - 1;

            // Spiral Loop
            // Loop until we reach the far right and the far bottom
            // We collect each element encountered in the direction we are going through
            // Every time we subtract one from the boundary we are going towards
            // Then change direction
            while (max_top <= max_bot && max_left <= max_right) {
                if (dir == "down") {
                    for (int i = max_top; i <= max_bot; i++) {
                        encrypt += matrix[i][max_right];
                    }
                    --max_right;
                    dir = "left";
                }
                // ______________________
                else if (dir == "left") {
                    for (int i = max_right; i >= max_left; i--) {
                        encrypt += matrix[max_bot][i];
                    }
                    --max_bot;
                    dir = "up";
                }
                // ______________________
                else if (dir == "up") {
                    for (int i = max_bot; i >= max_top; i--) {
                        encrypt += matrix[i][max_left];
                    }
                    ++max_left;
                    dir = "right";
                }
                // ______________________
                else if (dir == "right") {
                    for (int i = max_left; i <= max_right; i++) {
                        encrypt += matrix[max_top][i];
                    }
                    ++max_top;
                    dir = "down";
                }
                // ______________________
            }

            cout << "--> " << encrypt << " <--\n";
        }

        else if (choice == "2") {
            char key;
            cout << "- Input key\n--> ";
            cin >> key;

            while (!isdigit(key)) {
                cout << "- Invalid input! Please enter a valid integer for the matrix width\n--> ";
                cin >> key;
            }
            int width = key - '0';

            string out;
            string text;
            cout << "- Input text\n--> ";
            cin.ignore();
            getline(cin, text);
            text.erase(remove_if(text.begin(), text.end(), [](char x) {return !isalpha(x);}), text.end());

            int height = text.length() / width;

            // Create the matrix with initial values of X
            vector <vector<char>> matrix;
            int count = 0;
            for (int j = 0; j < height; j++) {
                matrix.push_back({});
                for (int k = 0; k < width; k++) {
                    matrix[j].push_back('X');
                    count++;
                }
            }
            count = 0;

            string dir = "down";
            int max_top = 0, max_left = 0;
            int max_bot = height - 1;
            int max_right = width - 1;

            count = 0;
            // Using the same spiral loop but we add the characters from the encrypted text (reverse of the encryption method)
            while (max_top <= max_bot && max_left <= max_right) {
                if (dir == "down") {
                    for (int i = max_top; i <= max_bot; i++) {
                        matrix[i][max_right] = toupper(text[count]);
                        count++;
                    }
                    --max_right;
                    dir = "left";
                }
                // ______________________
                else if (dir == "left") {
                    for (int i = max_right; i >= max_left; i--) {
                        matrix[max_bot][i] = toupper(text[count]);
                        count++;
                    }
                    --max_bot;
                    dir = "up";
                }
                // ______________________
                else if (dir == "up") {
                    for (int i = max_bot; i >= max_top; i--) {
                        matrix[i][max_left] = toupper(text[count]);
                        count++;
                    }
                    ++max_left;
                    dir = "right";
                }
                // ______________________
                else if (dir == "right") {
                    for (int i = max_left; i <= max_right; i++) {
                        matrix[max_top][i] = toupper(text[count]);
                        count++;
                    }
                    ++max_top;
                    dir = "down";
                }

                // ______________________
            }

            // After adding the characters we collect the characters from left to right (reverse of the encryption method)
            for (int j = 0; j < height; j++) {
                for (int k = 0; k < width; k++) {
                    out += matrix[j][k];
                }
            }
            cout << "--> " << out << " <--\n";
        }
    }
}

// 3. Vigenere Cipher
void vigenere() {
    cout << "===========================\n"
         << "===== Vigenere Cipher =====\n"
         << "===========================\n"
         << "= Vigenere cipher is an encryption cipher that uses a mathematical formula to encrypt text:\n"
         << "  [ascii(char + key_char) % 26 + 65]\n"
         << "= You have to enter a key of max 8 characters and text of 80 characters\n"
         << "= Every alphabetic character will be converted to uppercase\n";

    while (true) {
        string choice;
        cout << "\n1) Encrypt\n2) Decrypt\n3) Exit\n- Enter your choice\n--> ";
        cin >> choice;
        while (choice != "1" && choice != "2" && choice != "3") {
            cout << "- Invalid choice! Please pick a number between 1 and 3\n";
            cout << "\n1) Encrypt\n2) Decrypt\n3) Exit\n- Enter your choice\n--> ";
            cin >> choice;    
        }

        if (choice == "3")
            break;

        cout << "- Enter a text to encrypt\n--> ";
        string text, enc, dec;
        cin.ignore(1, '\n');
        getline(cin, text);
        // Checking the text length does not exceed 80
        while (text.size() > 80) {
            cout << "- Invalid input! Please enter a text of max. 80 letters\n--> ";
            getline(cin, text);
        }
        
        cout << "- Enter a keyword\n--> ";
        string key;
        getline(cin, key);
        cout << key << endl;
        // Checking the key length does not exceed 8
        while (key.size() > 8) {
            cout << "- Invalid input! Please enter a keyword of max. 8 letters\n--> ";
            getline(cin, key);
        }

        int count = 0;
        if (choice == "1") {

            int add;
            for (int i = 0; i < text.length(); i++) {
                // Capitalize each alpha character from text and key then apply the formula
                if (isalpha(text[i]) && isalpha(key[count])) {
                    add = ((toupper(text[i]) + toupper(key[count])) % 26) + 65;
                    enc += (char) add;
                }

                else {  // Any non-alpha character will stay as it is in the same place
                    enc += text[i];
                }

                count++;
                if (count >= key.length())
                    count = 0;
            }
            cout << "--> " << enc << " <--\n";
        }

        else if (choice == "2") {
            int sub;
            for (int i = 0; i < text.length(); i++) {
                if (isalpha(text[i])) {
                    // Same formula for encryption but instead we subtract the char from char_key and modify the modulo method
                    sub = ((26 + ((toupper(text[i]) - toupper(key[count])) % 26))) % 26 + 65;
                    dec += (char) sub;
                }

                else {
                    dec += text[i];
                }

                count++;
                if (count >= key.length())
                    count = 0;
            }
            cout << "--> " << dec << " <--\n";

        }
    }
}

// 2. Atbash Cipher
void atbash() {
    cout << "===========================\n"
         << "====== Atbash Cipher ======\n"
         << "===========================\n"
         << "= Atbash cipher is an encryption cipher that uses a mathematical formula to encrypt text:\n"
         << "  [ascii(Z - upper_char) + 65] so that A becomes Z and B becomes Y and so on..\n"
         << "= Basically both encryption and decryption uses the same formula\n"
         << "= Every alphabetic character will be converted to uppercase and any other characters will stay the same\n";

    while (true) {
        string choice;
        cout << "\n1) Encrypt\n2) Decrypt\n3) Exit\n- Enter your choice\n--> ";
        cin >> choice;
        while (choice != "1" && choice != "2" && choice != "3") {
            cout << "- Invalid choice! Please pick a number between 1 and 3\n";
            cout << "\n1) Encrypt\n2) Decrypt\n3) Exit\n- Enter your choice\n--> ";
            cin >> choice;    
        }

        if (choice == "3")
            break;

        cout << "- Enter a text to encrypt\n--> ";
        string text, enc, dec;
        cin.ignore(1, '\n');
        getline(cin, text);


        if (choice == "1" || choice == "2") {

            int add;
            // Apply the formula of [(Z - char) + 65] on capitalized letters 
            for (int i = 0; i < text.length(); i++) {
                if (isalpha(text[i])) {
                    add = 'Z' - toupper(text[i]) + 65;
                    enc += (char) add;
                }

                else {  // Any non-alpha characters will stay as they are
                    enc += text[i];
                }

            }
            cout << "--> " << enc << " <--\n";
        }
    }
}

// Main Menu
int main () {
    cout << "========================================\n"
         << "=========== Ciphering System ===========\n"
         << "========================================\n";

    while (true) {
        char choice;
        cout << "\n==== Please Choose The Desired Cipher ====\n"
             << "1) Affine Cipher\n"
             << "2) Route Cipher\n"
             << "3) Vigenere Cipher\n"
             << "4) Atbash Cipher\n"
             << "5) Exit\n"
             << "--> ";
        cin >> choice;
        if (choice == '1') 
            affine();
        else if (choice == '2')
            route();
        else if (choice == '3')
            vigenere();
        else if (choice == '4')
            atbash();
        else if (choice == '5') {
            cout << "- Thanks for using Ciphering/Deciphering System!\n";
            break;
        }
        else {
            cout << "- Invalid choice! Please choose a number between 1 and 5";
        }
    }

    return 0;
}