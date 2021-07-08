#include "PythonStatements.hpp"
using namespace py;

void Python::Split(std::string String, char Seperator){
    std::stringstream ss(String);
    std::string line;
    std::vector<std::string> SeparatedSentance;
    while(getline(ss, line, Seperator)) {
        SeparatedSentance.push_back(line);
    }
    splitlines.push_back(SeparatedSentance);
}

std::string Python::RemoveSpace(std::string StringWithSpace){
    auto space = StringWithSpace.find_first_not_of(' ');
    auto StringClean = StringWithSpace.substr(space != std::string::npos ? space : 0);
    return StringClean;
}
