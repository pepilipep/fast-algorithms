#include <iostream>
#include <cassert>
#include <ctime>

using namespace std;

#include "RMQPlusMinus.h"
#include "LCA.h"
#include "RMQ.h"

void testRMQPlusMinus(){

    int a1[] = {2};
    RMQNaive naive1(1, a1);
    RMQLog log1(1, a1);
    RMQPlusMinus plus1(1, a1);
    assert(naive1.Query(0, 0) == log1.Query(0, 0) && naive1.Query(0, 0) == plus1.Query(0, 0));

    /*int a2[10000];
    a2[0] = rand() % 10000;
    for(int i = 1; i < 10000; i ++){
        a2[i] = a2[i - 1] + 2 * (rand() % 2) - 1;
    }
    RMQNaive naive2(10000, a2);
    RMQLog log2(10000, a2);
    RMQPlusMinus plus2(10000, a2);
    for(int i = 0; i < 10000; i ++){
        for(int j = i; j < 10000; j ++){
            assert(naive2.Query(i, j) == log2.Query(i, j) && naive2.Query(i, j) == plus2.Query(i, j));
        }
    }*/

    int a3[100000];
    a3[0] = rand() % 100000;
    for(int i = 1; i < 100000; i ++){
        a3[i] = a3[i - 1] + 2 * (rand() % 2) - 1;
    }
    RMQLog log3(100000, a3);
    RMQPlusMinus plus3(100000, a3);
    cout << (double)clock() / (double)CLOCKS_PER_SEC << endl;
    for(int i = 0; i < 100000; i ++){
        for(int j = i; j < 100000; j ++){
            log3.Query(i, j);
        }
    }
    cout << (double)clock() / (double)CLOCKS_PER_SEC << endl;
    for(int i = 0; i < 100000; i ++){
        for(int j = i; j < 100000; j ++){
            plus3.Query(i, j);
        }
    }
    cout << (double)clock() / (double)CLOCKS_PER_SEC << endl;
}

void testLCA(){
    int root = 0;
    int p[] = {-1, 0, 0, 1, 1, 2, 4, 4, 5, 5, 5, 9};
    LCA lca(12, p, root);
    cout << lca.Query(1, 1) << endl;
    cout << lca.Query(0, 1) << endl;
    cout << lca.Query(6, 7) << endl;
    cout << lca.Query(3, 6) << endl;
    cout << lca.Query(3, 7) << endl;
    cout << lca.Query(8, 10) << endl;
    cout << lca.Query(8, 11) << endl;
    cout << lca.Query(9, 11) << endl;
    cout << lca.Query(7, 8) << endl;
}

void testRMQ(){
    const int n = 10000;
    int a[n];
    for(int i = 0; i < n; i ++){
        a[i] = rand() % n;
    }
    RMQLog rmqLog(n, a);
    RMQ rmq(n, a);
    for(int i = 0; i < n; i ++){
        for(int j = i; j < n; j ++){
            assert(rmq.Query(i, j) == rmqLog.Query(i, j));
        }
    }

}

int main(){
    //testRMQPLusMinus();
    //testLCA();
    //testRMQ();
    

    return 0;
}