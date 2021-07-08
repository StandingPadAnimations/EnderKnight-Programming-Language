#include "EKLexer.hpp"
using namespace lex;



void Lexer::Tokenize(std::string Code, int i){
    std::stringstream s(Code);
    std::string temp;
    while (s >> temp) {
        if (temp.compare("echo") == 0) {
                std::regex re("(echo)(.*)");
                Code = std::regex_replace(Code, re, "$2");
                bool has_num = (Code.find_first_of("0123456789") != std::string::npos);
                if(has_num == true){
                        bool has_arith = (Code.find_first_of("+-*/") != std::string::npos);
                        if(has_arith == true){
                                std::map<std::string, std::string> Arithmitic  {{Code, "NULL"}};
                                arith.push_back(Arithmitic);
                        }
                        else{
                                Code = '\"' + Code + '\"';
                        }
                }
                std::map<std::string, std::string> EchoMap {{"echo", Code}};
                tokens.push_back(EchoMap);
                break;
        }
        else if (temp.compare("var") == 0) {
                std::regex re("(var)(.*)");
                Code = std::regex_replace(Code, re, "$2");
                std::map<std::string, std::string> VarMap {{"var", Code}};
                tokens.push_back(VarMap);
                Lexer::ProcessVariables(Code, i);
                break;
        }

        else if (temp.compare("jmp") == 0) {
                std::regex re("(jmp)(.*)");
                Code = std::regex_replace(Code, re, "$2");
                std::map<std::string, std::string> GotoMap {{"jmp", Code}};
                tokens.push_back(GotoMap);
                break;
        }

        else if (temp.compare("math") == 0) {
                std::cout << "math no longer is a function, use echo" << "\n";
                throw std::exception();
        }

        else if (temp.compare("edef") == 0) {
                std::regex re("(edef)(.*)");
                Code = std::regex_replace(Code, re, "$2");
                std::map<std::string, std::string> EdefMap {{"edef", Code}};
                tokens.push_back(EdefMap);
                break;
        }

        else if (temp.compare("stop") == 0) {
                std::regex re("(stop)(.*)");
                Code = std::regex_replace(Code, re, "$2");
                std::map<std::string, std::string> StopMap {{"stop", Code}};
                tokens.push_back(StopMap);
                break;
        }

        else if (temp.compare("if") == 0) {
                std::regex re("(if)(.*)");
                Code = std::regex_replace(Code, re, "$2");
                std::map<std::string, std::string> IfMap {{"if", Code}};
                tokens.push_back(IfMap);
                break;
        }

        else if (temp.compare("/*") == 0) {
                std::regex re("(/*)(.*)");
                Code = std::regex_replace(Code, re, "$2");
                std::map<std::string, std::string> MuteMap {{"mute", Code}};
                tokens.push_back(MuteMap);
                break;
        }

        else{
                std::cout << "Invalid Syntax: " << Code << "\n";
                throw std::exception();
        }
        
    }
}

void Lexer::ProcessVariables(std::string Code, int i){
        lex_python.Split(Code, '=');
        lex_python.splitlines[i][0].erase(remove(lex_python.splitlines[i][0].begin(),lex_python.splitlines[i][0].end(),' '),lex_python.splitlines[i][0].end());
        // std::cout << lex_python.splitlines[i][0] << " " << lex_python.splitlines[i][1] << "\n";
        bool has_alpha = std::regex_match(lex_python.splitlines[i][0], std::regex("^[A-Za-z]+$"));
        if(has_alpha == true){
                std::map<std::string, std::string> VariableMeaning {{lex_python.splitlines[i][0], lex_python.splitlines[i][1]}};
                variables.push_back(VariableMeaning);
                }
        else{
                throw LexerException("Invalid Syntax; Variables must start with a letter between a-z or A-Z: ");
        }
}


