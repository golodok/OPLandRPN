#pragma once
#include "stack.h"
#include "map"
#include "QList"
#include <cctype>
#include "sstream"
using stackTypePtr =  std::shared_ptr<Stack<std::string>>;
class Converter
{

private:
    std::string output;
    std::map<char,std::string> map{{')',"0"},
                                   {'(',"1"},
                                   {'+',"2"},
                                   {'-',"2"},
                                   {'*',"3"},
                                   {'/',"3"},
                                   {'^',"4"},
                                   {'%',"3"},
                                  };


    bool isNumber(const std::string &sElem);
    void strToList(std::string & input, QList<std::string> &QLInput);
    bool isZnack(const std::string &sElem);
    bool getZhack(std::string & iPrioretet,const std::string &sElem);
    void concatStack(Stack<std::string> &stack2, Stack<std::string> &stack1, Stack<std::string> &m_stack, std::string & iPrioritet);
    void puchElemntsToStacks(Stack<std::string> &stack2, Stack<std::string> & stack1,Stack<std::string> & m_stack);
    bool chekEmptyStack(Stack<std::string> & m_stack);

    bool isZnackFromOPL(const std::string &sElem);
    bool isCloseBracketQList(const std::string &sElem);
    void puchToStackByPrioritet(const std::string & sZnack1,const std::string & sElem,Stack<std::string> &m_stack);

public:

    Converter();

    std::string fromRPN(std::string);
    std::string fromOPL(std::string);

};


