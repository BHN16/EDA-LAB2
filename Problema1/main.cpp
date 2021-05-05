#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

#define MAXD 1000
#define MAXT 5
using namespace std;

double arr[MAXD];
thread threads[MAXT];
double vmax = 0;
double tpa = MAXD/MAXT;
mutex mt;
atomic<double> maxAtomic (0);

void locking(int d) {
    double maxl = 0;
    for (int i = 0; i < tpa; i++) {
        maxl = max(maxl, arr[(int)(tpa*d+i)]);
    }
    mt.lock ();
    vmax = max(vmax, maxl);
    mt.unlock ();
}

void atomicVariable (int d) {
    double maxl = 0;
    for (int i = 0; i < tpa; i++) {
        maxl = max(maxl, arr[(int)(tpa*d+i)]);
    }
    maxAtomic = max(maxAtomic.load(), maxl);
}

int main() {
    for(int i = 0; i < MAXD; i++)  {
        arr[i] = random()/(double)1147483648;
    }
    for (int i = 0; i < MAXT; i++) {
        threads[i] = thread(atomicVariable, i);
    }
    for (int i = 0; i < MAXT; i++) {
        threads[i].join();
    }
    sort(arr, arr+MAXD);
    cout << arr[MAXD-1] << endl;
    cout << vmax << endl;
    cout << maxAtomic.load() << endl;
    return 0;
}