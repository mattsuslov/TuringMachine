#include "list.h"
#include <iostream>

List::~List() {
    ListNode *ptr = this->begin;
    while (ptr != nullptr) {
        ListNode *tmp = ptr->next;
        delete ptr;
        ptr = tmp;
    }
}

List::List(int count)
{
    if (count == 0) return;
    this->begin = new ListNode;
    this->end = this->begin;
    this->end->data = '_';
    for (int i = 1; i < count; ++i) {
        this->end->next = new ListNode;
        this->end->next->data = '_';
        this->end->next->prev = this->end;
        this->end = this->end->next;
    }
    this->lbound = this->begin;
    this->rbound = this->end;
    this->begin->prev = nullptr;
    this->end->next = nullptr;
}

void  List::ins_after(ListNode * elem) {
    if (elem == nullptr) return;
    ListNode *new_elem = new ListNode;
    new_elem->prev = elem;
    new_elem->next = elem->next;
    new_elem->data = "_";

    elem->next = new_elem;
    if (new_elem->next != nullptr) {
        new_elem->next->prev = new_elem;
    } else {
        this->end = new_elem;
    }
}

void List::swapRight() {
    if (rbound == this->end) {
        ins_after(rbound);
    }
    lbound = lbound->next;
    rbound = rbound->next;
}

void List::ins_before(ListNode * elem) {
    if (elem == nullptr) return;
    ListNode *new_elem = new ListNode;
    new_elem->prev = elem->prev;
    new_elem->next = elem;
    new_elem->data = "_";

    elem->prev = new_elem;
    if (new_elem->prev != nullptr) {
        new_elem->prev->next = new_elem;
    } else {
        this->begin = new_elem;
    }
}


void List::swapLeft() {
    if (lbound == this->begin) {
        ins_before(lbound);
    }
    lbound = lbound->prev;
    rbound = rbound->prev;
}
