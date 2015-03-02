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


/*
 * Function: enqueue
 * ---------------------
 * This funciton enqueues the value and priority into an array,
 * the sequence is determined by priority. The higher priority,
 * the larger the index will be, as I dequeue the array from the
 * end of the array which will save time of shifting that will be
 * used if "the higher priority, the smaller the index" strategy
 * is used.
 */
void PriorityQueue::enqueue(string value, double priority) {
    // TODO: Fill in the necessary code
    if (count == capacity) expandCapacity();
    if (count == 0) {
        array[0].value = value;
        array[0].priority = priority;
        count ++;
        return;
    }
    // 3 different conditions for inserting priority: 1. priority is larger than
    // any other priorities in array; 2. priority is smaller than any other other
    // priorities in array; 3. priority lies beteen the priorities in array.

    if (count > 0) {
        if (array[0].priority < priority) {
            for (int j = count; j > 0; j--) {
                array[j] = array[j - 1];
            }
            array[0].value = value;
            array[0].priority = priority;
        } else if (array[count - 1].priority > priority) {
            array[count].value = value;
            array[count].priority = priority;
        } else {
            for (int i = 0; i < count; i++){
                if (array[i].priority >= priority && array[i + 1].priority <= priority) {
                    for (int j = count; j > i + 1; j--) {
                        array[j] = array[j - 1];
                    }
                    array[i + 1].value = value;
                    array[i + 1].priority = priority;
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
