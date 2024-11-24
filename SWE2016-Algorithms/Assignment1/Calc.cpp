#include <stdio.h>
#include <stack>
#include <vector> // for using StrToNum, and translate char to int
#include <utility> // for using pair to distinguish num and operator

void readfile(char* inputfilename, char* inputstring);
void writefile(char* outputfilename, double& answer);

std::vector<std::pair<int, bool>> NumInStr(char* inputstr); // translate input string to vector<pair> type, 
// int in pair is number(also, ascii of oper) and bool in pair is 'number means oper or number'
std::vector<std::pair<int, bool>> InfixToPostfix(std::vector<std::pair<int, bool>> StrToNum);
// Infix form string (StrToNum) translate to Postfix form
double CAL(std::vector<std::pair<int, bool>> postfix);
// calculate postfix form, result is answer
int prec(int oper); // return precedence of operator

int main(int argc, char** argv)
{
    char* inputstr = new char[101]; // input string
    readfile(argv[1], inputstr); // read input file and store at inputstr
    std::vector<std::pair<int, bool>> POSTFIX = InfixToPostfix(NumInStr(inputstr)); // store POSTFIX expression as vector<pair> type
    
    double answer = CAL(POSTFIX); // calculate postfix ans return answer
    writefile(argv[2], answer); // write answer in output file
    return 0;
}

std::vector<std::pair<int, bool>> NumInStr(char* inputstr)
{
    std::vector<std::pair<int, bool>> StrToNum; // String to Number
    std::pair<int, bool> tmp; // int == num and ascii of operator, bool : true = operator, false = number
    for(int i = 0; inputstr[i] != '\0';) // No i++
    {
        tmp.first = 0, tmp.second = false; // int of pair = 0, bool of pair = false as default
        if(inputstr[i] == '+' || inputstr[i] == '-' || inputstr[i] == '*' 
        || inputstr[i] == '/' || inputstr[i] == '(' || inputstr[i] == ')')
        {
            tmp.first = inputstr[i]; // to translate operator to int
            tmp.second = true; // tmp.first is operator, so tmp.second : boolean value modified as true
            i++; // i++
            StrToNum.push_back(tmp); // push_back pair in StrToNum
            continue;
        }
        while(inputstr[i] >= '0' && inputstr[i] <= '9') // while inputstr[i] in range of number in ascii ('0' <= ? <= '9')
        {
            tmp.first = tmp.first*10 + (inputstr[i] - '0'); // if it's a continuous number, *10 in tmp.first every time.
            i++; // i++ to continue next inputstr element
        }
        StrToNum.push_back(tmp); // make number in pair tmp, push_back(tmp), already tmp.second is false
        // since 'i++' has already been done, there is no 'i++' in for statement
    }
    return StrToNum;
}
int prec(int oper) // the smaller value is higher priority
{
    if(oper == '*' || oper == '/'){ return 1; }
    else if(oper == '+' || oper == '-'){ return 2; }
    else if(oper == '(' || oper == ')'){ return 3; } // handle parentheses separately
	return 0;
}
std::vector<std::pair<int, bool>> InfixToPostfix(std::vector<std::pair<int, bool>> StrToNum)
{
    std::vector<std::pair<int, bool>> postfixStr;
    std::stack<int> oper; // made in integer type stack format for saving directly from pair
    std::pair<int, bool> tmp;
    for(auto it = StrToNum.begin(); it != StrToNum.end(); it++)
    {
        if( !(*it).second ) // if *it.second == false : if *it.first is number
        {
            postfixStr.push_back(*it); // push pair<number, false>
        }
        else
        { // if (*it).first is operator
            if((*it).first == '('){ oper.push((*it).first); } // if operator is left parentheses, push
            else if((*it).first == ')') // if operator is right parentheses
            {
                while(oper.top() != '(') // until meet left parentheses, pop from operator stack and push to postfixStr as tmp pair
                {
                    tmp.first = oper.top(); tmp.second = true;
                    postfixStr.push_back(tmp);   oper.pop();
                }
                oper.pop(); // pop left parentheses
            }
            else // if operator is not parentheses
            {
                while( !oper.empty() && prec(oper.top()) <= prec((*it).first))
                { // operator is not empty and until operator stack's top's priority is higher or equal to iterator's priority
                    tmp.first = oper.top(); tmp.second = true;
                    postfixStr.push_back(tmp); oper.pop(); // pop from operator stack and push to postfixStr as tmp pair
                }
                oper.push((*it).first); // and push present iterator's operator to operator stack
            }
        }
    }
    while(!oper.empty()) // push all remaining operators as tmp pair type
    {
        tmp.first = oper.top(); tmp.second = true;
        postfixStr.push_back(tmp); oper.pop();
    }
    return postfixStr;
}

double CAL(std::vector<std::pair<int, bool>> postfix)
{
    double num1, num2, answer;
    std::stack<double> calstack; // cal stack is only store number, so stack type is double to handle real or floating point number.
    for(auto it = postfix.begin(); it != postfix.end(); it++)
    {
        num1 = 0; num2 = 0;
        if((*it).second) // if present iterator is operator
        {
            num1 = (double)calstack.top(); calstack.pop();
            num2 = (double)calstack.top(); calstack.pop();
            // pop two value of calculator stack
            if((*it).first == '+'){ calstack.push((double)num2 + num1); }
            else if((*it).first == '-'){ calstack.push((double)num2 - num1); }
            else if((*it).first == '*'){ calstack.push((double)num2 * num1); }
            else if((*it).first == '/'){ calstack.push((double)num2 / num1); }
            // and push the calculated value.
        }
        else // if present iterator is number
        {
            calstack.push((*it).first); // push that value directly to calculator stack
        }
    }
    answer = calstack.top(); // answer is the last value left on the stack
    return answer;
}

void readfile(char* inputfilename, char* inputstring)
{
    FILE* fr = fopen(inputfilename, "r"); // open input file
    int tmp; // avoid warning sign of compiler : ignore return value warning
    tmp = fscanf(fr, "%s", inputstring); // store input at inputstring
    fclose(fr); // file close
}

void writefile(char* outputfilename, double& answer)
{
    FILE* fw = fopen(outputfilename, "w"); // open output file
    fprintf(fw, "%.2f", answer); // write answer to output file as .2f
    fclose(fw); // file close
}
