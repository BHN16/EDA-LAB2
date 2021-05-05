#include <iostream>
#include <thread>
#include "safestack.h"
using namespace std;

void func (SafeStack<char>*s, int n, char c) {
    for (int i = 0; i < n; i++) {
        s->push(c);
    }
}

int main () {
    thread threads[5];
    SafeStack<char> s;
    SafeStack<char>* s1 = new SafeStack<char>(); 
    for (int i = 0; i < 3; i++) {
        s.push('A');
    }
    for (int i = 0; i < 6; i++) {
        s.push('B');
    }
    for (int i = 0; i < 2; i++) {
        s.push('C');
    }
    for (int i = 0; i < 5; i++) {
        s.push('D');
    }
    for (int i = 0; i < 8; i++) {
        s.push('E');
    }
    while (!s.is_empty()) {
        cout << s.peek() << endl;
        s.pop ();
    }
    threads[0] = thread(func, s1, 3, 'A');
    threads[1] = thread(func, s1, 6, 'B');
    threads[2] = thread(func, s1, 2, 'C');
    threads[3] = thread(func, s1, 5, 'D');
    threads[4] = thread(func, s1, 8, 'E');
    for (int i = 0; i < 5; i++) {
        threads[i].join();
    }
    while (!s1->is_empty()) {
        cout << s1->peek() << endl;
        s1->pop();
    }
    return 0;
}