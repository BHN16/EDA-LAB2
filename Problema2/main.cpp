#include <iostream>
#include <thread>
#include "safestack.h"
#include <assert.h>

using namespace std;


void func (SafeStack<char>*s, int n, char c) {
    for (int i = 0; i < n; i++) {
        s->push(c);
    }
}


class tester{
public:
    void test(int a, int b, int c, int d, int e){
	thread threads[5];
	SafeStack<char> s;
    	SafeStack<char>* s1 = new SafeStack<char>(); 
    
	threads[0] = thread(func, s1, a, 'A');
    	threads[1] = thread(func, s1, b, 'B');
    	threads[2] = thread(func, s1, c, 'C');
    	threads[3] = thread(func, s1, d, 'D');
    	threads[4] = thread(func, s1, e, 'E');
  	for (int i = 0; i < 5; i++) {
        	threads[i].join();
    	}
    	while (!s1->is_empty()) {
        	cout << s1->peek() << endl;
		switch(s1->peek()){
			case 'A': a--;
			case 'B': b--;
			case 'C': c--;
			case 'D': d--;
			case 'E': e--;
		}
        	s1->pop();
    	}

	if(a==b==c==d==e==0) cout<<"Test passed\n";
	else cout<<"Test failed\n";


    }

};


int main () {
    
    tester t;
    t.test(1,2,3,4,5);

    return 0;
}
