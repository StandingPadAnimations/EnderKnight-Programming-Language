#ifndef EkParser
#define EkParser

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include "Exceptions.hpp"
#include "EKMathParsing.hpp"
using namespace error;

namespace par{
    class Parser{
        private:
            typedef std::vector<std::map<std::vector<std::string>, std::map<std::string, std::string>>> Nodes;
            typedef std::vector<std::vector<std::string>> PossibleParents;
            

        public:
            Nodes nodes;
            PossibleParents parents;
            math::MathParse ekparsemath;
            std::vector<std::map<std::string, std::string>> Arith;
            Parser(std::vector<std::map<std::string, std::string>> Arith) : Arith(Arith){}
            void Parse(std::vector<std::map<std::string, std::string>>);
            void IndentParser(std::string, std::string, int);
            void ParseLine(std::string, std::string);

    };
}

#endif 