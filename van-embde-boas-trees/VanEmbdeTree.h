#ifndef VANEMBDETREE_H
#define VANEMBDETREE_H

#include <cmath>
#include "node.h"

typedef long long ll;

class VanEmbdeTree{

    node *root;
    ll U;
    ll logU;

    void insert(node *cur, ll x){

        if(cur->size == 0){
            cur->min = cur->max = x;
            (cur->size) = 1;
            return;
        }
        if(x == cur->min || x == cur->max)
        {
            return;
        }
        if(cur->size == 1){
            if(x < cur->max)
                cur->min = x;
            else
                cur->max = x;
            (cur->size) ++;
            return;
        }
        if(x < cur->min){
            std::swap(x, cur->min);
            insert(cur, x);
            return;
        }
        if(x > cur->max){
            std::swap(x, cur->max);
            insert(cur, x);
            return;
        }
        ll a = (x >> (cur->k / 2));
        ll b = x - (a << (cur->k / 2));
        if(cur->R[a]->size == 0){
            insert(cur->Q, a);
        }
        int pr_sz = cur->R[a]->size;
        insert(cur->R[a], b);
        cur->size += (cur->R[a]->size - pr_sz);
    }

    void erase(node *cur, ll x){
        if(cur->size == 0 || x < cur->min || x > cur->max){
            return;
        }
        if(cur->size == 1){
            cur->min = cur->max = -1;
            cur->size = 0;
            return;
        }
        if(cur->size == 2){
            if(x == cur->min){
                cur->min = cur->max;
                cur->size --;
            }
            else if(x == cur->max){
                cur->max = cur->min;
                cur->size --;
            }
            return;
        }
        if(x == cur->min){
            ll new_min_a = cur->Q->min;
            ll new_min_b = cur->R[new_min_a]->min;
            cur->min = (new_min_a << (cur->k / 2)) + new_min_b;
            erase(cur->R[new_min_a], new_min_b);
            if(cur->R[new_min_a]->size == 0){
                erase(cur->Q, new_min_a);
            }
            cur->size --;
            return;
        }
        if(x == cur->max){
            ll new_max_a = cur->Q->max;
            ll new_max_b = cur->R[new_max_a]->max;
            cur->max = (new_max_a << (cur->k / 2)) + new_max_b;
            erase(cur->R[new_max_a], new_max_b);
            if(cur->R[new_max_a]->size == 0){
                erase(cur->Q, new_max_a);
            }
            cur->size --;
            return;
        }
        ll a = (x >> (cur->k / 2));
        ll b = x - (a << (cur->k / 2));
        int pr_sz = cur->R[a]->size;
        erase(cur->R[a], b);
        cur->size -= (pr_sz - cur->R[a]->size);
        if(cur->R[a]->size == 0){
            erase(cur->Q, a);
        }
    }

    void build(node *&cur, int k){
        cur = new node(k);
        if(k == 1)
            return;
        build(cur->Q, (k + 1) / 2);
        for(int i = 0; i < cur->R.size(); i ++){
            build(cur->R[i], k / 2);
        }
    }

    void deleteNodes(node *cur){
        if(cur->k == 1){
            delete cur;
            return;
        }
        for(node *next : cur->R){
            deleteNodes(next);
        }
        deleteNodes(cur->Q);
        delete cur;
    }

    ll prev(node *cur, ll x){
        if(cur->size == 0 || cur->min > x)
            return -1;
        if(cur->size <= 2){
            if(x >= cur->max)
                return cur->max;
            return cur->min;
        }
        if(cur->max <= x){
            return cur->max;
        }
        if(cur->min == x)
            return x;
        ll a = (x >> (cur->k / 2));
        ll b = x - (a << (cur->k / 2));
        if(cur->R[a]->size != 0 && cur->R[a]->min <= b){
            return (a << (cur->k / 2)) + prev(cur->R[a], b);
        }
        ll a1 = prev(cur->Q, a-1);
        if(a1 == -1)
            return cur->min;
        else
            return (a1 << (cur->k / 2)) + cur->R[a1]->max;
    }

    bool Search(node *cur, ll x){
        if(x == cur->min || x == cur->max)
            return true;
        if(cur->k == 1){
            return false;
        }
        ll a = (x >> (cur->k / 2));
        ll b = x - (a << (cur->k / 2));
        return Search(cur->R[a], b);
    }

public:

    VanEmbdeTree(ll _U) : U(_U){
        logU = log2(U);
        if((1LL << logU) != U){
            logU ++;
            U = (1LL << logU);
        }
        build(root, logU);
    }

    ~VanEmbdeTree(){
        deleteNodes(root);
    }

    void insert(ll x){
        insert(root, x);
    }

    void erase(ll x){
        erase(root, x);
    }

    bool Search(ll x){
        return Search(root, x);
    }

    int size(){
        return root->size;
    }

    ll prev(ll x){
        return prev(root, x);
    }


};


#endif