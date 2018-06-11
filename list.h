#pragma once
#include <iostream>
#include <string>
#include <memory>

template < typename TypeNode>
struct Node{
    std::shared_ptr<Node<TypeNode>> next;
    TypeNode value;
};


template<typename TList>
class List
{

public:
    std::shared_ptr<Node<TList>> head;
    List():head(nullptr){}
    void add(const TList); //ссылку забыл //связанные методы должны называться похоже. если есть pop_back, должен быть и push_back
    TList get (int N);
    TList pop_back();
    int count();
    void clear(){head = nullptr;} //лучше явно удалить элементы


};

template<typename TList>
void List<TList>::add( TList value)
{
    std::unique_ptr<Node<TList>> tmp(new Node<TList>());
    tmp->value = value;
    tmp->next = head;
    head = move(tmp);
}

template<typename TList>
TList List<TList>::get(int N)
{
    std::shared_ptr<Node<TList>> tmp(head);

//большая вложенность - плохо
//можно раскрутить так:
// if (!head) return nullptr;
//
    if ((head != nullptr)  ) { 
        for (int i = 0; i <=N; ++i) //Если в теле структуры больше одной строки, обязательно используй {}
            if(tmp->next != nullptr){
                tmp = tmp->next;
                return tmp->value;
            }else
            {
                TList value =  tmp->value; //в этой строке нет смысла
                tmp = tmp->next; //в этой строке нет смысла
                return value;
            }
    }
    return nullptr;
}

template<typename TList>
TList List<TList>::pop_back()
{
    std::shared_ptr<Node<TList>> tmp(head);
    if(head!= nullptr){
        head = tmp->next;
        return tmp->value;
    }
}


//Дорогая функция, которую можно заменить на счетчик-member
template<typename T>
int List<T>::count()
{
    int count =0;
    std::shared_ptr<Node<T>> tmp(head);
    if ((head != nullptr)  ) {
        while(tmp != nullptr){
            tmp = tmp->next;
            count++;
        }
    }
    return count;
}

