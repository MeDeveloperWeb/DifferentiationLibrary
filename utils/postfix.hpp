// C++ code to convert infix expression to postfix
#include <iostream>
#include <stack>
#include <cctype>
#include <vector>
#include "utilFun.hpp"

using namespace std;

// Function to return precedence of operators
int prec(char c) {
	if (c == '@') {
		return 4;
	}
	else if (c == '^')
		return 3;
	else if (c == '/' || c == '*')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}


// The main function to convert infix expression
// to postfix expression
vector<string> infixToPostfix(vector<string> s) {

	stack<string> st;
	vector<string> result;

	for (auto i : s) {
		char c = i[0];
		// If the scanned character is
		// an operand, add it to output string.
		if (isalnum(c)) {
			// string tmp = "";
			// while (isalnum(s[i])) {
			// 	tmp += s[i++];
			// }
			// i--;
			// string formFunc = funcFormatter(tmp);
			// //if found do something
			// //TODO
			// // size_t found = tmp.find("cos");
			// // result.push_back(string(1, c));
			// // result.push_back(formFunc);
			// size_t start = 0, end = 0;
			// while (end != string::npos) {
			// 	end = formFunc.find('*');
			// 	result.push_back(formFunc.substr(start, end-start));
			// 	start = end;
			// 	result.push_back("*");
			// }
			// result.push_back(formFunc.substr(start));
			result.push_back(i);
		}

		// If the scanned character is an
		// ‘(‘, push it to the stack.
		else if (c == '(')
			st.push("(");

		// If the scanned character is an ‘)’,
		// pop and add to output string from the stack
		// until an ‘(‘ is encountered.
		else if (c == ')') {
			while (st.top() != "(") {
				result.push_back(st.top());
				st.pop();
			}
			st.pop();
		}

		// If an operator is scanned
		else {
			//originally <= changed to < to maintain functions
			while (!st.empty() && c != st.top()[0] && prec(c) <= prec(st.top()[0])) {
				result.push_back(st.top());
				st.pop();
			}
			st.push(i);
		}
	}

	// Pop all the remaining elements from the stack
	while (!st.empty()) {
		result.push_back(st.top());
		st.pop();
	}

	return result;
}
