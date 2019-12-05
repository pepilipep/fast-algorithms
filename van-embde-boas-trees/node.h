#ifndef NODE_H
#define NODE_H

#include <vector>

typedef long long ll;

struct node{

    ll min, max;
    int k, size;
    node *Q;
    std::vector<node*> R;

public:

    node(){
        min = max = -1;
        k = 1;
        size = 0;
        Q = nullptr;
        R.assign(1LL << ((k + 1) / 2), nullptr);
    }

    node(int _k) : k(_k) {
        min = max = -1;
        size = 0;
        Q = nullptr;
        R.assign(1LL << ((k + 1) / 2), nullptr);
    }

    node(ll x, int _k) : k(_k){
        size = 1;
        min = max = x;
        Q = nullptr;
        R.assign(1LL << ((k + 1) / 2), nullptr);
    }


};



#endif