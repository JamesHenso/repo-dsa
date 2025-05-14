#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

//_____________________________________________
// Function so handle small problem
unordered_map<char, int> __precen ={ // operator precendence
    {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}
};

int precendence(char op){
    return __precen.count(op) ? __precen[op] : 0;
}

int compare(const string &a, const string &b) // compare 2 strings
{
    if (a.length() < b.length()) return -1;
    if (a.length() > b.length()) return 1;
    for (int i = 0; i < a.length(); i++){
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
    }
    return 0;
}

string __del_zero(const string &num){
    int pos = 0;
    bool negative = false;
    string s = num;
    if (!s.empty() && s[0] == '-') {
        negative = true;
        pos = 1;
    }
    while(pos < s.length() - 1 && s[pos] == '0') pos++;
    string res = s.substr(pos);
    if (res == "" || res == "0") return "0";
    return negative ? "-" + res : res;
}
string convert_postfix(const string &algo_str){
    stack<char> operators;
    string postfix;
    string number;
    bool expecting_operand = true;

    for (char ch : algo_str){
        if (isspace(ch)) continue;

        if (isdigit(ch)){
            number += ch;
            expecting_operand = false;
        }
        else {
            if (!number.empty()){
                postfix += number + ' ';
                number.clear();
            }
            if (ch == '-' && expecting_operand){
                postfix += "0 ";
            }

            if (ch == '('){
                operators.push(ch);
                expecting_operand = true;
            }
            else if (ch == ')'){
                while (!operators.empty() && operators.top() != '('){
                    postfix += operators.top();
                    postfix += ' ';
                    operators.pop();
                }
                if (operators.empty()) return "Error";
                operators.pop();
                expecting_operand = false;
            }
            else if (__precen.count(ch)){
                while (!operators.empty() && operators.top() != '('
                       && precendence(operators.top()) >= precendence(ch)){
                    postfix += operators.top();
                    postfix += ' ';
                    operators.pop();
                }
                operators.push(ch);
                expecting_operand = true;
            }
            else {
                return "Error"
                       + string(1, ch) + "'";
            }
        }
    }

    if (!number.empty()){
        postfix += number + ' ';
    }
    while (!operators.empty()){
        if (operators.top() == '(') 
            return "Error";
        postfix += operators.top();
        postfix += ' ';
        operators.pop();
    }

    return postfix;
}


//__________________________________________________________
// Typedef for calculte function

typedef string(*__calculate) (const string &, const string &);
string sum_BigInt(const string &num1, const string &num2);
string sub_BigInt(const string &num1, const string &num2);
string mul_BigInt(const string &num1, const string &num2);
string div_BigInt(const string &num1, const string &num2);

unordered_map<string, __calculate> operations = {
    {"+", sum_BigInt},
    {"-", sub_BigInt},
    {"*", mul_BigInt},
    {"/", div_BigInt}
};

//__________________________________________________________
// Code function for main 

string sum_BigInt(const string &num1, const string &num2){
    if(num1[0] == '-' && num2[0] == '-') return "-" + sum_BigInt(num1.substr(1), num2.substr(1));
    else if(num1[0] == '-') return sub_BigInt(num2, num1.substr(1));
    else if(num2[0] == '-') return sub_BigInt(num1, num2.substr(1));

    string result;
    int carry = 0;
    int len1 = num1.length() - 1, len2 = num2.length() - 1;

    while(len1 >= 0 || len2 >= 0 || carry){
        int digit1 = (len1 >= 0) ? num1[len1--] - '0' : 0;
        int digit2 = (len2 >= 0) ? num2[len2--] - '0' : 0;

        int sum = digit1 + digit2 + carry;

        carry = sum / 10;
        result += (sum % 10) + '0';
    }

    reverse(result.begin(), result.end());
    return result;

}

string sub_BigInt(const string &num1, const string &num2){
    if(num1 == num2) return "0";
    else if(num1[0] == '-' && num2[0] == '-') return sub_BigInt(num2.substr(1), num1.substr(1));
    else if(num1[0] == '-') return "-" + sum_BigInt(num1.substr(1), num2);
    else if(num2[0] == '-') return sum_BigInt(num1, num2.substr(1));

    bool negative = false;
    string large = num1, small = num2;

    if(num1.length() < num2.length() || (num1.length() == num2.length() && num1 < num2)){
        swap(large, small); 
        negative = true;
    }

    string result;
    int borrow = 0;
    int len1 = large.length() - 1, len2 = small.length() - 1;

    while(len1 >= 0 || len2 >= 0){
        int digit1 = (len1 >= 0) ? large[len1--] - '0' : 0;
        int digit2 = (len2 >= 0) ? small[len2--] - '0' : 0;

        int sub = digit1 - digit2 - borrow;

        if(sub < 0){
            sub += 10;
            borrow = 1;
        } else borrow = 0;

        result += (sub + '0');
    }

    while (result.length() > 1 && result.back() == '0') result.pop_back();

    reverse(result.begin(), result.end());

    return (negative) ? "-" + result : result;
}

string mul_BigInt(const string &num1, const string &num2)
{
    bool isNegative = (num1[0] == '-') ^ (num2[0] == '-');
    string absNum1 = (num1[0] == '-') ? num1.substr(1) : num1;
    string absNum2 = (num2[0] == '-') ? num2.substr(1) : num2;

    absNum1 = __del_zero(absNum1);
    absNum2 = __del_zero(absNum2);

    if (absNum1 == "0" || absNum2 == "0") return "0";

    if (absNum1.length() == 1 && absNum2.length() == 1){
        int result = (absNum1[0] - '0') * (absNum2[0] - '0');
        return isNegative ? "-" + to_string(result) : to_string(result);
    }

    int n = max(absNum1.length(), absNum2.length());
    if (n % 2 != 0) n++;

    while (absNum1.length() < n) absNum1 = "0" + absNum1;
    while (absNum2.length() < n) absNum2 = "0" + absNum2;

    int half = n / 2;
    string a = absNum1.substr(0, half);
    string b = absNum1.substr(half);
    string c = absNum2.substr(0, half); 
    string d = absNum2.substr(half);

    string ac = mul_BigInt(a, c);
    string bd = mul_BigInt(b, d);
    string ab_cd = mul_BigInt(sum_BigInt(a, b), sum_BigInt(c, d));
    string ad_plus_bc = sub_BigInt(ab_cd, sum_BigInt(ac, bd));

    for (int i = 0; i < 2 * (n - half); i++) ac += "0";
    for (int i = 0; i < (n - half); i++) ad_plus_bc += "0";

    string result = sum_BigInt(sum_BigInt(ac, ad_plus_bc), bd);
    result = __del_zero(result);

    return isNegative ? "-" + result : result;
}

string div_BigInt(const string &num1, const string &num2)
{
    if (num2 == "0") {
        return "Error";
    }

    bool isNegative = (num1[0] == '-') ^ (num2[0] == '-');
    string absNum1 = (num1[0] == '-') ? num1.substr(1) : num1;
    string absNum2 = (num2[0] == '-') ? num2.substr(1) : num2;

    absNum1 = __del_zero(absNum1);
    absNum2 = __del_zero(absNum2);

    if (absNum2 == "0") return "Error";
    if (absNum1 == "0") return "0";
    if (compare(absNum1, absNum2) < 0) return "0";

    string result = "";
    string curr = "";

    for (char digit : absNum1){
        curr += digit;

        while (curr.length() > 1 && curr[0] == '0') curr.erase(0, 1);

        int count = 0;

        while (compare(curr, absNum2) >= 0){
            curr = sub_BigInt(curr, absNum2);
            count++;
        }

        result += (count + '0');
    }

    result = __del_zero(result);
    if (isNegative && result != "0") result = "-" + result;
    return result;
}

//__________________________________________________________
// Function to progrees file and result
bool __getFile(const string &filename, vector<string> &lines)
{
    ifstream file(filename);
    if (!file.is_open()){
        cerr << "Error: Can't open file" << endl;
        return false;
    }

    string line;
    while (getline(file, line)){
        if (!line.empty()) lines.push_back(line);
    }

    file.close();
    return true;
}

//______________________________________________________________
// Function to calculate
string calculate(const string &algo){
    stack<string> op_algo;
    string postfix = convert_postfix(algo);
    istringstream ss(postfix);
    string token;

    while(ss >> token){
        if(isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) op_algo.push(token);
        else if(operations.count(token)){
            if(op_algo.size() < 2) return "Error";
            string num2 = op_algo.top(); op_algo.pop();
            string num1 = op_algo.top(); op_algo.pop();
            if(token == "/" && __del_zero(num2) == "0") return "Error";
            string result = operations[token](num1, num2);
            op_algo.push(result);
        }
        else return "Error";

    }

    if(op_algo.size() != 1) return "Error";

    return op_algo.top();

}

int main(int argc, char *argv[])
{
    if(argc != 3){
        cerr << "The comand line is wrong" << endl;
        cerr << "tests.txt output_IDStudent.txt" << endl;
        return 0;
    }

    string input = argv[1];
    string output = argv[2];
    ofstream file_op(output);

    vector<string> expression;

    if(!__getFile(input, expression)) return 0;

    for(const string &str : expression){
        string res = calculate(str);
        file_op << res << endl;
    }

    file_op.close();
    return 0;
}
