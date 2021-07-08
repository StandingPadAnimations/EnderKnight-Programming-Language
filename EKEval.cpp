#include "EKEval.hpp"
using namespace eval;

void Evaluator::Evaluate(const std::vector<std::map<std::vector<std::string>, std::map<std::string, std::string>>> Nodes){
    for(auto const& node : Nodes){
        for(auto const& node_map : node){
            const std::vector<std::string> parents = node_map.first;
            const std::map<std::string, std::string> token = node_map.second;
            std::string ParentForLine;
            for(std::vector<std::string>::const_iterator parent = parents.begin(); parent != parents.end(); ++parent){
                ParentForLine = (*parent);
                if(((*parent) == "NONE") || (parents[0] == "PARENT")){
                    break;
                }
            }
            if((ParentForLine == "NONE") || (parents[0] == "PARENT")){
                for(auto const& token_object : token){
                    if(token_object.first == "echo"){
                        Echo(token_object.second);
                    }
                    else if(token_object.first == "jmp"){
                        Goto(token_object.second, Nodes);
                    }
                    else if(token_object.first == "if"){
                        // If_Process(token_object.second, parents, Nodes);
                    }
                    else{
                    }
                }
            }
        }
    }
}

void Evaluator::Echo(const std::string EchoStatement){
    std::string EchoStatementClean = eval_python.RemoveSpace(EchoStatement);
    bool ArithCheck = (EchoStatementClean.find_first_of("+-*/") != std::string::npos);
    bool QuoteCheck = (EchoStatementClean.find_first_of('"') != std::string::npos);
    if(ArithCheck == true && QuoteCheck == false){
        for(auto const& ar : Arith){
            for(auto const& ar_def : ar){
                if(EchoStatement == ar_def.first){
                    std::cout << ar_def.second << std::endl;
                }
            }
        }
    }
    else{
        for(std::string::size_type pos = 0; pos < 1; ++pos){
            if(EchoStatementClean[pos] != '"'){
                for(auto const& var : EvalVariables){
                    for(auto const& var_def : var){
                        if(EchoStatementClean == var_def.first){
                            std::string VarStatementClean = eval_python.RemoveSpace(var_def.second);
                            VarStatementClean.erase(remove(VarStatementClean.begin(),VarStatementClean.end(),'"'),VarStatementClean.end());
                            std::cout << VarStatementClean << std::endl;
                        }
                    }
                }    
            }
            else{
                EchoStatementClean.erase(remove(EchoStatementClean.begin(),EchoStatementClean.end(),'"'),EchoStatementClean.end());
                EchoStatementClean = eval_python.RemoveSpace(EchoStatementClean);
                std::cout << EchoStatementClean << std::endl;
            }
        }
    }
}

void Evaluator::Goto(const std::string GotoStatement, const std::vector<std::map<std::vector<std::string>, std::map<std::string, std::string>>> Nodes){
    int occurance = 0;
    std::string GotoStatementClean = eval_python.RemoveSpace(GotoStatement);
    for(auto const& edef_node : Nodes){
        for(auto const& edef_map : edef_node){
            std::vector<std::string> edef_parents = edef_map.first;
            std::vector<std::string> edef_parents_unmodified = edef_map.first;
            std::map<std::string, std::string> edef_token = edef_map.second;
            for(std::vector<std::string>::iterator it = edef_parents.begin(); it != edef_parents.end(); ++it){
                (*it).erase(remove((*it).begin(),(*it).end(),':'),(*it).end());
                if(((*it) == GotoStatement) && (occurance == 0)){
                    ++occurance;
                    for(auto const& edef_token_object : edef_token){
                        if(edef_token_object.first == "edef"){
                            std::string edef = edef_token_object.second;
                            std::string EdefClean = eval_python.RemoveSpace(edef);
                            EdefClean.erase(remove(EdefClean.begin(),EdefClean.end(),':'),EdefClean.end());
                            if(EdefClean == GotoStatementClean){
                                for(auto const& node : Nodes){
                                    for(auto const& node_map : node){
                                        std::vector<std::string> parents = node_map.first;
                                        std::map<std::string, std::string> token = node_map.second;
                                        if((parents == edef_parents_unmodified) || (parents[0] == edef) && (token.find("if") != token.end())){
                                            // std::cout << parents[0] << " " << edef << std::endl;
                                            for(auto const& token_object : token){
                                                // std::cout << token_object.first << " " << token_object.second << std::endl;
                                                if(token_object.first == "echo"){
                                                    Echo(token_object.second);
                                                }
                                                else if(token_object.first == "jmp"){
                                                    Goto(token_object.second, Nodes);
                                                }
                                                else if(token_object.first == "if"){
                                                    // std::cout << "THERE SHOULD BE NO IF" << std::endl;
                                                    If_Process(token_object.second, parents, Nodes);
                                                }
                                                else{
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void Evaluator::If_Process(const std::string IfStatement, const std::vector<std::string> Parents, const std::vector<std::map<std::vector<std::string>, std::map<std::string, std::string>>> Nodes){
    eval_python.Split(IfStatement, '=');
    // std::cout << "TOP" << std::endl;
    for(std::vector<std::vector<std::string>>::iterator i = eval_python.splitlines.begin(); i != eval_python.splitlines.end(); ++i){
        (*i)[1].erase(remove((*i)[1].begin(),(*i)[1].end(),':'),(*i)[1].end());
        std::string MeaningClean = eval_python.RemoveSpace((*i)[1]);
        std::string VarClean = eval_python.RemoveSpace((*i)[0]);
        VarClean.erase(remove(VarClean.begin(),VarClean.end(),' '),VarClean.end());
        for(auto const& var : EvalVariables){
            for(auto const& var_def : var){
                std::string VarDefClean = eval_python.RemoveSpace(var_def.second);
                if((VarClean == var_def.first) && (MeaningClean == VarDefClean)){
                    int IfOccur = 0;
                    for(auto const& node : Nodes){
                        for(auto const& node_map : node){
                            const std::vector<std::string> parents = node_map.first;
                            const std::map<std::string, std::string> token = node_map.second;
                            if(parents == Parents){
                                for(auto const& token_object : token){
                                    if(token_object.first == "echo"){
                                        // std::cout << VarClean << " " << var_def.first << "\n" << MeaningClean << " " << VarDefClean << std::endl;
                                        Echo(token_object.second);
                                    }
                                    else if(token_object.first == "jmp"){
                                        // std::cout << VarClean << " " << var_def.first << "\n" << MeaningClean << " " << VarDefClean << std::endl;
                                        Goto(token_object.second, Nodes);
                                    }
                                    if(token_object.first == "if"){
                                        if(IfOccur == 0){
                                            ++IfOccur;
                                            continue;
                                        }
                                        else{
                                            // std::cout << "THERE SHOULD BE NO IF" << std::endl;
                                            If_Process(token_object.second, parents, Nodes);
                                        }
                                    }
                                }
                            }
                            else{
                                // std::cout << 0 << std::endl;
                            }
                        }
                    }
                }
                else{
                    break;
                }
            }
        }
    }
}