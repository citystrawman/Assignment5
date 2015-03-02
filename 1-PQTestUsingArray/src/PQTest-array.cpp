/*
 * File: PQTest.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This is the starter file for the test program for Assignment #5.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <cctype>
#include "console.h"
#include "pqueue.h"
#include "simpio.h"
#include "strlib.h"
#include "tokenscanner.h"
using namespace std;

/* Function prototypes */

void helpCommand();
void executeCommand(PriorityQueue & pQueue, string cmd);
void executeEnqueue(PriorityQueue & pq, string cmd);
string subtractToken(string & str);
bool isNumeric (string str);
void executeDequeue(PriorityQueue & pq, string cmd);
void executePeekPriority(PriorityQueue & pq, string cmd);
void executePeek(PriorityQueue & pq, string cmd);
void executeClear(PriorityQueue & pq, string cmd);
void executeSize(PriorityQueue & pq, string cmd);
void executeIsEmpty(PriorityQueue & pq, string cmd);
void executeList(PriorityQueue pq, string cmd);

/* Main program */

int main() {
   PriorityQueue pq;
   while (true) {
      string cmd = getLine("> ");
      if (cmd != "") {
         executeCommand(pq, cmd);
      }
   }
   return 0;
}

/*
 * Function: helpCommand
 * ---------------------
 * Displays a list of the required commands.  If you extend this program,
 * you should add new entries to this function.
 */

void helpCommand() {
   cout << "enqueue value priority -- Enqueues value at priority" << endl;
   cout << "dequeue -- Dequeues the most urgent item" << endl;
   cout << "peek -- Peeks at the first item without removing it" << endl;
   cout << "peekPriority -- Reports the priority of the first item" << endl;
   cout << "clear -- Clears the queue" << endl;
   cout << "size -- Reports the size of the queue" << endl;
   cout << "isEmpty -- Reports whether the queue is empty" << endl;
   cout << "list -- Lists the elements of the queue" << endl;
   cout << "help -- Prints this message" << endl;
}


/*
 * Function: executeCommand
 * ------------------------
 * Executes the command specified by the user.
 */
void executeCommand(PriorityQueue & pq, string cmd){
    switch (cmd[0]) {
    case 'e' : executeEnqueue(pq, cmd); break;
    case 'd' : executeDequeue(pq, cmd); break;
    case 'p' : if (cmd[4] == 'P') {
            executePeekPriority(pq, cmd); break;
        } else executePeek(pq, cmd); break;
    case 'c' : executeClear(pq, cmd); break;
    case 's' : executeSize(pq, cmd); break;
    case 'i' : executeIsEmpty(pq, cmd); break;
    case 'l' : executeList(pq, cmd); break;
    case 'h' : helpCommand(); break;
    default: cout << "Illegal command" << endl; break;
    }
}

/*
 * Function: executeEnqueue
 * ------------------------
 * Executes the enqueue command specified by the user.
 */
void executeEnqueue(PriorityQueue & pq, string cmd) {
    string inputStrValue;
    string inputStrPriority;
    double inputPriority;

    if (cmd.substr(0, 7) != "enqueue") {
        cout <<"Illegal command" << endl;
    }
     // 9 is least number of letters that forms an effective enqueue command
     // the second judgement determines if there's any spaces that separates
     // the command and input string/priority.
    else if (cmd.length() < 9 && cmd[7] != ' ') {
        cout << "Illegal command" << endl; return;
    } else {
        string cmdTemp = cmd.substr(7);
        inputStrValue = subtractToken(cmdTemp);
        if (inputStrValue == "") {
            cout << "A string A is expected" << endl; return;
        }
        inputStrPriority = subtractToken(cmdTemp);
        if (inputStrPriority == "" || !isNumeric(inputStrPriority) ) {
            inputPriority = 1;
        } else {
            inputPriority = stringToReal(inputStrPriority);
        }
        pq.enqueue(inputStrValue, inputPriority);

    }
}


/*
 * Function: subtractToken
 * ------------------------
 * Subtracts the first token of the string that exists between spaces,
 * and subtract the token from string so that the string can be further
 * subtracted more tokens. The variable start keeps track of the index
 * position at which the first token begins. The code sets start to -1
 * to indicate that the beginning of the first token has not yet been
 * encountered.
 * (make str = str + " "; so that the last token can be discovered.)
 */

string subtractToken(string & str) {
    string result;
    int start = -1;
    str = str + " ";
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (ch != ' ') {
            if (start == -1) start = i;
        } else {
            if (start >= 0) {
                result =str.substr(start, i - start);
                str = str.substr(i);
                start = -1;
                return result;
            }
        }
    }
    return result;
}

/*
 * Function: isNumeric
 * ------------------------
 * Determines if the string constitutes a numeric number.
 */
bool isNumeric (string str) {
    if (str.find(".") == string::npos) {
        for ( int i = 0; i < str.length(); i++) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    } else {
        int pos = str.find(".");
        string strTemp = str.substr(0, pos);
        str = strTemp + str.substr(pos + 1);
        for ( int i = 0; i < str.length(); i++) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }
}


/*
 * Function: executeDequeue
 * ------------------------
 * Executes the dequeue command specified by the user.
 */
void executeDequeue(PriorityQueue & pq, string cmd) {
    if (cmd != "dequeue") {
        cout << "Illegal command" << endl;
    } else {
        if (pq.isEmpty()) {
            cout << "The queue is empty" << endl;
        } else {
            cout << pq.dequeue() << endl;
        }
    }
}


/*
 * Function: executePeekPriority
 * ------------------------
 * Executes the peekPriority command specified by the user.
 */
void executePeekPriority(PriorityQueue & pq, string cmd) {
    if (cmd != "peekPriority") {
        cout << "Illegal command" << endl;
    } else {
        if (pq.isEmpty()) {
            cout << "The queue is empty" << endl;
        } else {
            cout << pq.peekPriority() << endl;
        }
    }
}

/*
 * Function: executePeek
 * ------------------------
 * Executes the peek command specified by the user.
 */
void executePeek(PriorityQueue & pq, string cmd) {
    if (cmd != "peek") {
        cout << "Illegal command" << endl;
    } else {
        if (pq.isEmpty()) {
            cout << "The queue is empty" << endl;
        } else {
            cout << pq.peek() << endl;
        }
    }
}

/*
 * Function: executeClear
 * ------------------------
 * Executes the clear command specified by the user.
 */
void executeClear(PriorityQueue & pq, string cmd) {
    if (cmd != "clear") {
        cout << "Illegal command" << endl;
    } else {
        pq.clear();
    }
}

/*
 * Function: executeSize
 * ------------------------
 * Executes the size command specified by the user.
 */
void executeSize(PriorityQueue & pq, string cmd) {
    if (cmd != "size") {
        cout << "Illegal command" << endl;
    } else {
        cout << pq.size() << endl;
    }
}

/*
 * Function: executeIsEmpty
 * ------------------------
 * Executes the isEmpty command specified by the user.
 */
void executeIsEmpty(PriorityQueue & pq, string cmd) {
    if (cmd != "isEmpty") {
        cout << "Illegal command" << endl;
    } else {
        if (pq.isEmpty()) {
            cout << "true" << endl;
        }
        else {
            cout << "false" << endl;
        }
    }
}

/*
 * Function: executeList
 * ------------------------
 * Executes the list command specified by the user.
 * This function dequeues all elements of the pq and store
 * the value and priority into the correspoding array
 * respectively and print the value out. Then enqueue the array
 * back into pq.
 */
void executeList(PriorityQueue pq, string cmd) {
    if (cmd != "list") {
        cout << "Illegal command" << endl;
    } else {
        string  *valueArr = new string [pq.size()];
        double priorityArr[pq.size()];
        cout << "Queue: ";

        int sizeNum = pq.size();
        for (int i = 0; i < sizeNum; i++) {
            valueArr[i] = pq.peek();
            cout << valueArr[i] << " ";
            priorityArr[i] = pq.peekPriority();
            pq.dequeue();
        }
        cout << endl;
        for (int i = 0; i < pq.size(); i++) {
            pq.enqueue(valueArr[i], priorityArr[i]);
        }
        delete []valueArr;
    }
}
