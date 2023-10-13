#if !defined(UTILFUN)
#define UTILFUN

#include <iostream>
#include "differentiation.hpp"

using namespace std;

bool isVar(string str) {
    int i = 0;
    while (i < str.size()) {
        if (!isalnum(str[i])) return false;
        i++;
    }
    return true;
}

string funcFormatter(string s) {
    size_t pos, end;
    for (int i = 0; i < FUNCTION_COUNT; ++i) {
        pos = s.find(functions[i]);
        end = pos + functions[i].size();
        if (pos != string::npos) {
            if (pos >= 3) {
                bool exists = false;
                for (int j = 0; j < FUNCTION_COUNT; ++j) {
                    size_t found = s.substr(0, pos).find(functions[j]);
                    if (found != string::npos) {
                        i = j - 1;
                        exists = true;
                        break;
                    }
                }
                if (exists) continue;
            }
            string result;
            for (std::size_t j = 0; j < pos; ++j) {
                result.append(s.substr(j, 1));
                if (isdigit(s[j]) && isdigit(s[j+1])) {
                    if (j + 1 == pos) {
                        result.append("*");
                    }
                }
                else result.append("*");
            }
            result +=  s.substr(pos, end - pos);

            if (s.size() == end) return result + '@';

            return result + "@" + funcFormatter(s.substr(pos + functions[i].size()));
        }
        else if (i == FUNCTION_COUNT - 1) {
            string result;
            for (std::size_t j = 0; j < s.size(); ++j) {
                result.append(s.substr(j, 1));
                // j + 1 < s.size() && (isalpha(s[j+1])) ? result.append("*") : "" ;

                j + 1 == s.size() || (isdigit(s[j]) && isdigit(s[j+1])) ? "" : result.append("*");
                // j + 1 != s.size() ? result.append("*") : "";
            }
            return result;
        }
    }
    return "";
}

string getBaseDerivative(string val, string second = "") {
    if (val == "x") return "1";
    else if (val == "cosec") {
        return "(-1)[cot(" + second + ")*cosec(" + second + ")]";
    }
    else if (val == "sec") {
        return "[tan(" + second + ")*sec(" + second + ")]";
    }
    else if (differentiation.count(val) > 0) {
            return '[' + differentiation[val] + '(' + second + ')' + ']';
        }
    else return "0";
}
#endif // UTILFUN
