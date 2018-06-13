#include "converter.h"
#include "sstream"



Converter::Converter()
{

}


bool Converter::isNumber(const std::string &sElem)
{
    if(!sElem.empty()){
        if(isdigit(sElem[0]))
            return true;
        else
            return false;
    }
    return false;
}


std::string Converter::fromRPN(std::string input)
{
    output = "";
    Stack<std::string> m_stack;
    Stack<std::string> stack1;
    Stack<std::string> stack2;
    std::string iPrioritet;
    QList<std::string> QLInput;

    strToList(input,QLInput);
    while(!QLInput.empty()){
        std::string sElem = QLInput[0];
        if(isNumber(sElem)){
            m_stack.puch(sElem);
            QLInput.pop_front();
        }
        else if(isZnack(sElem)){
            if(getZhack(iPrioritet,sElem)){
                if(chekEmptyStack(m_stack)){
                    std::string sTmpPtioritet = " ";
                    if(stack2.size()>0)
                        sTmpPtioritet=  stack2.pop();

                    puchElemntsToStacks(stack2,stack1,m_stack);
                    std::string sTmpInput =  sElem;
                    auto it = map.find(sTmpInput[0]);
                    std::string sTmp;
                    if(sTmpPtioritet!=" " && sTmpPtioritet<iPrioritet) {
                        sTmp="(" + stack2.pop()+")"+it->first+"(";
                        stack2.puch(sTmp);
                        sTmp= " ";
                        sTmp+=stack1.pop()+")";
                        stack1.puch(sTmp);
                        sTmp=" ";
                    }
                    else{
                        sTmp=stack2.pop() + sTmpInput[0];
                        stack2.puch(sTmp);
                    }
                    concatStack(stack2,stack1,m_stack,iPrioritet);
                    QLInput.pop_front();
                }
            }
        }
    }
    while (m_stack.size()!=0) {
        output+= m_stack.pop();

    }
    return output;
}



void Converter::strToList(std::string &input, QList<std::string> &QLInput)
{
    std::string sTmp;
    std::stringstream streamTmp;
    streamTmp<<input;
    while(streamTmp >>sTmp){
        if(isdigit(sTmp[0]) || sTmp[0]!= ' ' && map.find(sTmp[0])!=map.end() ){
            QLInput.push_back(sTmp);
        }
    }
}

bool Converter::isZnack(const std::string &sElem)
{
    if(!sElem.empty()){
        if(map.find(sElem[0]) != map.end())
            return true;
        else
            return false;
    }
    else
        return false;
}

bool Converter::getZhack(std::string &iPrioretet, const std::string &sElem)
{
    if(map.find(sElem[0]) != map.end()){
        auto it = map.find(sElem[0]);
        iPrioretet = it->second;
        return true;
    }
    return false;

}


void Converter::concatStack(Stack<std::string> &stack2, Stack<std::string> &stack1, Stack<std::string> &m_stack, std::string &iPrioritet)
{
    std::stringstream sTmp;
    sTmp<<stack2.pop();
    sTmp <<stack1.pop();
    m_stack.puch(sTmp.str());
    stack2.puch(iPrioritet);
}

void Converter::puchElemntsToStacks(Stack<std::string> &stack2, Stack<std::string> &stack1, Stack<std::string> &m_stack)
{

    stack1.puch(m_stack.pop());
    stack2.puch(m_stack.pop());

}

bool Converter::chekEmptyStack(Stack<std::string> &m_stack)
{
    if(m_stack.size()>=2)
        return true;
    else
        return false;
}



std::string Converter::fromOPL(std::string input)
{
    output = "";
    Stack<std::string> m_stack;
    QList<std::string> QLInput;
    strToList(input,QLInput);
    while(!QLInput.empty()){
        std::string sElem = QLInput[0];
        if(!isdigit(sElem[0])){
            if(isZnackFromOPL(sElem)){
                if(!isCloseBracketQList(sElem)){
                    std::string sZnack1;
                    if(m_stack.size()>=1){
                        sZnack1 =m_stack.pop();
                        if (sElem == "(") {
                            m_stack.puch(sZnack1);
                            m_stack.puch(sElem);
                            QLInput.pop_front();

                        }
                        else
                        {
                            puchToStackByPrioritet(sZnack1,sElem,m_stack);
                            QLInput.pop_front();
                        }
                    }
                    else{
                        m_stack.puch(sElem);
                        QLInput.pop_front();
                    }
                }
                else
                {
                    std::string sTmp;
                    do{
                        sTmp = m_stack.pop();
                        if(sTmp != "("){
                            output +=sTmp;
                        }
                        else {
                            QLInput.pop_front();
                            break;
                        }
                    }
                    while (m_stack.size()>0) ;
                }

            }
        }
        else{
            output+=QLInput[0];
            QLInput.pop_front();
        }
    }

    while (m_stack.size()!=0) {
        output+= m_stack.pop();
    }
    return output;
}



bool Converter::isZnackFromOPL(const std::string &sElem)
{
    if(map.find(sElem[0]) != map.end())
        return true;
    else
        return false;
}



bool Converter::isCloseBracketQList(const std::string &sElem)
{
    if (sElem == ")") {
        return true;
    }
    else
        return false;
}

void Converter::puchToStackByPrioritet(const std::string & sZnack1,const std::string & sElem,Stack<std::string> &m_stack)
{
    auto itPrioritet = map.find(sZnack1[0]);
    auto itPrioritet2 = map.find(sElem[0]);
    if(itPrioritet->second <itPrioritet2->second){
        m_stack.puch(sZnack1);
        m_stack.puch(sElem);
    }
    else {
        m_stack.puch(sElem);
        output+=sZnack1;
    }
}





