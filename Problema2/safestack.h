#include <stack>
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

template<class T>
class SafeStack {
private:
    mutex mt;
    stack<T> st;
public:
    SafeStack () {
    }

    void push (T data) {
        this->mt.lock ();
        this->st.push(data);
        this->mt.unlock ();
    }

    void pop () {
        if (this->st.empty()) return;
        this->mt.lock();this->st.pop();
        this->mt.unlock();
    }   

    bool is_empty() {
        return this->st.empty();
    }

    T peek () {
        return this->st.top();
    }
};