#include <iostream>
#include <fstream>
#include <string>
#include <EKLexer.hpp>
#include <PythonStatements.hpp>
#include <EKParser.hpp>
#include <EKEval.hpp>


int main(int argc, char *argv[]) {
    lex::Lexer eklexer;
    int var = 0;
    // std::vector<std::map<std::string, std::string>> DebugTokens {{{"lol", "lmao"}}, {{"vscode", "vs"}}};

    try{
        if(argc == 2){
            std::ifstream EnderScript(argv[1]);
            std::cout << "EnderKnight 1:" << std::endl;
            for(std::string CodeLine; std::getline(EnderScript, CodeLine);){
                eklexer.Tokenize(CodeLine, var);
                var = ++var;
            }
            

            par::Parser ekparser(eklexer.arith);
            std::vector<std::map<std::string, std::string>> DebugEkLexerTokens = eklexer.tokens;
            ekparser.Parse(eklexer.tokens);

            eval::Evaluator ekeval(eklexer.variables, ekparser.Arith);
            ekeval.Evaluate(ekparser.nodes);
        }
        else{
            std::cout << "EnderKnight 1 Shell:" << std::endl;
            std::cout << ">>>:" << std::flush;
            std::string CodeLine;
            std::getline(std::cin, CodeLine);
            eklexer.Tokenize(CodeLine, var);
            var = ++var;
            
            par::Parser ekparser(eklexer.arith);
            std::vector<std::map<std::string, std::string>> DebugEkLexerTokens = eklexer.tokens;
            ekparser.Parse(eklexer.tokens);

            eval::Evaluator ekeval(eklexer.variables, ekparser.Arith);
            ekeval.Evaluate(ekparser.nodes);
        }
    }

    catch(const std::exception& exp)  
    {             
        std::cout << exp.what() << std::endl;                
        return EXIT_FAILURE;
    }
    return 0;
}