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
    void add(const TList);
    TList get (int N);
    TList pop_back();
    int count();
    void clear(){head = nullptr;}


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
    if ((head != nullptr)  ) {
        for (int i = 0; i <=N; ++i)
            if(tmp->next != nullptr){
                tmp = tmp->next;
                return tmp->value;
            }else
            {
                TList value =  tmp->value;
                tmp = tmp->next;
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

