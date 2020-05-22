#pragma once
#include <iostream>
using namespace std;
template<typename Data>
class CiclicalList
{
protected:
    struct Element{
        Element* leftElement;
        Element* rightElement;
        Data data;
    };
    Element* currentElement;
    Element* firstElement;
public:
    CiclicalList()
    {
        firstElement = nullptr;
        currentElement = nullptr;
    }
    CiclicalList(Data const data)
    {
        firstElement = new Element();
        firstElement->data = data;
        firstElement->leftElement = firstElement;
        firstElement->rightElement = firstElement;
        currentElement = firstElement;
    }
    CiclicalList(CiclicalList const &ciclicalList)
    {
        if(ciclicalList->firstElement == nullptr)
        {
            firstElement = nullptr;
            currentElement = nullptr;
            return;
        }
        ciclicalList->currentElement=ciclicalList->firstElement;
        firstElement = new Element();
        firstElement->data = ciclicalList->currentElement->data;
        firstElement->leftElement = firstElement;
        firstElement->rightElement = firstElement;
        currentElement = firstElement;
        ciclicalList->currentElement=ciclicalList->currentElement->rightElement;
        while(ciclicalList->currentElement != ciclicalList->FirstElement)
        {
            this->insert(ciclicalList->currentElement->data);
            ciclicalList->currentElement=ciclicalList->currentElement->rightElement;
        }
        currentElement = firstElement;
    }

    unsigned int const size()
    {
        if(firstElement == nullptr)
            return 0;
        unsigned int counter = 0;
        Element *tmpElement = firstElement;
        do
        {
            ++counter;
            tmpElement = tmpElement->rightElement;
        }while(tmpElement != firstElement);
        return counter;
    }
    bool const isEmpty() const
    {
        if(firstElement == nullptr)
            return true;
        return false;
    }
    bool const isContains(Data const data) const
    {
        if(firstElement == nullptr)
            return false;
        Element *tmpElement = firstElement;
        do
        {
            if(tmpElement->data == data)
                return true;
            tmpElement = tmpElement->rightElement;
        }while(tmpElement != firstElement);
        return false;
    }

    Data const getCurrent()
    {
        return currentElement->data;
    }
    bool const shiftRight()
    {
        if(firstElement == nullptr)
            return false;
        currentElement = currentElement->rightElement;
        return true;
    }
    bool const shiftLeft()
    {
        if(firstElement == nullptr)
            return false;
        currentElement = currentElement->leftElement;
        return true;
    }
    void clear()
    {
        currentElement = firstElement;
        while(currentElement != nullptr)
        {
            if(currentElement == currentElement->leftElement)
            {
                delete currentElement;
                firstElement = nullptr;
                currentElement = nullptr;
                return;
            }
            Element *tmpElement = currentElement;
            currentElement->leftElement->rightElement = currentElement->rightElement;
            currentElement->rightElement->leftElement = currentElement->leftElement;
            currentElement = currentElement->rightElement;
            delete tmpElement;
        }
    }

    bool const deleteAtPos(unsigned int position)
    {
        if((firstElement == nullptr)||(position < 1))
            return false;
        Element *tmpCurrentElement = currentElement;
        currentElement = firstElement;
        while(position > 1)
        {
            currentElement = currentElement->rightElement;
            if(currentElement == firstElement)
            {
                currentElement = tmpCurrentElement;
                return false;
            }
            --position;
        }
        if(tmpCurrentElement == currentElement)
            tmpCurrentElement  = tmpCurrentElement->rightElement;
        deleteCur();
        if(tmpCurrentElement != nullptr)
            currentElement = tmpCurrentElement;
        else
            currentElement = firstElement;
        return true;
    }
    bool const deleteCur()
    {
        if(currentElement == nullptr)
            return false;
        if(currentElement == currentElement->rightElement)
        {
            delete currentElement;
            currentElement = nullptr;
            firstElement = nullptr;
            cout<<"\n\t||element deleted||\t";
            return true;
        }
        currentElement->leftElement->rightElement=currentElement->rightElement;
        currentElement->rightElement->leftElement=currentElement->leftElement;
        Element *tmpElement = currentElement;
        if(currentElement == firstElement)
            firstElement = firstElement->rightElement;
        currentElement = currentElement->rightElement;
        delete[] tmpElement;
        tmpElement = nullptr;
        return true;
    }
    bool const delet(Data const data)
    {
        if(firstElement == nullptr)
            return false;
        unsigned counter = 0;
        currentElement = firstElement;
        do
        {
            if(currentElement->data == data)
            {
                deleteCur();
                ++counter;
            }else{
                currentElement = currentElement->rightElement;
            }
        }while((currentElement != firstElement)&&(currentElement != nullptr));
        currentElement = firstElement;
        if(counter == 0)
            return false;
        return true;
    }

    bool const insert(Data const data)
    {
        if(firstElement == nullptr)
        {
            firstElement = new Element();
            currentElement = firstElement;
            currentElement->data = data;
            currentElement->leftElement = firstElement;
            currentElement->rightElement = firstElement;
            return true;
        }
        Element *tmpElement = new Element();
        tmpElement->data = data;
        tmpElement->leftElement = currentElement;
        tmpElement->rightElement = currentElement->rightElement;
        currentElement->rightElement->leftElement = tmpElement;
        currentElement->rightElement = tmpElement;
        currentElement = currentElement->rightElement;
        return true;
    }
    bool const insertAtPos(Data const data, unsigned int position)
    {
        if(position < 1)
            return false;
        if((firstElement == nullptr)&&(position != 1))
            return false;
        if((firstElement == nullptr)&&(position == 1))
        {
            firstElement = new Element();
            firstElement->data = data;
            firstElement->leftElement = firstElement;
            firstElement->rightElement = firstElement;
            currentElement = firstElement;
            return true;
        }
        if(position == 1)
        {
            Element *tmpElement = new Element();
            tmpElement->data = data;
            tmpElement->leftElement = firstElement->leftElement;
            firstElement->leftElement->rightElement = tmpElement;
            tmpElement->rightElement = firstElement;
            firstElement->leftElement = tmpElement;
            firstElement = tmpElement;
            currentElement = tmpElement;
            return true;
        }
        currentElement = firstElement;
        while(position>2)
        {
            --position;
            currentElement = currentElement->rightElement;
            if(currentElement == firstElement)
                return false;
        }
        Element *tmpElement = new Element();
        tmpElement->data = data;
        tmpElement->leftElement = currentElement;
        tmpElement->rightElement = currentElement->rightElement;
        currentElement->rightElement->leftElement = tmpElement;
        currentElement->rightElement = tmpElement;
        currentElement = tmpElement;
        return true;
    }

    void print()
    {
        if(firstElement == nullptr)
        {
            cout<<"No elements!";
            return;
        }
        Element *tmpElement = firstElement;
        do
        {
            std::cout<<tmpElement->data<<"\t";
            tmpElement = tmpElement->rightElement;
        }while(tmpElement != firstElement);
    }
    CiclicalList& operator = (CiclicalList const &ciclicalList)
    {
        if(ciclicalList->firstElement == nullptr)
        {
            firstElement = nullptr;
            currentElement = nullptr;
            return *this;
        }
        ciclicalList->currentElement=ciclicalList->firstElement;
        firstElement = new Element();
        currentElement = firstElement;
        do
        {
            currentElement->data = ciclicalList->currentElement->data;
            currentElement->leftElement = ciclicalList->currentElement->leftElement;
            currentElement->rightElement = ciclicalList->currentElement->rightElement;
            ciclicalList->currentElement = ciclicalList->currentElement->rightElement;
        }while(ciclicalList->currentElement != ciclicalList->FirstElement);
        return *this;
    }

    ~CiclicalList()
    {
        firstElement->leftElement->rightElement = nullptr;
        while(currentElement != nullptr)
        {
            currentElement = firstElement;
            firstElement = firstElement->rightElement;
            delete currentElement;
            currentElement = nullptr;
        }
    }
};
