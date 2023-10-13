#include <cmath>
#include "expression.hpp"
#include "utilFun.hpp"

#define VAR "x";

using namespace std;

expression::expression(string value)
{
    op = "";
    first = second = nullptr;
    val = value;
}

expression :: expression(expression *fst, expression *sec, string oper) {
    first = fst;
    second = sec;
    op = oper;
    val = (op == "@" ? '[' + fst->val + '(' + sec->val + ')' + ']' : fst->val + op + sec->val);
}

string expression :: differentiate()
{
    if (!first && !second) {
        return getBaseDerivative(val);
    }
    
    if (op == "^") {
        try {
            int power = stoi(second->val);
            if (to_string(power) != second->val) throw invalid_argument("Invalid");
            return second->val + '(' + first->val + '^' + to_string(power - 1) + ')';
        }
        catch(invalid_argument) {
            return "(" + second->val + ")" + first->val + '^' + "((" + second->val + ")" + "-1" + ')';
        }
        catch(out_of_range) {
            return second->val + first->val + '^' + '(' + second->val + "-1" + ')';
        }
    }
    else if (op == "+" || op == "-") {
        if (first->differentiate() == "0" && second->differentiate() == "0") return "0";

        if (first->differentiate() == "0") return second->differentiate();

        if (second->differentiate() == "0") return first->differentiate();

        return first->differentiate() + op + second->differentiate();
    }
    else if (op == "*") {
        if (first->differentiate() == "0" && second->differentiate() == "0") return "0";

        if (first->differentiate() == "0") return '(' + first->getValue() + ")(" + second->differentiate() + ')';

        if (second->differentiate() == "0") return '(' + second->getValue() + ")(" + first->differentiate() + ')';

        return '(' + first->differentiate() + ")(" + second->getValue()  + ")+(" + first->getValue() + ")(" + second->differentiate() + ')';
    }
    else if (op == "@") {
        return '(' + second->differentiate() + ')' + getBaseDerivative(first->val, second->val) /**'[' + first->differentiate() + '(' + second->getValue() + ")]"*/;
    }
    else if (op == "/") {
        if (first->differentiate() == "0" && second->differentiate() == "0") return "0";

        if (first->differentiate() == "0") return "[(-1)(" + first->getValue() + ")(" + second->differentiate() + ')' + "]/[(" + second->getValue() + ")^2]";

        if (second->differentiate() == "0") return "[(" + second->getValue() + ")(" + first->differentiate() + ')' + "]/[(" + second->getValue() + ")^2]";

        return + "[(" + first->differentiate() + ")(" + second->getValue()  + ")-(" + first->getValue() + ")(" + second->differentiate() + ')' + "]/[(" + second->getValue() + ")^2]";
    }
    return "";
}

string expression :: getValue() {
    // if (op == "@") {
    //     return '[' + first->val + '(' + second->val + ')' + ']';
    // }
    return val;
}