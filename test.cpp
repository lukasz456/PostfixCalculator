#include <iostream>
#include "string.h"
#include "intList.h"
#include "stringList.h"

using namespace std;

using Token = stos::string;
using Tokens = stringList::list; //vector<Token>

void getTokens(const char* infix, Tokens& result)
{
    do {
        const char* start = infix;

        while (*infix && *infix != ' ') {
            ++infix;
        }

        size_t size = (infix - start);
        if (size) {
            result.push_back(stos::string(start, size));
        }

    } while (*infix++ != '\0');
}

stos::string toString(const Tokens& tokens)
{
    stos::string result;

    const stringList::node* nextNode = tokens.getHead();
    while (nextNode) {
        if (result.size()) {
            result += " ";
        }
        result += nextNode->data;
        nextNode = tokens.getNext(nextNode);
    }

    // for (int i = 0; i < tokens.size(); ++i) {
    //     result += tokens.at(i);
    //     if (i < tokens.size() - 1) {
    //         result += " ";
    //     }
    // }

    // const stringList::node* nextNode = tokens.getHead();
    // while (nextNode) {
    //     const Token& token = nextNode->data;
    //     ...
    //     nextNode = nextNode->next;
    // }

    return result;
}

bool isNumber(const Token& token)
{
    if (token.size() == 0) { //!token.size()
        return false;
    }

    for (int i = 0; i < token.size(); ++i) { //auto& ch : token
        if (!isdigit(token[i])) {
            return false;
        }
    }

    return true;
}

constexpr const char* MUL = "*";	// multiplication
constexpr const char* DIV = "/";    // division
constexpr const char* ADD = "+";    // addition
constexpr const char* SUB = "-";	// subtraction
constexpr const char* OPEN = "(";	// parentheses open
constexpr const char* CLOSE = ")";	// parentheses close
constexpr const char* IF = "IF";	// if condition, F(a, b, c) -if a>0 return b, otherwise c
constexpr const char* N = "N";	    // unary negation
constexpr const char* MIN = "MIN";	// minimum, MIN ( a1 , a2 , ... )
constexpr const char* MAX = "MAX";	// maximum, MAX ( a1 , a2 , ... )
constexpr const char* COMMA = ",";  // Comma


bool isOperator(const Token& token)
{
    if (token == MUL || token == DIV || token == ADD || token == SUB || token == IF || token == N || token == MIN || token == MAX) {
        return true;
    }

    return false;
}

bool isPriorityGreaterOrEqual(const Token& left, const Token& right)
{
    static const Tokens tokens{ OPEN, CLOSE, MAX, MIN, IF, N, MUL, DIV, ADD , SUB };
    constexpr int size = 10; // Number of tokens

    int posLeft = 0;
    int posRight = 0;

    int i(0);
    const stringList::node* nextNode = tokens.getHead();
    while (nextNode) {

        if (nextNode->data == left) {
            posLeft = i;
        }
        if (nextNode->data == right) {
            posRight = i;
        }
        nextNode = tokens.getNext(nextNode);
        ++i;
    }

    //for (int i = 0; i < tokens.size(); ++i) {
    //    if (tokens.at(i) == left) {
    //        posLeft = i;
    //    }
    //    if (tokens.at(i) == right) {
    //        posRight = i;
    //    }
    //}

    bool table[size][size] = {
        // OPEN, CLOSE, MAX, MIN, IF, N, MUL, DIV, ADD, SUB
        {true, true, true, true, true, true, true, true, true, true},        // OPEN
        {true, true, true, true, true, true, true, true, true, true},        // CLOSE
        {false, false, true, true, true, true, true, true, true, true},      // MAX
        {false, false, true, true, true, true, true, true, true, true},      // MIN
        {false, false, false, false, true, true, true, true, true, true},    // IF
        {false, false, false, false, false, false, true, true, true, true},  // N
        {false, false, false, false, false, false, true, true, true, true},  // MUL
        {false, false, false, false, false, false, true, true, true, true},  // DIV
        {false, false, false, false, false, false, false, false, true, true},// ADD
        {false, false, false, false, false, false, false, false, true, true} // SUB
    };

    return table[posLeft][posRight];

}


void convertToPostfix(const Tokens& infixTokens, Tokens& newResult)
{
    Tokens stack;
    Tokens result;

    const stringList::node* nextNode = infixTokens.getHead();
    while (nextNode) {
        const Token& token = nextNode->data;
        if (isNumber(token))
        {
            result.push_back(token);
        }
        else if (isOperator(token))
        {
            while (!stack.empty() && isOperator(stack.back()) && isPriorityGreaterOrEqual(stack.back(), token))
            {
                result.push_back(stack.back());
                stack.pop_back();
            }

            stack.push_back(token);
        }
        else if (token == OPEN)
        {
            stack.push_back(token);
        }
        else if (token == CLOSE)
        {
            while (stack.back() != OPEN)
            {
                result.push_back(stack.back());
                stack.pop_back();
            }
            stack.pop_back();
        }
        else if (token == COMMA)
        {
            while (!stack.empty() && stack.back() != OPEN && stack.back() != COMMA)
            {
                result.push_back(stack.back());
                stack.pop_back();
            }
            stack.push_back(token);
        }
        nextNode = infixTokens.getNext(nextNode);
    }

    while (!stack.empty())
    {
        result.push_back(stack.back());
        stack.pop_back();
    }

    {
        int numberOfOperands = 0;
        const stringList::node* nextNode = result.getHead();
        while (nextNode)
        {
            const Token& token = nextNode->data;
            if (token == COMMA)
            {
                ++numberOfOperands;
            }
            else if (token == MIN)
            {
                newResult.push_back(token + stos::to_string(numberOfOperands + 1));
                numberOfOperands = 0;
            }
            else if (token == MAX)
            {
                newResult.push_back(token + stos::to_string(numberOfOperands + 1));
                numberOfOperands = 0;
            }
            else if (token == IF)
            {
                newResult.push_back(token);
                numberOfOperands = 0;
            }
            else if (token != COMMA)
            {
                newResult.push_back(token);
            }
            nextNode = result.getNext(nextNode);
        }
    }
}


void printStackContent(const intList::list& stack)
{
    const intList::node* prevNode = stack.getTail();

    while (prevNode) {
        cout << prevNode->data << " ";
        prevNode = stack.getPrev(prevNode);
    }

    //if (!stack.empty())
    //{
    //    for (int i = (int)stack.size() - 1; i >= 0; i--)
    //    {
    //        cout << stack.at((size_t)i) << " ";
    //    }

    //}
    cout << endl;
}

int numOfElements(const char* element)
{
    int counterOfElements = 0;
    while (*element != '\0')
    {
        ++counterOfElements;
        ++element;
    }
    return counterOfElements;
}

Token calculatePostfix(const Tokens& postfixTokens) //zmiana printowania zeby oprocz liczb na ktorych sa wykonywane dzialanie printowaly sie tez pozostale liczby ze stosu
{
    intList::list stack;  //vector<int> stack
    const stringList::node* nextNode = postfixTokens.getHead();
    while (nextNode)
    {
        const Token& token = nextNode->data;

        if (isNumber(token))
        {
            stack.push_back(stoi(token)); //stoi(token)
        }
        else
        {
            int a = stack.back();
            stack.pop_back();

            if (token == ADD)
            {
                int b = stack.back();
                stack.pop_back();

                cout << ADD << " " << a << " " << b << " ";
                printStackContent(stack);
                stack.push_back(b + a);
            }
            else if (token == SUB)
            {
                int b = stack.back();
                stack.pop_back();

                cout << SUB << " " << a << " " << b << " ";
                printStackContent(stack);

                stack.push_back(b - a);
            }
            else if (token == MUL)
            {
                int b = stack.back();
                stack.pop_back();

                cout << MUL << " " << a << " " << b << " ";
                printStackContent(stack);

                stack.push_back(b * a);
            }
            else if (token == DIV)
            {
                int b = stack.back();
                stack.pop_back();

                cout << DIV << " " << a << " " << b << " ";
                printStackContent(stack);

                if (a == 0)
                {
                    return Token("ERROR");
                }
                stack.push_back(b / a);

            }
            else if (token == N)
            {
                cout << N << " " << a << " ";
                printStackContent(stack);

                stack.push_back(-a);
            }
            else if (token == IF)
            {
                int b = stack.back();
                stack.pop_back();
                int c = stack.back();
                stack.pop_back();

                cout << IF << " " << a << " " << b << " " << c << " ";
                printStackContent(stack);

                stack.push_back((c > 0 ? b : a));
            }

            else if (token.substr(0, 3) == MIN)
            {
                // Get the number of operands
                stos::string nrOfOperandsStr = token.substr(3, token.size() - 3); //3, token.size() - strlen(MIN)
                int noOfOperands = stoi(nrOfOperandsStr); //stoi(nrOfOperandsStr)

                // Find the min value
                int minValue = a;
                intList::list stackMIN;
                stackMIN.push_back(a);

                while (--noOfOperands) {
                    int next = stack.back();
                    stackMIN.push_back(next);
                    stack.pop_back();
                    if (next < minValue) {
                        minValue = next;
                    }
                }
                // At first we print all elements of min, which are stored in the int vector stackMIN then all elements from the main stack
                //
                cout << token << " ";
                const intList::node* nextNode = stackMIN.getHead();
                while (nextNode) {
                    cout << nextNode->data << " ";
                    nextNode = stackMIN.getNext(nextNode);
                }

                //for (int i = 0; i < stackMIN.size(); ++i)
                //{
                //    cout << stackMIN.at(i) << " ";
                //}
                printStackContent(stack);
                stack.push_back(minValue);
            }

            else if (token.substr(0, 3) == MAX)
            {
                // Get the number of operands
                stos::string nrOfOperandsStr = token.substr(3, token.size() - 3); //3, token.size() - strlen(MIN)
                int noOfOperands = stoi(nrOfOperandsStr); //stoi(nrOfOperandsStr)

                // Find the max value
                int maxValue = a;
                intList::list stackMAX;
                stackMAX.push_back(a);
                while (--noOfOperands) {
                    int next = stack.back();
                    stackMAX.push_back(next);
                    stack.pop_back();
                    if (next > maxValue) {
                        maxValue = next;
                    }
                }
                // At first we print all elements of max, which are stored in the int vector stackMAX then all elements from the main stack
                //
                cout << token << " ";

                const intList::node* nextNode = stackMAX.getHead();
                while (nextNode) {
                    cout << nextNode->data << " ";
                    nextNode = stackMAX.getNext(nextNode);
                }

                //for (int i = 0; i < stackMAX.size(); ++i)
                //{
                //    cout << stackMAX.at(i) << " ";
                //}
                printStackContent(stack);
                stack.push_back(maxValue);
            }

        }
        nextNode = postfixTokens.getNext(nextNode);
    }
    return stos::to_string(stack.back());
}

void readExpressionsFromInput(Tokens& expressions)
{
    stos::string nrOfExpressionsStr;
    stos::string expression;

    getline(cin, nrOfExpressionsStr);

    int nrOfExpressions = stoi(nrOfExpressionsStr); //stoi(nrOfExpressionsStr)
    for (int i = 0; i < nrOfExpressions; ++i)
    {
        getline(cin, expression);
        expressions.push_back(expression);

    }
}

int main()
{
    stringList::list expressions;
    readExpressionsFromInput(expressions);

    const stringList::node* nextNode = expressions.getHead();
    while (nextNode) {
        Tokens infixTokens;
        getTokens(nextNode->data.c_str(), infixTokens);

        Tokens postfixTokens;
        convertToPostfix(infixTokens, postfixTokens);
        cout << toString(postfixTokens) << endl;

        Token result = calculatePostfix(postfixTokens);
        cout << result << endl << endl;

        nextNode = expressions.getNext(nextNode);
    }

    //for (int i = 0; i < expressions.size(); ++i)
    //{
    //    Tokens infixTokens = getTokens(expressions.at(i).c_str());
    //    Tokens postfixTokens = convertToPostfix(infixTokens);
    //    cout << toString(postfixTokens) << endl;
    //    Token result = calculatePostfix(postfixTokens);
    //    cout << result << endl << endl;
    //}
    //intList::testList();

    return 0;
}
