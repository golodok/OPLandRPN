#pragma once
#include "list.h"



template< typename SType>
class Stack
{
    List<SType> LCurrent;
public:

    void puch(const SType);
    SType pop();
    int size();
};



template<typename SType>
void Stack<SType>::puch(const SType value)
{
        LCurrent.puch_back(value);
}

template<typename SType>
SType Stack<SType>::pop()
{
    return  LCurrent.pop_back();

}

template<typename SType>
int Stack<SType>::size()
{
      return  LCurrent.count();
}
