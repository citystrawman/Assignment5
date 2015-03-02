/*
 * File: pqueue.cpp (linked-list version)
 * --------------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a linked list as the
 * underlying representation.  Only the copy constructor and assignment
 * operator are included.  Your job is to include definitions for the
 * other exported methods.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

// TODO: Add your method definitions here

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow a standard paradigm,
 * as described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      clear();
      deepCopy(src);
   }
   return *this;
}

PriorityQueue::PriorityQueue() {
   // TODO: Fill in the necessary code
    head = NULL;
    count = 0;
}

PriorityQueue::~PriorityQueue() {
   // TODO: Fill in the necessary code
    clear();
}

int PriorityQueue::size() {
   return count;  // TODO: Replace this line with the necessary code
}

bool PriorityQueue::isEmpty() {
   return count == 0;  // TODO: Replace this line with the necessary code
}

void PriorityQueue::clear() {
   while (count > 0) {
       dequeue();
   }
}

/*
 * Function: enqueue
 * ---------------------
 * This funciton enqueues the value and priority into linked list.
 *

                                          A                           B

            +----------+            +-----------+               +----------+
     head   |     +---------------->|  value    |          +--->|  value   |
            |          |            |           |          +    |          |
            +----------+            +-----------+          |    +----------+
                                    | Priority  |          |    | priority |
                                    |           |          |    |          |
                                    +-----------+          |    +----------+
                                    |           |          |    |          |
                                    |     +----------------+    |   NULL   |
                                    +-----------+               +----------+
 */

void PriorityQueue::enqueue(string value, double priority) {
    ValuePriorityPair* vp = new ValuePriorityPair;
    vp->value = value;
    vp->priority = priority;
    vp->link = NULL;
    if (head == NULL) {
        head = vp;
    } else {
        for (ValuePriorityPair* p = head; p != NULL; p = p->link) {
            ValuePriorityPair* nextP = p->link;
            if (p == head && vp->priority < head->priority) {
                vp->link = head;
                head = vp;
                count ++;
                return;
            }
            if (nextP == NULL) {
                p->link = vp;
                count ++;
                return;
            }
            if (vp->priority >= p->priority && vp->priority <= nextP->priority) {
                vp->link = nextP;
                p->link = vp;
                count ++;
                return;
            }
        }
    }
    count ++;
}

string PriorityQueue::dequeue() {
    // TODO: Replace this line with the necessary code
    string result = peek();
    ValuePriorityPair* next = head->link;
    delete head;
    head = next;
    count --;
    return result;
}

string PriorityQueue::peek() {
    // TODO: Replace this line with the necessary code
    if (isEmpty()) {
        error ("The queue is empty.");
    }
    return head->value;
}

double PriorityQueue::peekPriority() {
    // TODO: Replace this line with the necessary code
    if (isEmpty()) {
        error ("The queue is empty.");
    }
    return head->priority;
}

