#ifndef LIST_H
#define LIST_H

#include <QString>

class ListNode {
public:
    ListNode *prev;
    ListNode *next;
    QString data;
};

class List
{
public:
    ListNode *begin, *end;
    ListNode *lbound, *rbound;
    List(int count=0);
    void swapRight();
    void swapLeft();
    void ins_after(ListNode *);
    void ins_before(ListNode *);
    ~List();
};

#endif // LIST_H
