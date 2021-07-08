#include "EKParser.hpp"
using namespace par;

void Parser::Parse(std::vector<std::map<std::string, std::string>> TokenVector){
    int indent;
    for(auto const& i : TokenVector){
        for(auto const& j : i){
            for(std::string::size_type pos = 0; pos < j.second.size(); ++pos){
                if(j.second[pos] != ' '){
                    int Spaces = pos - 1;
                    if(Spaces % 4 == 0 && Spaces/4 > 0){
                        indent = static_cast<int>(Spaces/4);
                        IndentParser(j.second, j.first, indent);
                    }
                    else{
                        ParseLine(j.first, j.second);
                    }
                    break;
                }
            }
        }
    }
    for(auto& it : Arith){
        for(auto& jt : it){
            std::string MATH = ekparsemath.Parse(jt.first);
            it.at(jt.first) = MATH;
        }
    }
}

void Parser::IndentParser(std::string TokenSecond, std::string TokenFirst, int IndentCount){
    for (std::vector<std::vector<std::string>>::reverse_iterator i = parents.rbegin(); i != parents.rend(); ++i){ 
        for(std::vector<std::string>::iterator it = (*i).begin(); it != (*i).end(); ++it){
            // std::cout << "LIST " << (*it) << "\n";
        }
        if((*i).size() > IndentCount){
            // std::cout << "IGNORE " << TokenSecond << " " << (*i).size() << "\n";
            continue;
        } 

        else{
            if(TokenFirst == "if" || TokenFirst == "edef"){
                std::vector<std::string> ParentToken;
                std::vector<std::string> Parents;

                for(std::vector<std::string>::iterator it = (*i).begin(); it != (*i).end(); ++it){
                    if(it != (*i).end()){
                        Parents.push_back(*it);
                        // std::cout << "ADDING PARENTS TO NODE PARENTS " << Parents.size() << "\n";
                    }
                    else{
                        break;
                    }
                }
                
                for(std::vector<std::string>::iterator pos_parent = (*i).begin(); pos_parent != (*i).end(); ++pos_parent){
                    ParentToken.push_back(*pos_parent);
                    // std::cout << "ADDING PARENTS TO PARENTS TOKEN " << ParentToken.size() << "\n";
                }
                
                
                Parents.push_back(TokenSecond);
                
                // std::cout << "POSSIBLE PARENTS " << parents.size() << "\n";

                ParentToken.push_back(TokenSecond);
                parents.push_back(ParentToken);

                std::map<std::string, std::string> Token {{TokenFirst, TokenSecond}};
                std::map<std::vector<std::string>, std::map<std::string, std::string>> Node {{Parents, Token}};
                nodes.push_back(Node);
                // std::cout << "PARENT " << TokenSecond << " " << Parents.size() << "\n";
            }

            else{
                std::vector<std::string> Parents;

                for(std::vector<std::string>::iterator it = (*i).begin(); it != (*i).end(); ++it){
                    if(it != (*i).end()){
                        Parents.push_back(*it);
                        // std::cout << "ADDING PARENTS TO NODE PARENTS " << Parents.size() << "\n";
                    }
                    else{
                        break;
                    }
                }
                std::map<std::string, std::string> Token {{TokenFirst, TokenSecond}};
                std::map<std::vector<std::string>, std::map<std::string, std::string>> Node {{Parents, Token}};
                nodes.push_back(Node);
                // std::cout << "NOT A PARENT " << TokenSecond << " " << Parents.size() << "\n";
            }
            break;
        }
    } 
}

void Parser::ParseLine(std::string TokenFirst, std::string TokenSecond){
    if(TokenFirst == "if" || TokenFirst == "edef"){
        std::vector<std::string> Parents {TokenSecond};
        std::map<std::string, std::string> Token {{TokenFirst, TokenSecond}};
        std::map<std::vector<std::string>, std::map<std::string, std::string>> Node {{Parents, Token}};
        nodes.push_back(Node);
        std::vector<std::string> ParentToken {TokenSecond};
        parents.push_back(ParentToken);
        // std::cout << "PARENT " << TokenSecond << " " << Parents.size() << "\n";
    }
    else{
        std::vector<std::string> Parents {"NONE"};
        std::map<std::string, std::string> Token {{TokenFirst, TokenSecond}};
        std::map<std::vector<std::string>, std::map<std::string, std::string>> Node {{Parents, Token}};
        nodes.push_back(Node);
        // std::cout << "NOT A PARENT " << TokenSecond << " " << Parents.size() << "\n";
    }
}