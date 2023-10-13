// C++ code to convert infix expression to postfix
#include <iostream>
#include "utils/input.hpp"
#include "utils/expression.cpp"
#include "utils/utilFun.hpp"
using namespace std;
 
string differentiate(vector<string> exp) {
	stack<expression*> st;
    // Scan all characters one by one
    for (auto i = exp.begin(); i < exp.end(); ++i) {
        // If the scanned character is an operand
        // (number or alphabet here), push it to the stack.
        if (isVar(*i)) {
            expression* temp = new expression(*i);
            st.push(temp);
        }

        // If the scanned character is an operator,
        // pop two elements from stack apply the operator
        else {
            expression* val1 = st.top();
            st.pop();
            expression* val2 = st.top();
            st.pop();
            expression* tmp = new expression(val2, val1, *i);
            st.push(tmp); 
        }
    }
    return st.top()->differentiate();
}
// Driver code
int main()
{
	cout << "Enter the equation:" << endl;
	vector<string> input = getFormattedExp();
	// Function call
	// for (auto i : input)
    // {
    //     cout << i;
    // }
    // cout << "\nbye\n";
    
    cout << differentiate(input) << endl;

    // Hold window
    cin.get();
	return 0;
}