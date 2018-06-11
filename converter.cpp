#include "converter.h"


// !!! Почти нигде нет контроля на выход за границы массивов/списков

Converter::Converter()
{

}

// Функция проверки не должна завязываться на позицию элемента в контейнере
// Нужны обстракции. 
// Если функция Is... она должна принимать только один элемент для проверки.
bool Converter::isNumberFromRPN(QList<std::string> &QLInput)
{
    std::string sTmp = QLInput[0]; // А что если список пустой?
    // Ретурны в одной строке с условиями - не очень хороший стиль.
    if(isdigit(sTmp[0])) return true; // А что,е сли строка пустая?
    else return false;
}

// Алгоритм плохо читается
void Converter::fromRPN(std::string input)
{
    output = "";
    Stack<std::string> m_stack;
    Stack<std::string> stack1;
    Stack<std::string> stack2;
    std::string iPrioritet;
    QList<std::string> QLInput;

    // Как из названия функции понять, что она делает?
    // Старайся давать говорящие имена. Например, даже банальное strToList понятнее
    preparationInput(input,QLInput); 
    while(!QLInput.empty()){

        // Реалилизация по факту ничем не отличается от предыдущей. 
        // Итерация по списку всё равно внутри вложенных функций. 
        // Это очень опасно и нечитабельно.
        if(isNumberFromRPN(QLInput)){
            std::string sTmp =  QLInput[0];
            if(sTmp.size()>1){
                m_stack.puch(sTmp);
                QLInput.pop_front();
            }
            else{
                m_stack.puch(sTmp);
                QLInput.pop_front();

            }
        }
        else if(isZnackFromRPN(QLInput)){
            if(determinationOfZhackFromRPN(iPrioritet,QLInput)){
                std::string sTmpPtioritet = " ";
                if(stack2.size()>1)
                    sTmpPtioritet=  stack2.pop();

                if(checkDataStackAndPuchStacksFromRPN(stack2,stack1,m_stack)){
                    std::string sTmpInput =  QLInput[0];
                    auto it = map.find(sTmpInput[0]);
                    std::string sTmp;


                    if(sTmpPtioritet!=" " && sTmpPtioritet<iPrioritet) { 
                        sTmp="(" + stack2.pop()+")"+it->first+"(";       
                        stack2.puch(sTmp);          
                        sTmp= " ";
                    }
                    else{
                        sTmp=stack2.pop() + sTmpInput[0];
                        stack2.puch(sTmp);
                    }
                    if(sTmpPtioritet!=" " && sTmpPtioritet<iPrioritet){ // Явное дублирование кода выше. Будут ошибки
                        sTmp+=stack1.pop()+")";
                        stack1.puch(sTmp);
                        sTmp=" ";
                    }
                    concatStackFromRPN(stack2,stack1,m_stack,iPrioritet);
                    QLInput.pop_front();
                }
            }
        }
    }
    printOutput(m_stack,input); // Это здесь лишнее. Нарушение абстракции.
}



void Converter::preparationInput(std::string &input, QList<std::string> &QLInput)
{
    // Есть готовые функции для разбиения строк на токены
    std::string sTmp;
    for(int i =0;i!=input.size();i++){
        if(isdigit(input.at(i)) || input.at(i)!= ' ' || map.find(input.at(i))!=map.end() ){
            if(isdigit(input[i+1]) && isdigit(input.at(i))){

                while(isdigit(input.at(i))){
                    sTmp+= input.at(i);
                    i++;
                }
                QLInput.push_back(sTmp);
                i--;
                continue;
            }
            sTmp= input.at(i);

            QLInput.push_back(sTmp);
            sTmp= "";
        }
    }
}

bool Converter::isZnackFromRPN(QList<std::string> &QLInput) //константность
{
    // Проверки на выход за пределы
    std::string sTmp =QLInput[0];
    if(map.find(sTmp[0]) != map.end())
        return true;
    else return false;
}

bool Converter::determinationOfZhackFromRPN(std::string &iPrioretet, QList<std::string> &QLInput)
{
    std::string sTmp =QLInput[0];
    if(map.find(sTmp[0]) != map.end()){
        auto it = map.find(sTmp[0]);
        iPrioretet = it->second;
        return true;
    }

    // CRASH.Где возвращаемое значение?
}

void Converter::printOutput(Stack<std::string> &m_stack, std::string &input)
{
    while (m_stack.size()!=0) {
        output+= m_stack.pop();
    }
    std::cout<<input<<'\n';
    std::cout<<output<<'\n';
}

void Converter::concatStackFromRPN(Stack<std::string> &stack2, Stack<std::string> &stack1, Stack<std::string> &m_stack, std::string &iPrioritet)
{
    std::string sTmp;
    std::string sStack2 =stack2.pop();
    sTmp = sStack2 + stack1.pop(); // Для подобных целей лучше подходит stringstream
    m_stack.puch(sTmp);
    stack2.puch(sStack2);
    stack2.puch(iPrioritet);
}

bool Converter::checkDataStackAndPuchStacksFromRPN(Stack<std::string> &stack2, Stack<std::string> &stack1, Stack<std::string> &m_stack)
{
    std::string sTmp;

    if(m_stack.size()>=2){
        stack1.puch(m_stack.pop());
        stack2.puch(m_stack.pop());
        return true;
    }
    else return false;

}



void Converter::fromOPL(std::string input)
{
    output = "";
    Stack<std::string> m_stack;
    QList<std::string> QLInput;
    preparationInput(input,QLInput);
    while(!QLInput.empty()){
        if(!isdigit(QLInput[0][0])){
            if(isZnackFromOPL(QLInput)){
                if(!isCloseBracketQList(QLInput)){
                    workWhistOperFromOPL(QLInput,m_stack);
                }
                else{
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
    printOutput(m_stack,input);
}



bool Converter::isZnackFromOPL(QList<std::string> &QLInput)
{
    std::string sTmp =QLInput[0];
    if(map.find(sTmp[0]) != map.end())
        return true;
    else return false;
}

// функции не должны иметь названия виду workWith. Чаще всего это свидетельствует о том, что функция спроектирована неверно.
// Совершенно непонятно, что она делает
void Converter::workWhistOperFromOPL(QList<std::string> &QLInput, Stack<std::string> &m_stack)
{
    std::string sZnack2 = QLInput[0];
    if (map.find(sZnack2[0]) != map.end()) {
        std::string sZnack1;
        if(m_stack.size()>=1){
            sZnack1 =m_stack.pop();
            if (sZnack2 == "(") {
                m_stack.puch(sZnack1);
                m_stack.puch(sZnack2);
                QLInput.pop_front();

            }
            else{
                auto itPrioritet = map.find(sZnack1[0]);
                auto itPrioritet2 = map.find(sZnack2[0]);
                if(itPrioritet->second <itPrioritet2->second){
                    m_stack.puch(sZnack1);
                    m_stack.puch(sZnack2);
                    QLInput.pop_front();
                }
                else {
                    m_stack.puch(sZnack2);
                    output+=sZnack1;
                    QLInput.pop_front();
                }
            }
        }
        else{
            m_stack.puch(sZnack2);
            QLInput.pop_front();
        }

    }
}


bool Converter::isCloseBracketQList(QList<std::string> &QLInput)
{
    std::string sTmp= QLInput[0];
    if (sTmp == ")") {
        return true;
    }
    else return false;
}





