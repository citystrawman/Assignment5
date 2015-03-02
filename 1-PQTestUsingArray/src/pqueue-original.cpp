/*
 * File: pqueue.cpp (array version)
 * --------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a dynamic array as
 * the underlying representation.  Most of the code is already in place.
 * The only thing that is missing is the implementation of the actual
 * commands.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

PriorityQueue::PriorityQueue() {
   // TODO: Fill in the necessary code
    capacity = INITIAL_CAPACITY;
    array = new ValuePriorityPair [capacity];
    count = 0;
}

PriorityQueue::~PriorityQueue() {
   // TODO: Fill in the necessary code
    delete[] array;
}

int PriorityQueue::size() {
   return count;  // TODO: Replace this line with the necessary code
}

bool PriorityQueue::isEmpty() {
   return count == 0;  // TODO: Replace this line with the necessary code
}

void PriorityQueue::clear() {
   // TODO: Fill in the necessary code
    count = 0;
}

void PriorityQueue::enqueue(string value, double priority) {
   // TODO: Fill in the necessary code
    if (count == capacity) expandCapacity();
    if (count == 0) {
        array[0].value = value;
        array[0].priority = priority;
        count ++;
        cout << "Position 0, value" << array[0].value << " priority "<< array[0].priority << endl;
        return;
    }
    //if (priority == NULL) priority = 1;

    if (count > 0) {
        if (array[0].priority < priority) {
            for (int j = count; j > 0; j--) {
                array[j] = array[j - 1];
            }
            array[0].value = value;
            array[0].priority = priority;
            cout << "case 1; position " << "0, " << "value " << array[0].value << " priority " << array[0].priority << endl;
        } else if (array[count - 1].priority > priority) {
            array[count].value = value;
            array[count].priority = priority;
            cout << "case 2; position " << count << ", value " << array[count].value << " priority " << array[count].priority << endl;
        } else {
            for (int i = 0; i < count; i++){
                if (array[i].priority >= priority && array[i + 1].priority <= priority) {
                    cout << "this element is inserted at position " << i + 1 << endl;
                    for (int j = count; j > i + 1; j--) {
                        array[j] = array[j - 1];
                    }
                    array[i + 1].value = value;
                    array[i + 1].priority = priority;
                    cout << "case 3; position " << i + 1 << ", value " << array[i + 1].value << " priority " << array[i + 1].priority << endl;
                    count ++;
                    return;
                }
            }
        }
        count ++;
    }
}

string PriorityQueue::dequeue() {
    // TODO: Replace this line with the necessary code
   if (isEmpty()) error ("The queue is empty.");
   return array[--count].value;
}

string PriorityQueue::peek() {
    // TODO: Replace this line with the necessary code
    if (isEmpty()) error ("The queue is empty.");
   return array[count - 1].value;
}

double PriorityQueue::peekPriority() {
    // TODO: Replace this line with the necessary code
    if (isEmpty()) error ("The queue is empty.");
   return array[count - 1].priority;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow the standard
 * paradigm described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      if (array != NULL) delete[] array;
      deepCopy(src);
   }
   return *this;
}
