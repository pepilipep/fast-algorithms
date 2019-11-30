#ifndef RMQ_H
#define RMQ_H

#include "LCA.h"
#include "CartesianTree.h"

class RMQ{

    int n;
    int *a;
    LCA *lca;

public:

    RMQ(int _n, int *_a) : n(_n){
        a = new int[n];
        for(int i = 0; i < n; i ++){
            a[i] = _a[i];
        }
        CartesianTree cartesianTree(n, a);
        lca = new LCA(n, cartesianTree.getParents(), cartesianTree.getRoot());
    }

    int Query(int i, int j){
        lca->Query(i, j);
    }

    ~RMQ(){
        delete[] a;
        delete lca;
    }

};


#endif
