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


//void PriorityQueue::bubbleUp(int n) {
//    if (n == 0 || array[(n - 1) / 2].priority <= array[n].priority) {
//        return;
//    } else {
//        string valueTemp = array[n].value;
//        int priorityTemp = array[n].priority;
//        array[n].value = array[(n - 1) / 2].value;
//        array[n].priority = array[(n - 1) / 2].priority;
//        array[(n - 1) / 2].value = valueTemp;
//        array[(n - 1) / 2].priority = priorityTemp;
//        bubbleUp((n - 1) / 2);
//    }
//}

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
    count--;
    bubbleDown(start);

    return result;
}

//void PriorityQueue::bubbleDown(int n) {
//    if (n == count - 1 || (array[n].priority <= array[2 * n + 1].priority &&
//                       array[n].priority <= array[2 * n + 2].priority)) {
//        return;
//    } else {
//        int next;
//        if (array[2 * n + 1].priority <= array[2 * n + 2].priority) {
//            next = 2 * n + 1;
//        } else {
//            next = 2 * n + 2;
//        }
//        bubbleDown (next);
//    }
//}


void PriorityQueue::bubbleUp(int n) {
    if (n == 0 || array[(n - 1) / 2].priority <= array[n].priority) {
        return;
    } else {
        //cout << "bubbleUp, count = " << count << endl;
        std::string valueTemp = array[n].value;
        int priorityTemp = array[n].priority;
        array[n].value = array[(n - 1) / 2].value;
        array[n].priority = array[(n - 1) / 2].priority;
        array[(n - 1) / 2].value = valueTemp;
        array[(n - 1) / 2].priority = priorityTemp;
        cout << array[(n - 1) / 2].value << " is bubbled up." << endl;
        bubbleUp((n - 1) / 2);
    }
}


void PriorityQueue::bubbleDown(int n) {
    if ((2 * n + 1) >= count - 1) {
        return;
    } else {
        //std::string potentialValue = array[2 * n + 1].value;
        //int potentialPriority = array[2 * n + 1].priority;
        int potentialNext = 2 * n + 1;

        if ((2 * n + 2) <= (count - 1)) {
            if (array[2 * n + 1].priority <= array [2 * n + 2].priority ) {
                potentialNext = (2 * n + 1);
            } else {
                potentialNext = (2 * n + 2);
            }
        }

        int next = potentialNext;

        if (array[n].priority > array[next].priority) {
            cout << "Total " << count << " elements, ";
            cout << array[n].priority << " is greater than " << array[next].priority << ", ";
            std::string valueTemp = array[next].value;
            int priorityTemp = array[next].priority;
            array[next].value = array[n].value;
            array[next].priority = array[n].priority;
            array[n].value = valueTemp;
            array[n].priority = priorityTemp;
            cout << array[potentialNext].value << " is bubbled down." << endl;
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
