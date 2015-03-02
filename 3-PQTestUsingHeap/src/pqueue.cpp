/*
 * File: pqueue.cpp (heap version)
 * -------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a heap as the
 * underlying representation.  Only the copy constructor and assignment
 * operator are included.  Your job is to include definitions for the
 * other exported methods and to make a change to the definition of the
 * assignment operator so that it deletes any old storage.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

// TODO: Add your method definitions here

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
 * ------------------------
 * Add value and priority to array[count], and bubble up
 * this element if its priority is smaller than its parent.
 */
void PriorityQueue::enqueue(string value, double priority) {
    if (count == capacity) expandCapacity();
    if (count == 0) {
        array[0].value = value;
        array[0].priority = priority;
        count++;
        return;
    }
    if (count > 0) {
        array[count].value = value;
        array[count].priority = priority;
        int start = count;
        bubbleUp(start);
        count++;
        return;
    }
}


/*
 * Function: dequeue
 * ------------------------
 * returns the value of array[count - 1] which is the last element
 * in the array. Then swap the last element with first element, if
 * the swapped first element is larger than its children, bubbledown
 * the element until the parent is smaller than children.
 */
string PriorityQueue::dequeue() {
    // TODO: Replace this line with the necessary code
    if (isEmpty()) error ("The queue is empty.");
    string result = peek();
    string valueTemp = array[count - 1].value;
    int priorityTemp = array[count - 1].priority;
    array[count - 1].value = array[0].value;
    array[count - 1].priority =  array[0].priority ;
    array[0].value = valueTemp;
    array[0].priority = priorityTemp;
    int start = 0;
    // count-- command must come before bubbleDown() because
    // bubbleDown() will check count in if condition. From
    // the perspective of procedure described in handout, that is
    // delete the last element (after swapped) and then bubble down.
    count--;
    bubbleDown(start);
    return result;
}


/*
 * Function: bubbleUp
 * ------------------------
 * Compares array[n] recursively with its parent(array[(n-1)/2]). Keep
 * the element bubbled up until its priority is bigger than its parent.
 */
void PriorityQueue::bubbleUp(int n) {
    if (n == 0 || array[(n - 1) / 2].priority <= array[n].priority) {
        return;
    } else {
        std::string valueTemp = array[n].value;
        int priorityTemp = array[n].priority;
        array[n].value = array[(n - 1) / 2].value;
        array[n].priority = array[(n - 1) / 2].priority;
        array[(n - 1) / 2].value = valueTemp;
        array[(n - 1) / 2].priority = priorityTemp;
        bubbleUp((n - 1) / 2);
    }
}

/*
 * Function: bubbleDown
 * ------------------------
 * Compares array[n] recursively with its children(array[2n+1] and array[2n+2]).
 * Keep the element bubbled down until its priority is smaller than both of
 * its children. One thing to be aware is that array[n]'s children may be out of
 * the "true" range of array.
 *
 */
void PriorityQueue::bubbleDown(int n) {
    // to return, 2n+1 must greater than count. (cannot include equal).
    if ((2 * n + 1) > count - 1) {
        return;
    } else {
        int potentialNext = 2 * n + 1;
        // potentialNext equals to the "left" child.
        // if the "right" child does not exist, next = potentialNext;
        // if the "right" child exists, compare the two children first.
        if ((2 * n + 2) <= (count - 1)) {
            if (array[2 * n + 1].priority <= array [2 * n + 2].priority ) {
                potentialNext = (2 * n + 1);
            } else {
                potentialNext = (2 * n + 2);
            }
        }

        int next = potentialNext;

        if (array[n].priority > array[next].priority) {
            std::string valueTemp = array[next].value;
            int priorityTemp = array[next].priority;
            array[next].value = array[n].value;
            array[next].priority = array[n].priority;
            array[n].value = valueTemp;
            array[n].priority = priorityTemp;
            bubbleDown (next);
        }
    }
}

string PriorityQueue::peek() {
    // TODO: Replace this line with the necessary code
    if (isEmpty()) error ("The queue is empty.");
    return array[0].value;
}

double PriorityQueue::peekPriority() {
    // TODO: Replace this line with the necessary code
    if (isEmpty()) error ("The queue is empty.");
    return array[0].priority;
}



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
        // TODO: Include code to delete any data from the old queue
        deepCopy(src);
    }
    return *this;
}
