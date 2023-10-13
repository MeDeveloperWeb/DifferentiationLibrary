#include <iostream>

using namespace std;

class expression
{
private:
    string op;
    string val;
    expression *first;
    expression *second;
public:
    expression(string value);
    expression(expression *fst, expression *sec, string oper);
    string differentiate();
    string getValue();
};
