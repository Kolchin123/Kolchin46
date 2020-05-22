#include <iostream>
#include "cyclicallist.h"

using namespace std;

int main()
{
    CiclicalList<int> first;
    first.print();
    cout<<endl;
    first.insert(10);
    first.insert(11);
    first.insert(12);
    first.print();
    cout<<endl<<first.size()<<endl;
    //first.deleteCur();
    first.deleteAtPos(3);
    first.delet(11);
    first.print();
    cout<<endl;
    first.insert(12);
    //first.deleteCur();
    first.print();
    cout<<endl<<first.size()<<endl;
    //first.delet(12);
    first.insertAtPos(3,3);
    first.insertAtPos(3,3);
    first.insertAtPos(3,3);
    first.delet(3);
    first.print();
    cout<<endl;
    cout<<endl<<first.size()<<endl;
    return 0;
}
