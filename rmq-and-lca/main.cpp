#include <iostream>

using namespace std;

#include "RMQPlusMinus.h"

int main(){

    int a[] = {1, 0, 1, 2, 3, 2, 3, 2, 1, 0, -1, -2, -1, 0, 1, 0, 1};
    RMQPlusMinus rmq(17, a);
    cout << "=============\n";
    cout << rmq.Query(0, 7) << endl;
    cout << "=============\n";
    cout << rmq.Query(4, 4) << endl;
    cout << "=============\n";
    cout << rmq.Query(2, 4) << endl;
    cout << "=============\n";
    cout << rmq.Query(1, 5) << endl;
    cout << "=============\n";
    cout << rmq.Query(6, 7) << endl;
    cout << "=============\n";
    cout << rmq.Query(0, 2) << endl;
    cout << "=============\n";
    cout << rmq.Query(0, 15) << endl;
    cout << "=============\n";
    cout << rmq.Query(8, 15) << endl;
    cout << "=============\n";

    return 0;
}