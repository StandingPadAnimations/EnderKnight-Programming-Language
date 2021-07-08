#ifndef EkEval
#define EkEval

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "PythonStatements.hpp"
#include "Exceptions.hpp"
using namespace error;

namespace eval{
class Evaluator{
    private:

    public:
        std::vector<std::map<std::string, std::string>> EvalVariables;
        std::vector<std::map<std::string, std::string>> Arith;
        Evaluator(std::vector<std::map<std::string, std::string>> EvalVariables, std::vector<std::map<std::string, std::string>> Arith) : EvalVariables(EvalVariables), Arith(Arith){}

        py::Python eval_python;
        void Evaluate(std::vector<std::map<std::vector<std::string>, std::map<std::string, std::string>>>);
        void Echo(std::string);
        void Goto(std::string, std::vector<std::map<std::vector<std::string>, std::map<std::string, std::string>>>);
        void If_Process(std::string, std::vector<std::string>, std::vector<std::map<std::vector<std::string>, std::map<std::string, std::string>>>);
        void Math();
        void Stop();

};
}

#endif 