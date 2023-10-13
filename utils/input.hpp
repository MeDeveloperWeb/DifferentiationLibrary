#include <iostream>
#include <cctype>
#include <vector>
#include "postfix.hpp"

using namespace std;

string getInput() {
    string s;
    char c;
    while (cin.get(c))
    {
        if (c == '\n') break;

        s += c;
    }
    return s;   
}

vector<string> getFormattedInput() {
    string input = getInput();
    vector<string> result;

    for (int i = 0; i < input.length(); i++) {
        char c = input[i];

        // Skip blank spaces
		if (c == ' ') continue;

        if (isalnum(c)) {
            string tmp = "";
			while (isalnum(input[i])) {
				tmp += input[i++];
			}
			i--;
			string formFunc = funcFormatter(tmp);
            // result.push_back(formFunc);
            // size_t end = 0;
			// while ((end = formFunc.find('*')) != string::npos) {
			// 	result.push_back(formFunc.substr(0, end));
            //     formFunc = formFunc.substr(end + 1);
			// 	result.push_back("*");
            // }
            // result.push_back(formFunc);
            size_t start = 0;
            for (size_t i = 0; i < formFunc.size(); ++i) {
                char op = formFunc[i];
                if (op == '@' || op == '*') {
                    result.push_back(formFunc.substr(start, i - start));
                    result.push_back(string(1, op));
                    start = i+1;
                }
            }
            if (start < formFunc.size()) result.push_back(formFunc.substr(start));
        }
        else if ((i != 0 && i != input.length() - 1) && (( c == '(' && isVar(result.back()) ) ||  (c == ')' && isalnum(input[i+1])))) {
                result.push_back(string(1, c));
                result.push_back("*");
        }
         else result.push_back(string(1, c));
    }
    return result;
}

vector<string> getFormattedExp() {
    vector<string> input = getFormattedInput();
    return infixToPostfix(input);
}