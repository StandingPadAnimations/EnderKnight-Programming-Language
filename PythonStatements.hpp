#ifndef PythonStatements
#define PythonStatements

#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>


namespace py{
class Python{
    public:
        typedef std::vector<std::vector<std::string>> SplitLines;
        SplitLines splitlines;
        void Split(std::string, char);
        std::string RemoveSpace(std::string);
};
}

#endif