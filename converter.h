#pragma once
#include "stack.h"
#include "map"
#include "QList"
#include <cctype>
using stackTypePtr =  std::shared_ptr<Stack<std::string>>;
class Converter
{

    //Лучше явно указывать области видимости

    std::string output; // Зачем нужен этот член, если почти всегда используется локально?
    std::map<char,std::string> map{{')',"0"},
                                   {'(',"1"},
                                   {'+',"2"},
                                   {'-',"2"},
                                   {'*',"3"},
                                   {'/',"3"},
                                   {'^',"4"},
                                   {'%',"3"},
                                  }; // Почему приоритеты строковые? о_О

    //Функции всё еще непонятные
    bool isNumberFromRPN(QList<std::string> &QLInput);
    void preparationInput(std::string & input, QList<std::string> &QLInput);
    bool isZnackFromRPN(QList<std::string> &QLInput);
    bool determinationOfZhackFromRPN(std::string & iPrioretet,QList<std::string> &QLInput);
    void concatStackFromRPN(Stack<std::string> &stack2, Stack<std::string> &stack1, Stack<std::string> &m_stack, std::string & iPrioritet);

    //And в имени функции - явный признак того, что ее надо разбить
    bool checkDataStackAndPuchStacksFromRPN(Stack<std::string> &stack2, Stack<std::string> & stack1,Stack<std::string> & m_stack);
    bool isZnackFromOPL(QList<std::string> &QLInput);
    void workWhistOperFromOPL(QList<std::string> &QLInput, Stack<std::string> & m_stack);
    bool isCloseBracketQList(QList<std::string> &QLInput);

    void printOutput(Stack<std::string>& m_stack , std::string & input); //Лишняя функция. Абстракции не должны работать с выводом.

public:

    Converter();
    void fromRPN(std::string); // должны позвращать преобразованную строку
    void fromOPL(std::string); // ---





};


