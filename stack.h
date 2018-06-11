#pragma once
#include "list.h"



template< typename SType>
class Stack
{
    List<SType> LCurrent;
    int sizeOfStack; //Это надо реализовать через список
public:
    Stack():sizeOfStack(0){ }
    void puch(const SType);
    SType pop();
    int size(){return sizeOfStack;}
};



template<typename SType>
void Stack<SType>::puch(const SType value)
{
        LCurrent.add(value);
        sizeOfStack++; //Это надо реализовать через список
}

template<typename SType>
SType Stack<SType>::pop()
{
    sizeOfStack--; //Это надо реализовать через список
    return  LCurrent.pop_back();

}
