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
    int sizeOfList;
public:
    std::shared_ptr<Node<TList>> head;
    List():head(nullptr),sizeOfList(0){}
    void puch_back(const  TList &);
    TList get (int N);
    TList pop_back();
    int count(){ return sizeOfList;}
    void clear();


};

template<typename TList>
void List<TList>::clear(){
    std::shared_ptr<Node<TList>> tmp(head);
    while(head!= nullptr){
        head = tmp->next;
        sizeOfList--;
    }
}

template<typename TList>
void List<TList>::puch_back(const TList & value)
{
    std::unique_ptr<Node<TList>> tmp(new Node<TList>());
    tmp->value = value;
    tmp->next = head;
    head = move(tmp);
    sizeOfList++;
}

template<typename TList>
TList List<TList>::get(int N)
{
    std::shared_ptr<Node<TList>> tmp(head);
    if(!head) return nullptr;
    else{
        for (int i = 0; i <=N; ++i){
            tmp = tmp->next;
            return tmp->value;
        }
    }
}

template<typename TList>
TList List<TList>::pop_back()
{
    std::shared_ptr<Node<TList>> tmp(head);
    if(head!= nullptr){
        head = tmp->next;
        --sizeOfList;
        return tmp->value;
    }
    return nullptr;
}



