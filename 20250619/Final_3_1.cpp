#include <iostream>
#include <string>
#include <vector>
#include <stdexcept> // for exception handling
#include <cctype>    // for character handling
#include <algorithm>


class Cal_01_IO {
public:
    char logicOperator = '\0';  // control logical diagram
    double inputNum = 0;
    
public:
    Cal_01_IO() = default;  // Constructor
    
    std::string getExpressionStr() {
        std::cout << "Enter your arithmetic expression, Ex: 5+(5-3)*2=   "<< std::endl;
        std::string userInputStr;
        std::getline(std::cin, userInputStr);
        return userInputStr;
    }
    
    std::string reduceArithmeticExpression(std::string arithmeticExpression) {
        if (arithmeticExpression.find('=') == std::string::npos) {
            return "Invalid input: ";
        }
        
        for (size_t i = 0; i < arithmeticExpression.length(); i++) {
            char c = arithmeticExpression[i];
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') {
                try {
                    inputNum = std::stod(arithmeticExpression.substr(0, i));
                    logicOperator = c;
                    arithmeticExpression = arithmeticExpression.substr(i + 1);
                    break;
                } catch (const std::invalid_argument& e) {
                    std::cout << "Invalid input: ";
                    break;
                } catch (const std::out_of_range& e) {
                    std::cout << "Number out of range: ";
                    break;
                }
            }
        }
        
        return arithmeticExpression;
    }
    
    double getNumber() {
        bool inputFinished = false;
        std::string inputNumString;
        
        while (!inputFinished) {
            std::cout << "Enter a number: ";
            std::cin >> inputNumString;
            
            try {
                inputNum = std::stod(inputNumString);
                inputFinished = true;
            } catch (const std::invalid_argument& e) {
                std::cout << "Invalid input: ";
            } catch (const std::out_of_range& e) {
                std::cout << "Number out of range: ";
            }
            
            // Clear any remaining input in the buffer
            std::cin.clear();
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        return inputNum;
    }
    
    char getOperator() {
        bool inputFinished = false;
        std::string operatorStr;
        
        while (!inputFinished) {
            std::cout << "Enter an operator (+, -, *, /, =): ";
            std::cin >> operatorStr;
            
            if (operatorStr.length() > 1) {
                std::cout << "Bad Operator!! Please retype operator again.\n";
                continue;
            }
            
            logicOperator = operatorStr[0];
            if (!(logicOperator == '=' || logicOperator == '+' || 
                  logicOperator == '-' || logicOperator == '*' || 
                  logicOperator == '/')) {
                std::cout << "Error operator!!!\n";
                continue;
            }
            
            inputFinished = true;
        }
        
        return logicOperator;
    }
};



//#include "Cal_01_IO.h" // Assuming you've converted Cal_01_IO to C++

struct Cal_Information {
    bool finalBoolean = false;
    double finalDouble = 0.0;
};

class Cal_02_EngineParts : public Cal_01_IO {
public:
    double sum = 0.0;
    double product = 0.0;
    char activeOperator = '\0';
    bool divisionError = false;
    Cal_Information cal_information;

    void resetGlobalVariables() {
        inputNum = 0; 
        sum = 0; 
        product = 0;
        activeOperator = '\0'; 
        logicOperator = '\0';
    }

public:
    double calculatorKernel(double result, double num, char operatorChar) {
        if (operatorChar == '\0') {
            result = num;
        } else {
            switch (operatorChar) {
                case '+': case '=':
                    result += num; 
                    break;
                case '-':
                    result -= num; 
                    break;
                case '*':
                    result *= num; 
                    break;
                case '/':
                    if (num == 0) {
                        std::cout << "Error: Division by zero" << std::endl;
                        divisionError = true;
                        return 0;
                    }
                    result /= num;
                    break;
                default:
                    std::cout << "Invalid operator" << std::endl;
            }
        }
        return result;
    }

    Cal_Information finalTerminate() {
        cal_information.finalBoolean = true;
        
        switch(activeOperator) {
            case '\0': case '+': case '-':
                sum = product + calculatorKernel(sum, inputNum, activeOperator);
                break;
            case '*':
                sum = sum + calculatorKernel(product, inputNum, activeOperator);
                break;
            case '/':
                if(inputNum == 0) {
                    std::cout << "divisor cannot be 0" << std::endl; 
                    divisionError = true;
                } else {
                    sum = sum + calculatorKernel(product, inputNum, activeOperator);
                }
                break;
            default:
                std::cout << "Operator error !!" << std::endl; 
                cal_information.finalBoolean = false;
        }
        
        if(!divisionError) {
            cal_information.finalDouble = sum;
        } else {
            std::cout << "Arithmetic expression gets wrong operator." << std::endl;
            cal_information.finalBoolean = false;
        }
        
        return cal_information;
    }

    double getSum_lastOperator() {
        switch(activeOperator) {
            case '\0': case '+': case '-':
                sum = product + calculatorKernel(sum, inputNum, activeOperator);
                break;
            case '*':
                sum = sum + calculatorKernel(product, inputNum, activeOperator);
                break;
            case '/':
                if(inputNum == 0) {
                    std::cout << "divisor cannot be 0" << std::endl; 
                    divisionError = true;
                } else {
                    sum = sum + calculatorKernel(product, inputNum, activeOperator);
                }
                break;
        }
        product = 0;
        return sum;
    }

    double getProduct_lastOperator() {
        switch(activeOperator) {
            case '\0': case '+':
                product = inputNum;
                break;
            case '-':
                product = (-1) * inputNum;
                break;
            case '*':
                product = calculatorKernel(product, inputNum, activeOperator);
                break;
            case '/':
                if(inputNum == 0) {
                    std::cout << "divisor cannot be 0" << std::endl; 
                    product = 0; 
                    divisionError = true;
                } else {
                    product = calculatorKernel(product, inputNum, activeOperator);
                }
                break;
        }
        return product;
    }

    double getResultOfArithmeticExpression(std::string arithmeticExpression) {
        resetGlobalVariables();
        
        while(arithmeticExpression.length() > 0) {
            activeOperator = logicOperator;
            arithmeticExpression = reduceArithmeticExpression(arithmeticExpression);
            
            if(logicOperator == '=') {
                finalTerminate();
                break;
            } else if(logicOperator == '+' || logicOperator == '-') {
                sum = getSum_lastOperator();
            } else if(logicOperator == '*' || logicOperator == '/') {
                product = getProduct_lastOperator();
            } else {
                std::cout << "Expression error !!" << std::endl;
                break;
            }
        }
        
        return cal_information.finalDouble;
    }
};



//#include "Cal_02_EngineParts.h" // Assuming previous classes are converted

class Cal_03_Operation : public Cal_02_EngineParts {
public:
    std::string expression = "";

public:
    void printResult() {
        if (!divisionError) {
            std::cout << "Terminated calculation.  sum = " << sum << std::endl;
        }
    }

    double xFlow() {
        double result = 0;
        while (true) {
            activeOperator = logicOperator;
            inputNum = getNumber();
            expression += std::to_string(inputNum) + " ";
            logicOperator = getOperator();
            expression += logicOperator;
            expression += " ";

            if (logicOperator == '=') {
                finalTerminate();
                break;
            }
            else if (logicOperator == '+' || logicOperator == '-') {
                sum = getSum_lastOperator();
            }
            else if (logicOperator == '*' || logicOperator == '/') {
                product = getProduct_lastOperator();
            }
            else {
                std::cout << "Expression error !!" << std::endl;
                break;
            }
            
            std::cout << "expression = " << expression << std::endl;
            std::cout << std::endl;
        }
        return result;
    }

    std::string transferPriorityToArithmeticExpression(const std::string& priortyExpression) {
        std::string arithmeticExpression = "";
        int marks = 0, marksPosition = -1;
        
        if (priortyExpression.empty()) return "";
        if (priortyExpression.find('(') == std::string::npos) return priortyExpression;

        for (size_t i = 0; i < priortyExpression.length(); i++) {
            if (priortyExpression[i] == '(') {
                if (marks == 0) marksPosition = static_cast<int>(i);
                marks++;
            }
            if (priortyExpression[i] == ')') {
                marks--;
                if (marks == 0) {
                    std::string innerExpr = priortyExpression.substr(marksPosition + 1, i - marksPosition - 1);
                    std::string remainingExpr = priortyExpression.substr(i + 1);
                    
                    std::string processedInner;
                    if (innerExpr.find('(') != std::string::npos) {
                        processedInner = std::to_string(
                            getResultOfArithmeticExpression(
                                transferPriorityToArithmeticExpression(innerExpr) + "="
                            )
                        );
                    } else {
                        processedInner = std::to_string(
                            getResultOfArithmeticExpression(innerExpr + "=")
                        );
                    }

                    arithmeticExpression = 
                        priortyExpression.substr(0, marksPosition) +
                        processedInner +
                        transferPriorityToArithmeticExpression(remainingExpr);
                }
            }
        }
        return arithmeticExpression;
    }

    double zFlow() {
        std::string priorityExpression = getExpressionStr();
        std::string arithmeticExpression = transferPriorityToArithmeticExpression(priorityExpression);
        return getResultOfArithmeticExpression(arithmeticExpression + "=");
    }
};

int main(){

    Cal_03_Operation a;
    double x=a.zFlow();
    std::cout<<std::endl;
    std::cout<< "The result is " << x << std::endl;

    return 0;
}