#ifndef EKlexer
#define EKlexer

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include "PythonStatements.hpp"
#include "Exceptions.hpp"
using namespace error;

namespace lex{
class Lexer{
    private:
        typedef std::vector<std::map<std::string, std::string>> Tokens;
        typedef std::vector<std::string> KeyWords;
        typedef std::vector<std::map<std::string, std::string>> Variables;
        typedef std::vector<std::map<std::string, std::string>> Arith;

    public:
        Tokens tokens;
        Variables variables;
        Arith arith;
        py::Python lex_python;
        void Tokenize(std::string, int);
        void ProcessVariables(std::string, int);
};
}

#endif 