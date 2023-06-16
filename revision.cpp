#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

void addToFile(vector<string> tokens)
{
    ofstream file("testing.csv", ios::app);

    if (!file)
    {
        cout << "failed to open the file" << endl;
    }

    string line;
    for (const string &token : tokens)
    {
        file << token << ',';
    }

    file.close();

    cout << "Content added to a file successfully" << endl;
}
int main()
{
    string command;
    do
    {
        cout << "Enter any command you want: " << endl;
        getline(cin, command);

        transform(command.begin(), command.end(), command.begin(), ::tolower);

        stringstream ss(command);
        vector<string> tokens;
        string token;
        while (ss >> token)
        {
            tokens.push_back(token);
        }
        cout << tokens.size() << endl;

        if (tokens.size() == 3 && tokens.at(0).compare("rwanda") == 0)
        {
            addToFile(tokens);
        }
        else if (command.compare("exit") == 0)
        {
            cout << "BYE!" << endl;
            break;
        }
        else
        {
            cout << "try again please" << endl;
        }
    } while (command.compare("exit") != 0);
}