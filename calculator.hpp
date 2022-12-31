//
// Invisparent
// Wang Chenyi, Henan University
// 20221229 2308
//

#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#define CALCULATOR_PRECISION double
#define CALCULATOR_STOD_PRECISION std::stod
#define CALCULATOR_LEGAL_NUMBER_SET {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'}
//#define CALCULATOR_LEGAL_SYNTAX_SET {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '+', '-', '*', '/', '(', ')'}

#include <iostream>
#include <string>
#include <iterator>
#include <unordered_set>

class Calculator {
public:
    CALCULATOR_PRECISION operator()(const std::string &inString) {
        return operator()(inString.cbegin(), inString.cend());
    }

    CALCULATOR_PRECISION operator()
            (std::string::const_iterator iterA, std::string::const_iterator iterB, int reverseOperator = 0) {
        /**
         *  About reverseOperator:
         *  reverseOperator == 0 : Do not reverse any operator
         *  reverseOperator == 1 : Reverse + and -
         *  reverseOperator == 2 : Reverse * and /
         */
        if (iterA == iterB)
            return 0;
        if (*iterA == '(' && *(iterB - 1) == ')') {
            ++iterA;
            --iterB;
            reverseOperator = 0;
        }
        int minOperatorPriority = 3;
        // +-: 1, */: 2 ;
        int bracketCounter = 0;
        std::string::const_iterator minOperatorPosIter = iterB;
        for (std::string::const_iterator traverseIter = iterA; traverseIter != iterB; ++traverseIter) {
            if (*traverseIter == '(') {
                ++bracketCounter;
                while (bracketCounter) {
                    ++traverseIter;
                    if (*traverseIter == '(')
                        ++bracketCounter;
                    else if (*traverseIter == ')')
                        --bracketCounter;
                }
                ++traverseIter;
                if (traverseIter == iterB)
                    break;
            }
            if (legalNumberElement.find(*traverseIter) == legalNumberElement.end()) {
                if ((*traverseIter == '+' || *traverseIter == '-') && minOperatorPriority > 1) {
                    minOperatorPriority = 1;
                    minOperatorPosIter = traverseIter;
                } else if ((*traverseIter == '*' || *traverseIter == '/') && minOperatorPriority > 2) {
                    minOperatorPriority = 2;
                    minOperatorPosIter = traverseIter;
                }
            }
        }
        if (minOperatorPosIter == iterB)
            return CALCULATOR_STOD_PRECISION(std::string(iterA, iterB));
        else {
            switch (reverseOperator) {
                case 0:
                    switch (*minOperatorPosIter) {
                        case '+':
                            return operator()(iterA, minOperatorPosIter) + operator()(minOperatorPosIter + 1, iterB);
                        case '-':
                            return operator()(iterA, minOperatorPosIter) - operator()(minOperatorPosIter + 1, iterB, 1);
                        case '*':
                            return operator()(iterA, minOperatorPosIter) * operator()(minOperatorPosIter + 1, iterB);
                        case '/':
                            return operator()(iterA, minOperatorPosIter) / operator()(minOperatorPosIter + 1, iterB, 2);
                    }
                case 1:
                    switch (*minOperatorPosIter) {
                        case '+':
                            return operator()(iterA, minOperatorPosIter) - operator()(minOperatorPosIter + 1, iterB);
                        case '-':
                            return operator()(iterA, minOperatorPosIter) + operator()(minOperatorPosIter + 1, iterB, 1);
                        case '*':
                            return operator()(iterA, minOperatorPosIter) * operator()(minOperatorPosIter + 1, iterB);
                        case '/':
                            return operator()(iterA, minOperatorPosIter) / operator()(minOperatorPosIter + 1, iterB, 2);
                    }
                case 2:
                    switch (*minOperatorPosIter) {
                        case '+':
                            return operator()(iterA, minOperatorPosIter) + operator()(minOperatorPosIter + 1, iterB);
                        case '-':
                            return operator()(iterA, minOperatorPosIter) - operator()(minOperatorPosIter + 1, iterB, 1);
                        case '*':
                            return operator()(iterA, minOperatorPosIter) / operator()(minOperatorPosIter + 1, iterB);
                        case '/':
                            return operator()(iterA, minOperatorPosIter) * operator()(minOperatorPosIter + 1, iterB, 2);
                    }
                default:
                    break;
            }
        }
    }

private:
    static const std::unordered_set<char> legalNumberElement, legalSyntaxElement, legalOperatorElement;
};

const std::unordered_set<char> Calculator::legalNumberElement = CALCULATOR_LEGAL_NUMBER_SET;
//const std::unordered_set<char> Calculator::legalSyntaxElement = CALCULATOR_LEGAL_SYNTAX_SET;

#endif // CALCULATOR_HPP
