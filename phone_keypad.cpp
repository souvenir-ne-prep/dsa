#include <iostream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

string findMapping(string str)
{
    static const unordered_map<string, string> mapping = {
        {"00", "+"},
        {"000", "!"},
        {"0000", ":"},
        {"00000", "<"},
        {"000000", ">"},
        {"0000000", "\""},
        {"00000000", "|"},
        {"000000000", "{"},
        {"0000000000", "}"},
        {"00000000000", ";"},
        {"000000000000", "\\"},
        {"0000000000000", ","},
        {"00000000000000", "/"},
        {"000000000000000", "?"},
        {"11", "a"},
        {"111", "b"},
        {"1111", "c"},
        {"22", "d"},
        {"222", "e"},
        {"2222", "f"},
        {"33", "g"},
        {"333", "h"},
        {"3333", "i"},
        {"44", "j"},
        {"444", "k"},
        {"4444", "l"},
        {"55", "m"},
        {"555", "n"},
        {"5555", "o"},
        {"66", "p"},
        {"666", "q"},
        {"6666", "r"},
        {"77", "s"},
        {"777", "t"},
        {"7777", "u"},
        {"88", "v"},
        {"888", "w"},
        {"8888", "x"},
        {"99", "y"},
        {"999", "z"},
        {"9999", ","},
        {"01", " "}};
    string res = "";
    auto it = mapping.find(str);
    if (str.size() < 2)
        res += str;
    else if (it != mapping.end())
        res += it->second;
    return res;
}

int main()
{
    string text;

    cout << "Welcome to this program\nPlease enter your sequence:";
    getline(cin, text);

    transform(text.begin(), text.end(), text.begin(), ::tolower);

    istringstream iss(text);

    cout << "The output is:\n\n";

    vector<string> words;
    string word;
    while (iss >> word)
    {
        words.push_back(word);
    }
    for (const auto &str : words)
    {
        cout << findMapping(str);
    }
    cout << "\n";

    return 0;
}
