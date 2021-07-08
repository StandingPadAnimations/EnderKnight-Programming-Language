#include "EKMathParsing.hpp"
using namespace math;

void AddToStack(char OperatorType, std::stack<char> &Stack, std::deque<std::string> &Output){
    int OperatorTypePreference = 0;
    int PreviousOperatorPreference = 0;
    char PreviousOperator;
    std::string Convert;
    switch(OperatorType){
        case '+':
            OperatorTypePreference = 1;
            break;
        case '-':
            OperatorTypePreference = 1;
            break;
        case '*':
            OperatorTypePreference = 2;
            break;
        case '/':
            OperatorTypePreference = 2;
            break;
        case '(':
            Stack.push(OperatorType);
            return;
        case ')':
            PreviousOperatorPreference = 0;
            for(int i = 0; i < Stack.size(); ++i){
                if(Stack.top() != '('){
                    Convert = Stack.top();
                    Output.push_back(Convert);
                    Stack.pop();
                }
                else{
                    Stack.pop();
                    break;
                }
            }
    }

    if(Stack.size() != 0){
        switch(Stack.top()){
            case '+':
                PreviousOperatorPreference = 1;
                PreviousOperator = '+';
                break;
            case '-':
                PreviousOperatorPreference = 1;
                PreviousOperator = '-';
                break;
            case '*':
                PreviousOperatorPreference = 2;
                PreviousOperator = '*';
                break;
            case '/':
                PreviousOperatorPreference = 2;
                PreviousOperator = '/';
                break;
        }
        if(OperatorTypePreference > PreviousOperatorPreference && OperatorTypePreference != 0){
            Stack.push(OperatorType);
            return;
        }
        if(OperatorTypePreference == PreviousOperatorPreference || OperatorTypePreference < PreviousOperatorPreference && OperatorTypePreference != 0){
            Convert = PreviousOperator;
            Output.push_back(Convert);
            Stack.pop();
            Stack.push(OperatorType);
            return;
        }
        
    }
    else{
        if(OperatorType != '('){
            Stack.push(OperatorType);
            return;
        }
    }
}

void Solve(float Num1, float Num2, std::string Op, std::stack<std::string> &Numbers){
    std::string Answer;
    if(Op == "+"){
        Answer = std::to_string(Num1+Num2);
    }
            
    else if(Op == "-"){
        Answer = std::to_string(Num1-Num2);
    }

    else if(Op == "*"){
        Answer = std::to_string(Num1*Num2);
    }
            
    else if(Op == "/"){
        Answer = std::to_string(Num1/Num2);
    }
    Numbers.push(Answer);
    return;
}

std::string MathParse::Parse(std::string math){
    std::string Convert;
    std::string Prior = "NONE";
    std::stack<char> Stack;
    std::deque<std::string> Output;
    std::stack<std::string> Numbers;
    std::string FinalOutput;
    math.erase(std::remove_if(begin(math), end(math),[l = std::locale{}](auto ch) {return std::isspace(ch, l); }),end(math));
    for(int op; op < math.size(); ++op){
        if((math[op] >= '0') && (math[op] <= '9') || (math[op] == '.')){
            bool PriorIsDigit = (Prior.find_first_not_of("0123456789.") == std::string::npos);
            Convert = math[op];
            if(PriorIsDigit == true){
                Convert = Prior + Convert;
                Output.pop_back();
            }
            Output.push_back(Convert);
            Prior = math[op];
        }
        else{
            bool PriorIsDigit = (Prior.find_first_not_of("0123456789.") == std::string::npos);
            if((PriorIsDigit == true) && (math[op] == '(')){
                AddToStack('*', Stack, Output);
            }
            AddToStack(math[op], Stack, Output);
            Prior = math[op];
        }
    }
    do{
        if(Stack.top() != ')'){
            Convert = Stack.top();
            Output.push_back(Convert);
        }
        Stack.pop();
    }while(Stack.size() != 0);

    do{
        bool has_only_digits = (Output.front().find_first_not_of("0123456789.") == std::string::npos);
        if((has_only_digits == true)){
            Convert = Output.front();
            Numbers.push(Convert);
        }
        else{
            float Num2 = std::stof(Numbers.top());
            Numbers.pop();
            float Num1 = std::stof(Numbers.top());
            Numbers.pop();
            Solve(Num1, Num2, Output.front(), Numbers);
        }
        Output.pop_front();
    }while(Output.size() != 0);
    
    FinalOutput = Numbers.top();
    while((FinalOutput.find(".")!=std::string::npos) && (FinalOutput.substr(FinalOutput.length() - 1, 1) == "0") || (FinalOutput.substr(FinalOutput.length() - 1, 1) == ".")){
        FinalOutput.pop_back();
    }
    return FinalOutput;
}
